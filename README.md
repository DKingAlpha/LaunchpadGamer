# Launchpad Gamer makes your Launchpad never cooler and funnier than ever before!

## What does it Do:
Launchpad Gamer provides a grant acccess to control launchpad behavior, within only one or two config files.
To reach this goal, Launchpad Gamer provides an interface where you can combine varieties of public method by writing them in to one or two config files, then load them in. Your launchpad will react as your every line configured in text.

## FEEL FREE TO SUBMIT YOUR PR ! 
* Your Config Set in a situation (a game,a software,...)
* Bug Fix
* Optimizition
* More Device Support

### Your devotion helps to exploit the best Launchpad !


## Support:
* Customizing Keyboard/Moust Mapping with a config file
* Control Cursor Movement Speed by your tap velocity !
* Customizing Light Effect / Midi File with a config file
* Easy & Combinable & Abbreviatable  Config Rule !


## Notice:
* The Project is currently only tested based on `Launchpad Pro`.


## Enhencement:
* Config Parser Compatibility


## Progress:
* Launchpad Interface                        Done
* Light Control config grammer               Done
* Light Control config parser                Done
* Key Mapper config grammer                  Done
* Key Mapper config parser                   Done
* Key Simulator control Interface            Done
* Sound/Music Support                        Undecided
* GUI                                        Undecided

`If you really need these, issue please.`



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
* Rule 7: () is neccessary , even it's no argument.
* Rule 8: Velocity needs to be enabled in Launchpad Pro
* `THAT'S ALL ABOUT IT !`


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

