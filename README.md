### This project provides an acccess to control launchpad behavior with one or two config files,
### which supports powerful functions , highly customizable , with easy grammer.

#### FEEL FREE TO SUBMIT A PR ! Your Config Set or Code helps to exploit the real Launchpad !

## Support:
* Customizing Keyboard/Moust Mapping with config a file
* Control Cursor Movement Speed by your tap velocity !
* Customizing Light Effect / Midi File with config a file
* Easy & Combinable & Abbreviatable  Config Rule !


### Notice:
* The Project is currently tested on a Launchpad Pro.
* No real support for other Launchpad device.


### Progress:
* Launchpad Interface                        Done
* Light Control config grammer               Done
* Light Control config parser                Done
* Key Mapper config grammer                  Done
* Key Mapper config parser                   Done
* Key Simulator control Interface            Done
* Sound/Music Support                        Undecided


#### Config files should be put at config/$CONFSET/
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


###   KEY     EVENT         ACTIONS
*   key     event        action1;action2;action3;...

### KEY
* row,col
* keycode

### EVENT
* KEYAUTO
* KEYDOWN
* KEYUP


###    ACTION
* PlayMidiFile(filepath)
* SetColor(key1,color1|row2,col2,color2|...)
* SetRowColor(row1,color1|row2,color2|...)
* SetColumnColor(col1,color1|col2,color2)
* SetPadColor(color1)
* SetFlash(key1,color1|row2,col2,color2|...)
* SetPulse(key1,color1|row2,col2,color2|...)
* DisplayText(color,speed,text)
* ClearPad()
* StopDisplayText()
* SendMessage(dec1,dec2,dec3,...)
* Sleep(milisecond)

### KEYAUTO SPECIAL    ( AutoMap Down/Up Event )
* MouseLeft(x1,y1)
* MouseRight(x1,y1)
* MouseMiddle(x1,y1)
* MouseShift(x1,y2)      # auto repeat    # recommend  -40~40   # offset=+AUTO or offset=-AUTO to move mouse by your velocity !
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

