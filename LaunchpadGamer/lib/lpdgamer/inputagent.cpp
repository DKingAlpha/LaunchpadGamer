#pragma once
#include "inputagent.h"
#include "extravk.h"
#include <iostream>
#include "padstatus.h"

int InputAgent::parseKeyname(std::string keyname)
{

    if (stricmp(keyname.c_str(), "LEFT") == 0) return VK_LEFT;
    if (stricmp(keyname.c_str(), "UP") == 0) return VK_UP;
    if (stricmp(keyname.c_str(), "RIGHT") == 0) return VK_RIGHT;
    if (stricmp(keyname.c_str(), "DOWN") == 0) return VK_DOWN;
    if (stricmp(keyname.c_str(), "A") == 0) return VK_A;
    if (stricmp(keyname.c_str(), "B") == 0) return VK_B;
    if (stricmp(keyname.c_str(), "C") == 0) return VK_C;
    if (stricmp(keyname.c_str(), "D") == 0) return VK_D;
    if (stricmp(keyname.c_str(), "E") == 0) return VK_E;
    if (stricmp(keyname.c_str(), "F") == 0) return VK_F;
    if (stricmp(keyname.c_str(), "G") == 0) return VK_G;
    if (stricmp(keyname.c_str(), "H") == 0) return VK_H;
    if (stricmp(keyname.c_str(), "I") == 0) return VK_I;
    if (stricmp(keyname.c_str(), "J") == 0) return VK_J;
    if (stricmp(keyname.c_str(), "K") == 0) return VK_K;
    if (stricmp(keyname.c_str(), "L") == 0) return VK_L;
    if (stricmp(keyname.c_str(), "M") == 0) return VK_M;
    if (stricmp(keyname.c_str(), "N") == 0) return VK_N;
    if (stricmp(keyname.c_str(), "O") == 0) return VK_O;
    if (stricmp(keyname.c_str(), "P") == 0) return VK_P;
    if (stricmp(keyname.c_str(), "Q") == 0) return VK_Q;
    if (stricmp(keyname.c_str(), "R") == 0) return VK_R;
    if (stricmp(keyname.c_str(), "S") == 0) return VK_S;
    if (stricmp(keyname.c_str(), "T") == 0) return VK_T;
    if (stricmp(keyname.c_str(), "U") == 0) return VK_U;
    if (stricmp(keyname.c_str(), "V") == 0) return VK_V;
    if (stricmp(keyname.c_str(), "W") == 0) return VK_W;
    if (stricmp(keyname.c_str(), "X") == 0) return VK_X;
    if (stricmp(keyname.c_str(), "Y") == 0) return VK_Y;
    if (stricmp(keyname.c_str(), "Z") == 0) return VK_Z;
    if (stricmp(keyname.c_str(), "LSHIFT") == 0) return VK_LSHIFT;
    if (stricmp(keyname.c_str(), "RSHIFT") == 0) return VK_RSHIFT;
    if (stricmp(keyname.c_str(), "LCTRL") == 0) return VK_LCONTROL;
    if (stricmp(keyname.c_str(), "RCTRL") == 0) return VK_RCONTROL;
    if (stricmp(keyname.c_str(), "ENTER") == 0) return VK_RETURN;
    if (stricmp(keyname.c_str(), "BACKSPACE") == 0) return VK_BACK;
    if (stricmp(keyname.c_str(), "TAB") == 0) return VK_TAB;
    if (stricmp(keyname.c_str(), "SHIFT") == 0) return VK_SHIFT;
    if (stricmp(keyname.c_str(), "LWIN") == 0) return VK_LWIN;
    if (stricmp(keyname.c_str(), "RWIN") == 0) return VK_RWIN;
    if (stricmp(keyname.c_str(), "NUMPAD0") == 0) return VK_NUMPAD0;
    if (stricmp(keyname.c_str(), "NUMPAD1") == 0) return VK_NUMPAD1;
    if (stricmp(keyname.c_str(), "NUMPAD2") == 0) return VK_NUMPAD2;
    if (stricmp(keyname.c_str(), "NUMPAD3") == 0) return VK_NUMPAD3;
    if (stricmp(keyname.c_str(), "NUMPAD4") == 0) return VK_NUMPAD4;
    if (stricmp(keyname.c_str(), "NUMPAD5") == 0) return VK_NUMPAD5;
    if (stricmp(keyname.c_str(), "NUMPAD6") == 0) return VK_NUMPAD6;
    if (stricmp(keyname.c_str(), "NUMPAD7") == 0) return VK_NUMPAD7;
    if (stricmp(keyname.c_str(), "NUMPAD8") == 0) return VK_NUMPAD8;
    if (stricmp(keyname.c_str(), "NUMPAD9") == 0) return VK_NUMPAD9;
    if (stricmp(keyname.c_str(), "MULTIPLY") == 0) return VK_MULTIPLY;
    if (stricmp(keyname.c_str(), "ADD") == 0) return VK_ADD;
    if (stricmp(keyname.c_str(), "SUBTRACT") == 0) return VK_SUBTRACT;
    if (stricmp(keyname.c_str(), "DECIMAL") == 0) return VK_DECIMAL;
    if (stricmp(keyname.c_str(), "DIVIDE") == 0) return VK_DIVIDE;
    if (stricmp(keyname.c_str(), "NUMLOCK") == 0) return VK_NUMLOCK;
    if (stricmp(keyname.c_str(), "F1") == 0) return VK_F1;
    if (stricmp(keyname.c_str(), "F2") == 0) return VK_F2;
    if (stricmp(keyname.c_str(), "F3") == 0) return VK_F3;
    if (stricmp(keyname.c_str(), "F4") == 0) return VK_F4;
    if (stricmp(keyname.c_str(), "F5") == 0) return VK_F5;
    if (stricmp(keyname.c_str(), "F6") == 0) return VK_F6;
    if (stricmp(keyname.c_str(), "F7") == 0) return VK_F7;
    if (stricmp(keyname.c_str(), "F8") == 0) return VK_F8;
    if (stricmp(keyname.c_str(), "F9") == 0) return VK_F9;
    if (stricmp(keyname.c_str(), "F10") == 0) return VK_F10;
    if (stricmp(keyname.c_str(), "F11") == 0) return VK_F11;
    if (stricmp(keyname.c_str(), "F12") == 0) return VK_F12;
    if (stricmp(keyname.c_str(), "ALT") == 0) return VK_MENU;
    if (stricmp(keyname.c_str(), "LALT") == 0) return VK_LMENU;
    if (stricmp(keyname.c_str(), "RALT") == 0) return VK_RMENU;
    if (stricmp(keyname.c_str(), "CAPSLOCK") == 0) return VK_CAPITAL;
    if (stricmp(keyname.c_str(), "ESC") == 0) return VK_ESCAPE;
    if (stricmp(keyname.c_str(), "SPACE") == 0) return VK_SPACE;
    if (stricmp(keyname.c_str(), "PAGEUP") == 0) return VK_PRIOR;
    if (stricmp(keyname.c_str(), "PAGEDOWN") == 0) return VK_NEXT;
    if (stricmp(keyname.c_str(), "END") == 0) return VK_END;
    if (stricmp(keyname.c_str(), "HOME") == 0) return VK_HOME;
    if (stricmp(keyname.c_str(), "INSERT") == 0) return VK_INSERT;
    if (stricmp(keyname.c_str(), "DELETE") == 0) return VK_DELETE;
    if (stricmp(keyname.c_str(), "SELECT") == 0) return VK_SELECT;
    if (stricmp(keyname.c_str(), "SNAPSHOT") == 0) return VK_SNAPSHOT;
    if (stricmp(keyname.c_str(), "HELP") == 0) return VK_HELP;
    if (stricmp(keyname.c_str(), "F13") == 0) return VK_F13;
    if (stricmp(keyname.c_str(), "F14") == 0) return VK_F14;
    if (stricmp(keyname.c_str(), "F15") == 0) return VK_F15;
    if (stricmp(keyname.c_str(), "F16") == 0) return VK_F16;
    if (stricmp(keyname.c_str(), "F17") == 0) return VK_F17;
    if (stricmp(keyname.c_str(), "F18") == 0) return VK_F18;
    if (stricmp(keyname.c_str(), "F19") == 0) return VK_F19;
    if (stricmp(keyname.c_str(), "F20") == 0) return VK_F20;
    if (stricmp(keyname.c_str(), "F21") == 0) return VK_F21;
    if (stricmp(keyname.c_str(), "F22") == 0) return VK_F22;
    if (stricmp(keyname.c_str(), "F23") == 0) return VK_F23;
    if (stricmp(keyname.c_str(), "F24") == 0) return VK_F24;
    if (stricmp(keyname.c_str(), "CTRL") == 0) return VK_CONTROL;
    if (stricmp(keyname.c_str(), "PLAY") == 0) return VK_PLAY;
    if (stricmp(keyname.c_str(), "ZOOM") == 0) return VK_ZOOM;
    if (stricmp(keyname.c_str(), "SCROLL") == 0) return VK_SCROLL;
    return 0;
}

bool InputAgent::isExtKey(int vkcode)
{
    if (
        vkcode == VK_RETURN ||
        vkcode == VK_LEFT ||
        vkcode == VK_RIGHT ||
        vkcode == VK_UP ||
        vkcode == VK_DOWN ||
        vkcode == VK_NUMLOCK ||
        vkcode == VK_DIVIDE ||
        vkcode == VK_RCONTROL ||
        vkcode == VK_RMENU ||
        vkcode == VK_LWIN ||
        vkcode == VK_RWIN ||
        vkcode == VK_INSERT ||
        vkcode == VK_DELETE ||
        vkcode == VK_HOME ||
        vkcode == VK_END ||
        vkcode == VK_PRIOR ||
        vkcode == VK_NEXT
        )
    {
        return true;
    }
    else
        return false;
}


void InputAgent::KeyPress(int caller_lpdkey, std::string keyname)
{
    int vkcode = parseKeyname(keyname);
    KeyDown(vkcode);
    Sleep(20);
    KeyUp(vkcode); 
    Sleep(500);         // threshold
    while (PadStatus[caller_lpdkey] == 1)
    {
        KeyDown(vkcode);
        Sleep(20);
        KeyUp(vkcode);
        Sleep(20);
    }
}


void InputAgent::KeyUp(int vkcode)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_KEYBOARD;
    lpinput->ki.wScan = MapVirtualKey(vkcode, MAPVK_VK_TO_VSC);
    lpinput->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP | (isExtKey(vkcode) ? KEYEVENTF_EXTENDEDKEY : 0) ;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::KeyUp(std::string keyname)
{
    KeyUp(parseKeyname(keyname));
}

void InputAgent::KeyDown(int vkcode)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_KEYBOARD;
    lpinput->ki.wScan = MapVirtualKey(vkcode, MAPVK_VK_TO_VSC);
    lpinput->ki.dwFlags = KEYEVENTF_SCANCODE | (isExtKey(vkcode) ? KEYEVENTF_EXTENDEDKEY : 0);
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::KeyDown(std::string keyname)
{
    KeyDown(parseKeyname(keyname));
}



void InputAgent::MouseLeftClick()
{
    MouseLeftDown();
    Sleep(30);
    MouseLeftUp();
}

void InputAgent::MouseLeftDown()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseLeftUp()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseRightClick()
{
    MouseRightDown();
    Sleep(30);
    MouseRightUp();
}

void InputAgent::MouseRightDown()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseRightUp()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseMiddleClick()
{
    MouseMiddleDown();
    Sleep(30);
    MouseMiddleUp();
}

void InputAgent::MouseMiddleDown()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseMiddleUp()
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    SendInput(1, lpinput, sizeof(INPUT));
}



void InputAgent::MouseLeftClick(int x, int y)
{
    MouseLeftDown(x, y);
    Sleep(30);
    MouseLeftUp(x, y);
}

void InputAgent::MouseLeftDown(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseLeftUp(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseRightClick(int x, int y)
{
    MouseRightDown(x, y);
    Sleep(30);
    MouseRightUp(x, y);
}

void InputAgent::MouseRightDown(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseRightUp(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTUP;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseMiddleClick(int x, int y)
{
    MouseMiddleDown(x, y);
    Sleep(30);
    MouseMiddleUp(x, y);
}

void InputAgent::MouseMiddleDown(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_MIDDLEDOWN;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseMiddleUp(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_MIDDLEUP;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseMove(int x, int y)
{
    LPINPUT lpinput = new INPUT;
    memset(lpinput, 0, 1 * sizeof(INPUT));
    lpinput->type = INPUT_MOUSE;
    lpinput->mi.dx = x*(65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
    lpinput->mi.dy = y*(65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
    lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    SendInput(1, lpinput, sizeof(INPUT));
}

void InputAgent::MouseShift(int caller_lpdkey, int x, int y)
{
    do {
        LPINPUT lpinput = new INPUT;
        LPPOINT lpp = new POINT;
        memset(lpinput, 0, 1 * sizeof(INPUT));
        GetCursorPos(lpp);
        lpinput->type = INPUT_MOUSE;
        lpinput->mi.dx = (lpp->x + x) * (65536.0f / (GetSystemMetrics(SM_CXSCREEN)-1));
        lpinput->mi.dy = (lpp->y - y) * (65536.0f / (GetSystemMetrics(SM_CYSCREEN)-1));
        lpinput->mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        SendInput(1, lpinput, sizeof(INPUT));
        Sleep(5);

    } while (PadStatus[caller_lpdkey] == 1);
}

