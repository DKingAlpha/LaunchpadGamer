#include <windows.h>  
#include <iostream>
#include <cstdlib>

#include "lib/lpdgamer/launchpad.h"


int main(void)
{
    LaunchpadPro* lpd = new LaunchpadPro();
    std::string config_set;
    std::cout << "Please Enter the Name of Config Set(Name of Folder in config/):" << std::endl;
    std::cin >> config_set;
    while (true)
    {
        lpd->connect();
        if (lpd->isConnected())
        {
            std::cout << "Launchpad is Connected!" << std::endl << "Launchpad¡¡Gamer Running" << std::endl;
            lpd->loadConfig(config_set.c_str());
        }
        else
        {
            std::cout << "Launchpad is not connected (well)." << std::endl<< "Reconnecting..." << std::endl;
            Sleep(5000);
        }
    }
    delete lpd;
    return 0;
}
