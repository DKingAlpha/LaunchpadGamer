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
        Sleep(2000);
        lpd->sendMessage(240, 126, 127, 6, 1, 247);
        while (true)
        {
            lpd->getMessage(&msg);
            /*scanf("%s", midif);
            sprintf(midifilename, "resources/%s.mid", midif);
            lpd->playMidiFile(midifilename);*/
            if (msg.size() != 0)
            {
                std::vector<BYTE>::iterator iter;
                for (iter = msg.begin(); iter != msg.end(); iter++)
                {
                    printf("0x%02X ",*iter);
                }
                for (iter = msg.begin(); iter != msg.end(); iter++)
                {
                    printf("%c", *iter);
                }
                printf("\n" );
            }
            Sleep(50);
        }
    }
    else
    {
        printf("not connected\n");
    }
}
