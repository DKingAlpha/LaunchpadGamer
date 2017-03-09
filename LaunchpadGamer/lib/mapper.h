#pragma once
#include <map>
#include "launchpad.h"

class MidiParser
{
    public:
        MidiParser(LaunchpadPro* launchpad);
        MidiParser(LaunchpadPro* launchpad,std::string mapgame);
        void parseMsg(std::vector<BYTE> msg);
        void loadConfig(std::string mapgame);
        void reactTo(int key, int vel);

    private:
        LaunchpadPro* lpd = 0;
        std::string game_to_map;
        // map<pair<key,event>,action>
        std::map<std::pair<int, int>, std::string> conf_keymap;
        std::map<std::pair<int, int>, std::string> conf_lightmap;
};

