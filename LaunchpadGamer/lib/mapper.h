#pragma once
#include "launchpad.h"

class MidiParser
{
    public:
        MidiParser(LaunchpadBase* launchpad);
        MidiParser(LaunchpadBase* launchpad,std::string mapgame);
        void parseMsg(std::vector<BYTE> msg);
        void loadConfig(std::string mapgame);
        void reactTo(int key, int vel);

    private:

        LaunchpadBase* lpd = 0;
        std::string game_to_map;
};

