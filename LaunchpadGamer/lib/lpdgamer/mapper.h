#pragma once
#include <map>
#include "launchpad.h"
#include "inputagent.h"

class MidiParser
{
    public:
        MidiParser(LaunchpadPro* launchpad);
        MidiParser(LaunchpadPro* launchpad,std::string mapgame);
        void parseMsg(std::vector<BYTE> msg);
        void setupMapper(std::string mapgame);
        void reactTo(int key, int vel);

    private:
        LaunchpadPro* lpd = 0;
        InputAgent* input = new InputAgent();
        std::string game_to_map;
        // map<pair<key,event>,actionstring>
        std::map<std::pair<int, int>, std::string> conf_keymap;
        std::map<std::pair<int, int>, std::string> conf_lightmap;

        void loadLight(std::string mapgame);
        void loadKeyMap(std::string mapgame);

};


