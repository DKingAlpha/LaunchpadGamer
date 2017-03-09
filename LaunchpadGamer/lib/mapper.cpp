#include "mapper.h"
#include <fstream>
#include <streambuf>
#include <thread>

#define PlayMidiFile 1
#define SetColor  2
#define SetRowColor 3
#define SetColumnColor 4
#define SetPadColor 5
#define SetFlash 6
#define SetPulse 7
#define DisplayText 8
#define ClearPad 9
#define StopDisplayText 10
#define SendMessage 11


std::vector<std::string> split(const  std::string& s, const std::string& delim, int times)
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    int time = 0;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);

        if (find_pos == std::string::npos)
        {
            elems.push_back(s.substr(pos, len - pos));
            time++;
            break;
        }
        if (find_pos == pos)
        {
            pos += delim_len;
            continue;
        }

        if (time >= times)
        {
            elems.push_back(s.substr(pos, len - pos));
            return elems;
        }
        else
        {
            elems.push_back(s.substr(pos, find_pos - pos));
            time++;
            pos = find_pos + delim_len;
        }
    }
    return elems;
}

std::vector<std::string> split(const  std::string& s, const std::string& delim)
{
    return split(s, delim, 1000);
}




MidiParser::MidiParser(LaunchpadPro * launchpad, std::string mapgame)
{
    lpd = launchpad;
    game_to_map = mapgame;
    loadConfig(game_to_map);

}

MidiParser::MidiParser(LaunchpadPro * launchpad)
{
    lpd = launchpad;
    game_to_map = "lol";
    loadConfig(game_to_map);
}

void MidiParser::parseMsg(std::vector<BYTE> msg)
{
    int  key = 0, vel = 0;
    if (msg[0] == (BYTE)0x90 || msg[0] == (BYTE)0xB0)
    {
        key = msg[1];
        vel = msg[2];
        std::thread th(std::bind(&MidiParser::reactTo, this ,key,vel));
        th.detach();
    }
}

void MidiParser::loadConfig(std::string mapgame)
{
    std::ifstream conffile("config/" + mapgame + "/light.ini",_IOS_Nocreate);

    if (conffile)
    {
        std::string conf((std::istreambuf_iterator<char>(conffile)), std::istreambuf_iterator<char>()); //read all
        std::vector<std::string> lines = split(conf, "\n");
        std::vector<std::string>::iterator liter;
        conf_lightmap.clear();
        for (liter = lines.begin(); liter != lines.end(); liter++)
        {
                if ((*liter).size() == 0) continue;                   // skip blank line
                if ((*liter).back() == '\r') (*liter).pop_back();     // rtrim '\r'
                if ((*liter).size() == 0) continue;
                if ((*liter)[0] == '#') continue;                     // ignore # comment line
                std::vector<std::string> values = split(*liter, " ",2);
                if (values.size() != 4 && values.size() != 3) continue;                     // skip malformed line
                // prepare arguments
                int key = 0, keyevent = 0; std::string actions;
                // KEY
                if (values[0].find(",") == std::string::npos)
                    key = atoi(values[0].c_str());
                else
                {
                    std::vector<std::string> loc = split(values[0], ",");
                    key = 10 * atoi(loc[0].c_str()) + atoi(loc[1].c_str());
                }
                // EVENT
                if (stricmp(values[1].c_str(), "KEYAUTO") == 0 ) keyevent = 3;
                if (stricmp(values[1].c_str(), "KEYUP") == 0) keyevent = 2;
                if (stricmp(values[1].c_str(), "KEYDOWN") == 0) keyevent = 1;
                // ACTION
                actions = values[2];

                // now analyse and insert
                if (key != 0 && keyevent >= 1 && keyevent <= 3)
                {
                    std::pair<int, int> pair1(key, keyevent);
                    std::map<std::pair<int, int>, std::string>::iterator mapiter;
                    mapiter = conf_lightmap.find(pair1);
                    if (mapiter != conf_lightmap.end())
                    {
                        conf_lightmap.erase(pair1);           // remove conflict old rule
                    }
                    std::pair<std::pair<int, int>, std::string> elem(pair1, actions);
                    conf_lightmap.insert(elem);
                }
        }
    }
    else
    {
        return;
    }
}

void MidiParser::reactTo(int key, int vel)
{
    int updown = 0;
    if (vel == 0)  updown = 2;     // UP
    if (vel > 0) updown = 1;     //DOWN

    
    std::map<std::pair<int, int>, std::string>::iterator mapiter;


    // handle defined event
    mapiter = conf_lightmap.find(std::pair<int, int>(key, updown));
    if (mapiter != conf_lightmap.end())
    {
        std::string actions;
        actions = mapiter->second;

        std::vector<std::string> action = split(actions, ";");
        for (std::vector<std::string>::iterator ait = action.begin(); ait != action.end(); ait++)
        {
            std::string cmd_line = *ait;
            std::string cmd_name = split(cmd_line,"(",1)[0];
            std::string param;
            std::vector<std::string> pv = split(split(cmd_line, "(", 1)[1], ")", 1);
            if (pv.size() > 0) param = pv[0];

            if (stricmp(cmd_name.c_str(), "PlayMidiFile") == 0)
            {
                std::thread th(std::bind(&LaunchpadPro::playMidiFile, lpd, param));
                th.detach();
            }
            if (stricmp(cmd_name.c_str(), "SetColor") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()), atoi(cp[2].c_str()));
                    }
                    else    // size == 2
                    {
                        lpd->setColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "SetRowColor") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                std::vector<std::string>::iterator pit;
                for (pit = ps.begin(); pit != ps.end(); pit++)
                {
                    std::vector<std::string> cp = split(*pit, ",");
                    lpd->setRowColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                }
            }
            if (stricmp(cmd_name.c_str(), "SetColumnColor") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                std::vector<std::string>::iterator pit;
                for (pit = ps.begin(); pit != ps.end(); pit++)
                {
                    std::vector<std::string> cp = split(*pit, ",");
                    lpd->setColumnColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                }
            }
            if (stricmp(cmd_name.c_str(), "SetPadColor") == 0)
            {
                lpd->setPadColor(atoi(param.c_str()));
            }
            if (stricmp(cmd_name.c_str(), "SetFlash") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setFlash(atoi(cp[0].c_str()), atoi(cp[1].c_str()), atoi(cp[2].c_str()));
                    }
                    else    // size == 2
                    {
                        lpd->setFlash(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "SetPulse") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setPulse(atoi(cp[0].c_str()), atoi(cp[1].c_str()), atoi(cp[2].c_str()));
                    }
                    else    // size == 2
                    {
                        lpd->setPulse(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "DisplayText") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                lpd->displayText(atoi(ps[0].c_str()), atoi(ps[1].c_str()), ps[2]);
            }
            if (stricmp(cmd_name.c_str(), "ClearPad") == 0)
            {
                lpd->clearPad();
            }
            if (stricmp(cmd_name.c_str(), "StopDisplayText") == 0)
            {
                lpd->stopDisplayText();
            }
            if (stricmp(cmd_name.c_str(), "SendMessage") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    lpd->sendMessage(atoi(cp[0].c_str()), atoi(cp[1].c_str()), atoi(cp[2].c_str()));
                }
            }
            if (stricmp(cmd_name.c_str(), "Sleep") == 0)
            {
                Sleep(atoi(param.c_str()));
            }
        }
        return;        // if explicit KEYEVENT is defined, return and not do KEYAUTO action
    }


    // handle KEYAUTO event             // no  explicit KEYEVENTs are defined. We auto react.
    
    mapiter = conf_lightmap.find(std::pair<int, int>(key, 3));      // KEYAUTO
    if (mapiter == conf_lightmap.end())
    {
        return;
    }
    else
    {
        std::string actions;
        actions = mapiter->second;

        std::vector<std::string> action = split(actions, ";");
        for (std::vector<std::string>::iterator ait = action.begin(); ait != action.end(); ait++)
        {
            std::string cmd_line = *ait;
            std::string cmd_name = split(cmd_line, "(", 1)[0];
            std::string param;
            std::vector<std::string> pv = split(split(cmd_line, "(", 1)[1], ")", 1);
            if (pv.size() > 0) param = pv[0];

            if (stricmp(cmd_name.c_str(), "PlayMidiFile") == 0)
            {
                std::thread th(std::bind(&LaunchpadPro::playMidiFile, lpd, param));
                th.detach();

            }
            if (stricmp(cmd_name.c_str(), "SetColor") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()), updown == 1 ? atoi(cp[2].c_str()) : 0);
                    }
                    else    // size == 2
                    {
                        lpd->setColor(atoi(cp[0].c_str()), updown == 1 ? atoi(cp[1].c_str()) : 0);
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "SetRowColor") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                std::vector<std::string>::iterator pit;
                for (pit = ps.begin(); pit < ps.end(); pit++)
                {
                    std::vector<std::string> cp = split(*pit, ",");
                    lpd->setRowColor(atoi(cp[0].c_str()), updown == 1 ? atoi(cp[1].c_str()) : 0);
                }
            }
            if (stricmp(cmd_name.c_str(), "SetColumnColor") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                std::vector<std::string>::iterator pit;
                for (pit = ps.begin(); pit < ps.end(); pit++)
                {
                    std::vector<std::string> cp = split(*pit, ",");
                    lpd->setColumnColor(atoi(cp[0].c_str()), updown == 1 ? atoi(cp[1].c_str()) : 0);
                }
            }
            if (stricmp(cmd_name.c_str(), "SetPadColor") == 0)
            {
                lpd->setPadColor(updown == 1 ? atoi(param.c_str()) : 0);
            }
            if (stricmp(cmd_name.c_str(), "SetFlash") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setFlash(atoi(cp[0].c_str()), atoi(cp[1].c_str()), updown == 1 ? atoi(cp[2].c_str()) : 0);
                    }
                    else    // size == 2
                    {
                        lpd->setFlash(atoi(cp[0].c_str()), updown == 1 ? atoi(cp[1].c_str()) : 0);
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "SetPulse") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    if (cp.size() == 3)
                    {
                        lpd->setPulse(atoi(cp[0].c_str()), atoi(cp[1].c_str()), updown == 1 ? atoi(cp[2].c_str()) : 0);
                    }
                    else    // size == 2
                    {
                        lpd->setPulse(atoi(cp[0].c_str()), updown == 1 ? atoi(cp[1].c_str()) : 0);
                    }
                }
            }
            if (stricmp(cmd_name.c_str(), "DisplayText") == 0)
            {
                std::vector<std::string> ps = split(param, "|");
                lpd->displayText(atoi(ps[0].c_str()), atoi(ps[1].c_str()), ps[2]);
            }
            if (stricmp(cmd_name.c_str(), "ClearPad") == 0)
            {
                lpd->clearPad();
            }
            if (stricmp(cmd_name.c_str(), "StopDisplayText") == 0)
            {
                lpd->stopDisplayText();
            }
            if (stricmp(cmd_name.c_str(), "SendMessage") == 0)
            {
                std::vector<std::string> colors = split(param, "|");
                std::vector<std::string>::iterator colit;
                for (colit = colors.begin(); colit != colors.end(); colit++)
                {
                    std::vector<std::string> cp = split(*colit, ",");
                    lpd->sendMessage(atoi(cp[0].c_str()), atoi(cp[1].c_str()), atoi(cp[2].c_str()));
                }
            }
            if (stricmp(cmd_name.c_str(), "Sleep") == 0)
            {
                Sleep(atoi(param.c_str()));
            }
        }
    }

}
