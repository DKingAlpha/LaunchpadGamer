#include "mapper.h"
#include <fstream>
#include <streambuf>
#include <thread>
#include "padstatus.h"

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
    input = new InputAgent();
    game_to_map = mapgame;
    setupMapper(game_to_map);

}

MidiParser::MidiParser(LaunchpadPro * launchpad)
{
    lpd = launchpad;
    input = new InputAgent();
    game_to_map = "lol";
    setupMapper(game_to_map);
}

void MidiParser::parseMsg(std::vector<BYTE> msg)
{
    int  key = 0, vel = 0;
    if (msg[0] == (BYTE)0x90 || msg[0] == (BYTE)0xB0)
    {
        key = msg[1];
        vel = msg[2];
        std::thread(std::bind(&MidiParser::reactTo, this ,key,vel)).detach();
    }
}

void MidiParser::setupMapper(std::string mapgame)
{
    loadLight(mapgame);
    loadKeyMap(mapgame);
}

void MidiParser::loadLight(std::string mapgame)
{

    // Read Light Config
    std::ifstream conffile_light("config/" + mapgame + "/light.ini", _IOS_Nocreate);

    if (conffile_light)
    {
        std::string conf((std::istreambuf_iterator<char>(conffile_light)), std::istreambuf_iterator<char>()); //read all
        std::vector<std::string> lines = split(conf, "\n");
        std::vector<std::string>::iterator liter;
        conf_lightmap.clear();
        for (liter = lines.begin(); liter != lines.end(); liter++)
        {
            if ((*liter).empty()) continue;                   // skip blank line
            if ((*liter).back() == '\r') (*liter).pop_back();     // rtrim '\r'
            if ((*liter).empty()) continue;
            if ((*liter)[0] == '#') continue;                     // ignore # comment line
            std::vector<std::string> values = split(*liter, " ", 2);
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
            if (stricmp(values[1].c_str(), "KEYAUTO") == 0) keyevent = 3;
            if (stricmp(values[1].c_str(), "KEYUP") == 0) keyevent = 2;
            if (stricmp(values[1].c_str(), "KEYDOWN") == 0) keyevent = 1;
            // ACTION
            if (values.size() == 2)
                actions = "AUTO()";
               else
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

    conffile_light.close();
}

void MidiParser::loadKeyMap(std::string mapgame)
{
    // Read KeyMap Config
    std::ifstream conffile_keymap("config/" + mapgame + "/keymap.ini", _IOS_Nocreate);

    if (conffile_keymap)
    {
        std::string conf((std::istreambuf_iterator<char>(conffile_keymap)), std::istreambuf_iterator<char>()); //read all
        std::vector<std::string> lines = split(conf, "\n");
        std::vector<std::string>::iterator liter;
        conf_keymap.clear();
        for (liter = lines.begin(); liter != lines.end(); liter++)
        {
            if ((*liter).empty()) continue;                   // skip blank line
            if ((*liter).back() == '\r') (*liter).pop_back();     // rtrim '\r'
            if ((*liter).empty()) continue;
            if ((*liter)[0] == '#') continue;                     // ignore # comment line
            std::vector<std::string> values = split(*liter, " ", 2);
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
            if (stricmp(values[1].c_str(), "KEYAUTO") == 0) keyevent = 3;
            if (stricmp(values[1].c_str(), "KEYUP") == 0) keyevent = 2;
            if (stricmp(values[1].c_str(), "KEYDOWN") == 0) keyevent = 1;
            // ACTION
            actions = values[2];

            // now analyse and insert
            if (key != 0 && keyevent >= 1 && keyevent <= 3)
            {
                std::pair<int, int> pair1(key, keyevent);
                std::map<std::pair<int, int>, std::string>::iterator mapiter;
                mapiter = conf_keymap.find(pair1);
                if (mapiter != conf_keymap.end())
                {
                    conf_keymap.erase(pair1);           // remove conflict old rule
                }
                std::pair<std::pair<int, int>, std::string> elem(pair1, actions);
                conf_keymap.insert(elem);
            }
        }
    }

}


void MidiParser::reactTo(int key, int vel)
{
    int pressure = vel;
    
    if (vel == 0)
    {
        PadStatus[key] = 0;
    }
    if (vel > 0)
    {
        PadStatus[key] = 1;
    }

    std::map<std::pair<int, int>, std::string>::iterator mapiter;
    //  Light Map
    {
        // handle KEYDOWN/KEYUP event
        mapiter = conf_lightmap.find(std::pair<int, int>(key, PadStatus[key] == 1?1:2));
        if (mapiter != conf_lightmap.end())
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
                    std::thread(std::bind(&LaunchpadPro::playMidiFile, lpd, param)).detach();
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
                    std::vector<std::string> ps = split(param, ",");
                    lpd->displayText(atoi(ps[0].c_str()), atoi(ps[1].c_str()), atoi(ps[2].c_str()) ,ps[3]);
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
        else
        {
            // handle KEYAUTO event             // no explicit KEYEVENTs are defined. We auto react.
            mapiter = conf_lightmap.find(std::pair<int, int>(key, 3));      // KEYAUTO
            if (mapiter != conf_lightmap.end())

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
                        if (PadStatus[key] == 1) std::thread(std::bind(&LaunchpadPro::playMidiFile, lpd, param)).detach();

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
                                lpd->setColor(atoi(cp[0].c_str()), atoi(cp[1].c_str()), PadStatus[key] == 1 ? atoi(cp[2].c_str()) : 0);
                            }
                            else    // size == 2
                            {
                                lpd->setColor(atoi(cp[0].c_str()), PadStatus[key] == 1 ? atoi(cp[1].c_str()) : 0);
                            }
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "AUTO") == 0)
                    {
                        lpd->setColor(key, PadStatus[key] == 1 ? key : 0);
                    }
                    if (stricmp(cmd_name.c_str(), "SetRowColor") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit < ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            lpd->setRowColor(atoi(cp[0].c_str()), PadStatus[key] == 1 ? atoi(cp[1].c_str()) : 0);
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "SetColumnColor") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit < ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            lpd->setColumnColor(atoi(cp[0].c_str()), PadStatus[key] == 1 ? atoi(cp[1].c_str()) : 0);
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "SetPadColor") == 0)
                    {
                        lpd->setPadColor(PadStatus[key] == 1 ? atoi(param.c_str()) : 0);
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
                                lpd->setFlash(atoi(cp[0].c_str()), atoi(cp[1].c_str()), PadStatus[key] == 1 ? atoi(cp[2].c_str()) : 0);
                            }
                            if (cp.size() == 2)
                            {
                                lpd->setFlash(atoi(cp[0].c_str()), PadStatus[key] == 1 ? atoi(cp[1].c_str()) : 0);
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
                                lpd->setPulse(atoi(cp[0].c_str()), atoi(cp[1].c_str()), PadStatus[key] == 1 ? atoi(cp[2].c_str()) : 0);
                            }
                            if (cp.size() == 2)
                            {
                                lpd->setPulse(atoi(cp[0].c_str()), PadStatus[key] == 1 ? atoi(cp[1].c_str()) : 0);
                            }
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "DisplayText") == 0)
                    {
                        std::vector<std::string> ps = split(param, ",");
                        PadStatus[key] == 1 ? lpd->displayText(atoi(ps[0].c_str()), 1, atoi(ps[1].c_str()), ps[2])
                            : lpd->stopDisplayText();

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
            else
            {
                lpd->setColor(key, PadStatus[key] == 1 ? key : 0);
            }
        }

    }


    // Key Map
    {
        // handle KEYDOWN/KEYUP event
        mapiter = conf_keymap.find(std::pair<int, int>(key, PadStatus[key] == 1 ? 1 : 2));
        if (mapiter != conf_keymap.end())
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
                if (pv.size() > 0)
                {
                    param = pv[0];

                    if (stricmp(cmd_name.c_str(), "KeyPress") == 0)
                    {
                        std::thread(std::bind(&InputAgent::KeyPress, input, key , param)).detach();
                    }
                    if (stricmp(cmd_name.c_str(), "KeyDown") == 0)
                    {
                        input->KeyDown(param);
                    }
                    if (stricmp(cmd_name.c_str(), "KeyUp") == 0)
                    {
                        input->KeyUp(param);
                    }

                    if (stricmp(cmd_name.c_str(), "MouseLeftClick") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseLeftClick(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseLeftDown") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseLeftDown(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseLeftUp") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseLeftUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightClick") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseRightClick(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightDown") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseRightDown(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightUp") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseRightUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleClick") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseMiddleClick(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleDown") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseMiddleDown(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleUp") == 0)
                    {
                        std::vector<std::string> ps = split(param, "|");
                        std::vector<std::string>::iterator pit;
                        for (pit = ps.begin(); pit != ps.end(); pit++)
                        {
                            std::vector<std::string> cp = split(*pit, ",");
                            input->MouseMiddleUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMove") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        input->MouseMove(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                    if (stricmp(cmd_name.c_str(), "MouseShift") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        input->MouseShift(key,atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }

                    if (stricmp(cmd_name.c_str(), "Sleep") == 0)
                    {
                        Sleep(atoi(param.c_str()));
                    }
                } 
                else
                {
                    if (stricmp(cmd_name.c_str(), "MouseLeftClick") == 0)
                    {
                        input->MouseLeftClick();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseLeftDown") == 0)
                    {
                        input->MouseLeftDown();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseLeftUp") == 0)
                    {
                        input->MouseLeftUp();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightClick") == 0)
                    {
                        input->MouseRightClick();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightDown") == 0)
                    {
                        input->MouseRightDown();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRightUp") == 0)
                    {
                        input->MouseRightUp();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleClick") == 0)
                    {
                        input->MouseMiddleClick();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleDown") == 0)
                    {
                        input->MouseMiddleDown();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddleUp") == 0)
                    {
                        input->MouseMiddleUp();
                    }
                }
            }
            return;        // if explicit KEYEVENT is defined, return and not do KEYAUTO action
        }

        // handle KEYAUTO event
        // no explicit KEYEVENTs are defined. We auto react.
        mapiter = conf_keymap.find(std::pair<int, int>(key, 3));      // KEYAUTO
        if (mapiter!= conf_keymap.end())
        
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
                if (pv.size() > 0)
                {
                    param = pv[0];
                    if (stricmp(cmd_name.c_str(), "MouseLeft") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        PadStatus[key] == 1 ?
                            input->MouseLeftDown(atoi(cp[0].c_str()), atoi(cp[1].c_str())) :
                            input->MouseLeftUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRight") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        PadStatus[key] == 1 ?
                            input->MouseRightDown(atoi(cp[0].c_str()), atoi(cp[1].c_str())) :
                            input->MouseRightUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddle") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        PadStatus[key] == 1 ?
                            input->MouseMiddleDown(atoi(cp[0].c_str()), atoi(cp[1].c_str())) :
                            input->MouseMiddleUp(atoi(cp[0].c_str()), atoi(cp[1].c_str()));
                    }
                    if (stricmp(cmd_name.c_str(), "MouseShift") == 0)
                    {
                        std::vector<std::string> cp = split(param, ",");
                        if (PadStatus[key] == 1)
                        {
                            int delta_x = 0, delta_y = 0;
                            if (cp[0] == "+AUTO" || cp[0] == "AUTO") { delta_x = pressure / 4; }
                            else if (cp[0] == "-AUTO") { delta_x = - pressure / 4; }
                            else { delta_x = atoi(cp[0].c_str()); }
                            if (cp[1] == "+AUTO" || cp[1] == "AUTO") { delta_y = pressure / 6; }
                            else if (cp[1] == "-AUTO") { delta_y = -pressure / 6; }
                            else { delta_y = atoi(cp[1].c_str()); }
                            std::thread(std::bind(&InputAgent::MouseShift, input, key, delta_x, delta_y)).detach();
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "KeyPress") == 0)
                    {
                        if (PadStatus[key] == 1)
                        {
                            std::thread(std::bind(&InputAgent::KeyPress, input,key, param)).detach();
                            //input->KeyPress(key, param);
                        }
                    }
                    if (stricmp(cmd_name.c_str(), "Sleep") == 0)
                    {
                        Sleep(atoi(param.c_str()));
                    }
                }
                else
                {

                    if (stricmp(cmd_name.c_str(), "MouseLeft") == 0)
                    {
                        PadStatus[key] == 1 ?
                            input->MouseLeftDown() :
                            input->MouseLeftUp();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseRight") == 0)
                    {
                        PadStatus[key] == 1 ?
                            input->MouseRightDown() :
                            input->MouseRightUp();
                    }
                    if (stricmp(cmd_name.c_str(), "MouseMiddle") == 0)
                    {
                        PadStatus[key] == 1 ?
                            input->MouseMiddleDown() :
                            input->MouseMiddleUp();
                    }
                    
                }
            }
        }
    }
}

