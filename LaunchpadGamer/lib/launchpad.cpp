//
// Lightpad - Helpers.cpp
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha, Origami1105, WhoovesPON3.
// Additional support from LaunchpadFun (http://www.launchpadfun.com/en/).
// https://www.nightwave.co/lightpad
//

#include <algorithm>
#include <thread>
#include <cmath>
#include "rtmidi/RtMidi.h"
#include "midifile/MidiFile.h"
#include <windows.h>
#include "mapper.h"
//#include "launchpad.h"


// Generate with GenerateNoteButtonMap.cpp
const int note_button_map[] = {
	91, 92, 93, 94, 95, 96, 97, 98, 11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34, 41, 42, 43, 44,
	51, 52, 53, 54, 61, 62, 63, 64, 71, 72, 73, 74, 81, 82, 83, 84, 15, 16, 17, 18, 25, 26, 27, 28,
	35, 36, 37, 38, 45, 46, 47, 48, 55, 56, 57, 58, 65, 66, 67, 68, 75, 76, 77, 78, 85, 86, 87, 88,
	89, 79, 69, 59, 49, 39, 29, 19, 80, 70, 60, 50, 40, 30, 20, 10, 1, 2, 3, 4, 5, 6, 7, 8
};
const int note_button_offset = 28;
const int note_button_size = sizeof(note_button_map) / sizeof(int);
// End generate block


// Note<>Button conversion
int note_to_button(int note) {
	if (note < note_button_offset || note > (note_button_size + note_button_offset)) return 0;
	return note_button_map[note - note_button_offset];
}

int button_to_note(int button) {
	for (int i = 0; i < note_button_size + note_button_offset; i++)
		if (note_button_map[i] == button) return i + note_button_offset;
	return 0;
}

LaunchpadBase::LaunchpadBase() 
{
	midiin = new RtMidiIn();
	midiout = new RtMidiOut();
}

int LaunchpadBase::connect() {
	connected = false;

	inport = getMidiPort(INPORT_NAME, midiin);
	outport = getMidiPort(OUTPORT_NAME, midiout);

	if ((inport == -1) || (outport == -1)) {
		delete midiin;
		delete midiout;
		return -1;
	}

	// Open (Pro) Standalone port.
	midiin->openPort(inport);
	midiout->openPort(outport);

	// Don't ignore sysex, timing, or active sensing messages.
	midiin->ignoreTypes(false, false, false);

	connected = true;
	return 0;
}

void LaunchpadBase::disconnect() {
	if (connected) {
		connected = false;
		delete midiin;
		delete midiout;
	}
}

bool LaunchpadBase::isConnected() {
	return connected;
}

int LaunchpadBase::getMidiPort(std::string name, RtMidi *ports) {
	for ( unsigned int i = 0; i < ports->getPortCount(); i++ ) {
		try {
			if (ports->getPortName(i).find(name) != string::npos  && ports->getPortName(i).find(PRODUCT_NAME) != string::npos) {
				return i;
			}
		} catch (RtMidiError &error) {
			error.printMessage();
			return -1;
		}
	}

	return -1;
}

double LaunchpadBase::getMessage(std::vector<BYTE> *message_in) {
	if (isConnected() == false) return -1;
	return midiin->getMessage(message_in);
}

void LaunchpadBase::sendMessage(unsigned int first_byte, ...) {
	if (isConnected() == false) return;
	va_list varlist;
	va_start(varlist, first_byte);
	unsigned int byte = first_byte;
	while (byte != SYSEX_FIN && byte >= 0 && byte <= 255) {
		message.push_back(byte);
		byte = va_arg(varlist, unsigned int);
	}
    if (byte >= 0 && byte <= 255) message.push_back(byte);
	va_end(varlist);

	midiout->sendMessage(&message);
	message.erase(message.begin(), message.begin() + message.size());
}

void LaunchpadBase::setColor(BYTE key, BYTE color) {
	if (isConnected() == false) return;

}

void LaunchpadBase::setPulse(BYTE key, BYTE color) {
	if (isConnected() == false) return;

}

LaunchpadPro::LaunchpadPro() {
	#ifdef _WIN32
	INPORT_NAME = "MIDIIN2";
	OUTPORT_NAME = "MIDIOUT2";
    PRODUCT_NAME = "Launchpad Pro";
	#else
	INPORT_NAME = "Launchpad Pro Standalone Port";
	OUTPORT_NAME = "Launchpad Pro Standalone Port";
    PRODUCT_NAME = "Launchpad Pro";
	#endif
}

int LaunchpadPro::connect() {
	int status = LaunchpadBase::connect();
	if (status == 0) {
		std::vector<unsigned char> device_info;

		// Inquiry Device
		sendMessage( 240, 126, 127, 6, 1, 247 );
		while (device_info.size() == 0) {
			getMessage(&device_info);
			Sleep( 10 ); // Sleep for 10 milliseconds ... platform-dependent.
		}

		sendMessage( 240, 0, 32, 41, 2, 16, 33, 1, SYSEX_FIN); // Set to Standalone Mode
		sendMessage( 240, 0, 32, 41, 2, 16, 44, 3, SYSEX_FIN); // Set to Programmer Mode
	}
	return status;
}

void LaunchpadPro::disconnect() {
	sendMessage( 240, 0, 32, 41, 2, 16, 14, 0, SYSEX_FIN); // Clear all LED colors
	sendMessage( 240, 0, 32, 41, 2, 16, 44, 0, SYSEX_FIN); // Set to Note Mode
	LaunchpadBase::disconnect();
}

bool LaunchpadPro::isConnected() {
	return LaunchpadBase::isConnected();
}

void LaunchpadPro::setColor(BYTE key, BYTE color) {
	if (isConnected() == false) return;
    BYTE keytype = (isButton(key) ? 0xB0 : 0x90) + channel;
    sendMessage(keytype, key, color, MSG_FIN);
}

void LaunchpadPro::setColor(BYTE  key,
                            BYTE  red, BYTE  green, BYTE  blue) {
	if (isConnected() == false) return;
	sendMessage( 240, 0, 32, 41, 2, 16, 11, key, red, green, blue, SYSEX_FIN );
}

void LaunchpadPro::setColor(int row, int col, int color)
{
    if (isConnected() == false) return;
    BYTE key = 10 * row + col;
    BYTE keytype = (isButton(row, col) ? 0xB0 : 0x90) + channel;
    sendMessage(keytype, key, color, MSG_FIN);
}

void LaunchpadPro::setColumnColor(int col, int color)
{
    if (isConnected() == false) return;
    for (int i = 0; i <= 9; i++)
    {
        setColor(i, col, color);
    }
    return;
}

void LaunchpadPro::setRowColor(int row, int color)
{
    if (isConnected() == false) return;
    for (int i = 0; i <= 9; i++)
    {
        setColor(row, i, color);
    }
}

void LaunchpadPro::stopDisplayText()
{
    if (isConnected() == false) return;
    sendMessage(240, 0, 32, 41, 2, 16, 20, SYSEX_FIN);
}

void LaunchpadPro::setPadColor(int color)
{
    if (isConnected() == false) return;
    sendMessage(240, 0, 32, 41, 2, 16, 14, color, SYSEX_FIN);
}

void LaunchpadPro::clearPad()
{
    if (isConnected() == false) return;
    stopDisplayText();
    sendMessage(240, 0, 32, 41, 2, 16, 14, 0, SYSEX_FIN);
}

void LaunchpadPro::setFlash(BYTE  key, BYTE  color) {
	if (isConnected() == false) return;
	sendMessage( 240, 0, 32, 41, 2, 16, 35, key, color, SYSEX_FIN);
}
void LaunchpadPro::setFlash(int row, int col, BYTE  color) {
    if (isConnected() == false) return;
    BYTE key = 10 * row + col;
    sendMessage(240, 0, 32, 41, 2, 16, 35, key, color, SYSEX_FIN);
}


void LaunchpadPro::setPulse(BYTE  key, BYTE  color) {
	if (isConnected() == false) return;
	sendMessage( 240, 0, 32, 41, 2, 16, 40, key, color, SYSEX_FIN);
}
void LaunchpadPro::setPulse(int row, int col, BYTE  color) {
    if (isConnected() == false) return;
    BYTE key = 10 * row + col;
    sendMessage(240, 0, 32, 41, 2, 16, 40, key, color, SYSEX_FIN);
}

void LaunchpadPro::displayText(unsigned int color, unsigned int speed,
                               std::string text) {
	if (isConnected() == false) return;
	message.push_back(240);
	message.push_back(0);
	message.push_back(32);
	message.push_back(41);
	message.push_back(2);
	message.push_back(16);
	message.push_back(40);
	message.push_back(color);
	message.push_back(speed);
	for (int i = 0; i < text.size(); ++i) message.push_back(text[i]);
	message.push_back(247);

	midiout->sendMessage(&message);
	message.erase(message.begin(), message.begin() + message.size());
}

void LaunchpadPro::playMidiFile(std::string file) {
    MidiFile midifile;
    MidiEvent *mev;
    std::vector<unsigned char> message;
    int keytype, key, note, color, deltatick;
    midifile.read(file);
    midifile.joinTracks();
    int BPM = midifile.getTicksPerQuarterNote();
    for (int event = 0; event < midifile[0].size(); event++)
    {
        mev = &midifile[0][event];
        keytype = (int)(*mev)[0];
        note = (int)(*mev)[1];
        color = (int)(*mev)[2];
        if (event == 0) deltatick = mev->tick;
        else deltatick = mev->tick - midifile[0][event - 1].tick;
        if (keytype == 0x80 || keytype == 0x90)
        {
            if (keytype == 0x80) color = 0;
            if (deltatick > 0) Sleep(60000 / (BPM * deltatick));
            key = note_to_button(note);
            setColor(key, color);
        }
    }
}

void LaunchpadPro::setupMapper(std::string mapgame)
{
    game_to_map = mapgame;

    std::vector<BYTE> msg;
    MidiParser midiparser(this, game_to_map);

    while (true)
    {
        getMessage(&msg);
        if (msg.size() != 0)
        {
            midiparser.parseMsg(msg);
        }
        Sleep(30);
    }
}



bool LaunchpadPro::isButton(int row , int col)
{
    if ((row == 0 || row == 9) && (col >= 1 && col <= 8))
        return true;
    else
        return false;
}

bool LaunchpadPro::isKey(int row, int col)
{
    return !isButton(row, col);
}

bool LaunchpadPro::isButton(int code)
{
    return !isKey(code);
}

bool LaunchpadPro::isKey(int code)
{
    int a = code / 10, b = code % 10;
    if ((a >= 1 && a <= 8) && (b >= 1 && b <= 8))
        return true;
    else
        return false;
}

LaunchpadS::LaunchpadS() {
	#ifdef WINDOWS // May not be accurate!
	INPORT_NAME = "Launchpad S";
	OUTPORT_NAME = "Launchpad S";
    PRODUCT_NAME = "Launchpad S";
	#else
	INPORT_NAME = "Launchpad S";
	OUTPORT_NAME = "Launchpad S";
    PRODUCT_NAME = "Launchpad S";
	#endif
}

int LaunchpadS::connect() {
	int status = LaunchpadBase::connect();

	if (status == 0) {
		std::vector<unsigned char> device_info;

		// Inquiry Device
		sendMessage( 240, 126, 127, 6, 1, 247 );
		while (device_info.size() == 0) {
			getMessage(&device_info);
			Sleep( 10 ); // Sleep for 10 milliseconds ... platform-dependent.
		}

		sendMessage( 176, 0, 2, MSG_FIN ); // Set to Drum Rack Mode
	}
	return status;
}

void LaunchpadS::disconnect() {
	sendMessage( 176, 0, 0, MSG_FIN); // Reset
	LaunchpadBase::disconnect();
}

bool LaunchpadS::isConnected() {
	return LaunchpadBase::isConnected();
}

unsigned char LaunchpadS::pro_to_s_note(unsigned char pro_note, unsigned char msg_type) {
	if (msg_type == 176) return pro_note;
	return pro_note;
}

unsigned char LaunchpadS::pro_to_s_color(unsigned char pro_color) {
	return pro_color;
}

void LaunchpadS::setColor(unsigned char light, unsigned char color) {
	if (isConnected() == false) return;
	message.push_back(144);
	message.push_back(pro_to_s_note(light, 144 /*msg_type*/));
	message.push_back(color);

	midiout->sendMessage(&message);
	message.erase(message.begin(), message.begin() + message.size());
}

void LaunchpadS::setPulse(unsigned char light, unsigned char color) {
	if (isConnected() == false) return;
	// XXX Implement me!
}
