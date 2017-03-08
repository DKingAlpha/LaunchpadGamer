#include "mapper.h"
#include <fstream>

MidiParser::MidiParser(LaunchpadBase * launchpad, std::string mapgame)
{
    lpd = launchpad;
    game_to_map = mapgame;
    loadConfig(game_to_map);

}

MidiParser::MidiParser(LaunchpadBase * launchpad)
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
        reactTo(key,vel);
    }
}

void MidiParser::loadConfig(std::string mapgame)
{
    std::fstream conffile("config/" + mapgame + ".ini",_IOS_Nocreate);
    if (conffile)
    {
        
    }
}

void MidiParser::reactTo(int key, int vel)
{

}
