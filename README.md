### This project provides an acccess to control launchpad behavior with one or two config files,
### which supports powerful functions , highly customizable , with easy grammer.


### Progress:
* Launchpad Interface                        Done
* Light Control config grammer               Done
* Light Control config parser                Done
* Key Mapper config grammer                  Done
* Key Mapper config parser                   Ongoing
* Key Simulator control Interface            Need help of a low level implement



#### Config files should be located at config/$CONFSET/
then be load in main() as lpd->setupMapper(CONFSET);
Light mapping file is named as light.ini
Key mapping file is named as keymap.ini


#   KEY     EVENT         ACTIONS
##   key     event        action1;action2;action3;...

## KEY
### row,col
### keycode

## EVENT
### KEYAUTO
### KEYDOWN
### KEYUP

##    ACTION
### PlayMidiFile(filepath)
### SetColor(key1,color1|row2,col2,color2|...)
### SetRowColor(row1,color1|row2,color2|...)
### SetColumnColor(col1,color1|col2,color2)
### SetPadColor(color1)
### SetFlash(key1,color1|row2,col2,color2|...)
### SetPulse(key1,color1|row2,col2,color2|...)
### DisplayText(color,speed,text)
### ClearPad()
### StopDisplayText()
### SendMessage(dec1,dec2,dec3,...)
### Sleep(milisecond)

### BE AWARE THAT SPACE CHARACTOR ARE NOT DEALT WELL SO DO NOT USE SPACE IN MOST CASE.

4,4   KEYDOWN   SetRowColor(2,45|4,45);Sleep(2000);SetRowColor(2,0|4,0);PlayMidiFile(a2.mid)

4,4   KEYDOWN   Sleep(2000);SetRowColor(2,0|4,0);PlayMidiFile(testmidi/a1.mid)

4,7   KEYAUTO   SetRowColor(2,45|4,45)
