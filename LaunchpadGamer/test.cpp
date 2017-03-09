#include <windows.h>  
#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "lib/launchpad.h"


int main(void)
{
    char midif[20] = "";
    char midifilename[40] = "";

    LaunchpadPro* lpd = new LaunchpadPro();
    lpd->connect();
    std::vector<BYTE> msg;

    if (lpd->isConnected())
    {
        lpd->setupMapper("lol");
    }
    else
    {
        printf("not connected\n");
    }
}
