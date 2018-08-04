# Warning:
Deprecated

This tool is a console-based Launchpad Controller. Please refer to the newer project [ControllerGamer](https://github.com/DKingCN/ControllerGamer) with GUI designed.

`bug in parsing config file is not fixed yet.`


## What does it Do:
Launchpad Gamer provides a grant acccess to control launchpad behavior, within only one or two config files.
To reach this goal, Launchpad Gamer provides an interface where you can combine varieties of public method by writing them in to one or two config files, then load them in. Your launchpad will react as your every line configured in text.


## Usage Examples
Add in config/confset/*.ini
```
# Mouse Smooth Move
3,6  KEYAUTO  MouseShift(-AUTO,+AUTO)
3,7  KEYAUTO  MouseShift(0,+AUTO)
3,8  KEYAUTO  MouseShift(+AUTO,+AUTO)
2,6  KEYAUTO  MouseShift(-AUTO,0)
2,7  KEYAUTO  MouseLeft()
2,8  KEYAUTO  MouseShift(+AUTO,0)
1,6  KEYAUTO  MouseShift(-AUTO,-AUTO)
1,7  KEYAUTO  MouseShift(0,-AUTO)
1,8  KEYAUTO  MouseShift(+AUTO,-AUTO)


* Mouse Shift Light
3,6  KEYAUTO  SetColor(3,6,45);Sleep(25);SetColor(4,5,45);Sleep(25);SetColor(5,4,45);Sleep(25);SetColor(6,3,45);Sleep(25);SetColor(7,2,45);Sleep(25);SetColor(8,1,45)
3,7  KEYAUTO  SetColor(3,7,45);Sleep(25);SetColor(4,7,45);Sleep(25);SetColor(5,7,45);Sleep(25);SetColor(6,7,45);Sleep(25);SetColor(7,7,45);Sleep(25);SetColor(8,7,45)
3,8  KEYAUTO  SetColor(3,8,45)
2,6  KEYAUTO  SetColor(2,6,45);Sleep(25);SetColor(2,5,45);Sleep(25);SetColor(2,4,45);Sleep(25);SetColor(2,3,45);Sleep(25);SetColor(2,2,45);Sleep(25);SetColor(2,1,45)
2,7  KEYAUTO  SetColor(3,6,40);SetColor(3,8,40);SetColor(1,6,40);SetColor(1,8,40);SetRowColor(2,45);SetColumnColor(7,45);
2,8  KEYAUTO  SetColor(2,8,45)
1,6  KEYAUTO  SetColor(1,6,45)
1,7  KEYAUTO  SetColor(1,7,45)
1,8  KEYAUTO  SetColor(1,8,45)
```
Save and Run !

## FEEL FREE TO SUBMIT YOUR PR
* Your Config Set in a situation (a game,a software,...)
* Bug Fix
* Optimizition
* More Device Support

## Support:
* Customizing Keyboard/Moust Mapping with a config file
* Control Cursor Movement Speed by your tap velocity !
* Customizing Light Effect / Midi File with a config file
* Easy & Combinable & Abbreviatable  Config Rule !


## Notice:
* The Project is currently only tested on `Launchpad Pro`.


## HELP INFO

### Config files should be put at config/$CONFSET/
Then be load in test.cpp main() as lpd->loadConfig(CONFSET);

Light mapping file should be named as light.ini
Key mapping file should be named as keymap.ini

### Please Read config example

* Rule 1: No Nesting. 
* RUle 2: Sequenced actions are accepted, divided by `;`. Last `;` is NOT neccessary.
* Rule 3: No Space within one parameter.
* Rule 4: Some Arguments can be write in one Action, divided by `|`
* Rule 5: Some Actions are restricted with EVENT.
* Rule 6: Be careful with KEYAUTO.
* Rule 7: () is neccessary , even it has no arguments.
* Rule 8: Velocity needs to be enabled in Launchpad Pro


### Config Item Pattern

    KEY       EVENT           ACTIONS
    
    key     event        action1;action2;action3;...

### KEY
* row,col
* keycode

### EVENT
* KEYAUTO
* KEYDOWN
* KEYUP


### ACTION
* PlayMidiFile(filepath)
* SetColor(key1,color1|row2,col2,color2|...)
* SetRowColor(row1,color1|row2,color2|...)
* SetColumnColor(col1,color1|col2,color2)
* SetPadColor(color1)
* SetFlash(key1,color1|row2,col2,color2|...)
* SetPulse(key1,color1|row2,col2,color2|...)
* DisplayText(color,loop,speed,text)         # speed=1-7  # loop = 1/0  # ONLY USED IN KEYDOWN/KEYUP
* DisplayText(color,speed,text)              # ONLY USED IN KEYAUTO
* ClearPad()
* StopDisplayText()
* SendMessage(dec1,dec2,dec3,...)
* Sleep(milisecond)

### KEYAUTO SPECIAL    ( AutoMap Down/Up Event )
* MouseLeft(x1,y1)
* MouseRight(x1,y1)
* MouseMiddle(x1,y1)
* MouseShift(x1,y2)      # auto repeat    # recommend  -40~40   # offset=+AUTO or offset=-AUTO to move mouse by velocity !
* KeyPress(keyname)     # auto repeat

## KEYUP/KEYDOWN       # Click/Down/Up action support Action() at current position
* MouseLeftClick(x1,y1|x2,y2|...)
* MouseLeftDown(x1,y1|x2,y2|...)
* MouseLeftUp(x1,y1|x2,y2|...)
* MouseRightClick(x1,y1|x2,y2|...)
* MouseRightDown(x1,y1|x2,y2|...)
* MouseRightUp(x1,y1|x2,y2|...)
* MouseMiddleClick(x1,y1|x2,y2|...)
* MouseMiddleDown(x1,y1|x2,y2|...)
* MouseMiddleUp(x1,y1|x2,y2|...)
* MouseMove(x,y)
* MouseShift(offset_x,offset_y);    # recommend  -40~40   # offset=+AUTO or offset=-AUTO to use velocity!
* KeyPress(keyname)                # will not auto repeat 
* KeyDown(keyname)
* KeyUp(keyname)
* Sleep(millisecond)

