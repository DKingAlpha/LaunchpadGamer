#pragma once
#include <string>
#include <windows.h>
#include <set>

class InputAgent
{
public:
    void KeyPress(int caller_lpdkey, std::string keyname);
    void KeyUp(std::string keyname);
    void KeyUp(int vkcode);
    void KeyDown(int vkcode);
    void KeyDown(std::string keyname);
    void MouseLeftClick();
    void MouseLeftDown();
    void MouseLeftUp();
    void MouseRightClick();
    void MouseRightDown();
    void MouseRightUp();
    void MouseMiddleClick();
    void MouseMiddleDown();
    void MouseMiddleUp();
    void MouseLeftClick(int x, int y);
    void MouseLeftDown(int x, int y);
    void MouseLeftUp(int x, int y);
    void MouseRightClick(int x, int y);
    void MouseRightDown(int x, int y);
    void MouseRightUp(int x, int y);
    void MouseMiddleClick(int x, int y);
    void MouseMiddleDown(int x, int y);
    void MouseMiddleUp(int x, int y);
    void MouseMove(int x, int y);
    void MouseShift(int caller_lpdkey, int x, int y);

private:
    int parseKeyname(std::string keyname);
    bool isExtKey(int vkcode);

};