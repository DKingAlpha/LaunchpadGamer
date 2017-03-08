//
// Lightpad - Helpers.h
// ©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha, Origami1105, WhoovesPON3.
// Additional support from LaunchpadFun (http://www.launchpadfun.com/en/).
// https://www.nightwave.co/lightpad
//

#include <windows.h>
#include "./rtmidi/RtMidi.h"



int note_to_button(int note);
int button_to_note(int button);

class LaunchpadBase {
	public:
		LaunchpadBase();
		int connect();
		void disconnect();
		bool isConnected();
		int getMidiPort(std::string name, RtMidi *ports);
		double getMessage(std::vector<unsigned char> *message_in);
        void sendMessage(unsigned int first_byte, ...);
		virtual void setColor(unsigned char light, unsigned char color);
		virtual void setPulse(unsigned char light, unsigned char color);
		std::string INPORT_NAME;
		std::string OUTPORT_NAME;
        std::string PRODUCT_NAME;
        int channel = 0;
	protected:
		RtMidiIn *midiin;
		RtMidiOut *midiout;
		int inport;
		int outport;
		std::vector<unsigned char> message;
		bool connected;
};

class LaunchpadPro : public LaunchpadBase {
	public:
		LaunchpadPro();
		int connect();
		void disconnect();
		bool isConnected();
		void setColor(BYTE key, BYTE color);
		void setColor(BYTE key, BYTE red, BYTE green, BYTE blue);
        void setColor(int row, int col, int color);
        void setRowColor(int row, int color);
        void setColumnColor(int col, int color);
        void stopDisplayText();
        void setPadColor(int color);
        void clearPad();
		void setFlash(BYTE key, BYTE color);
		void setPulse(BYTE key, BYTE color);
		void displayText(unsigned int color, unsigned int speed, std::string text);
        void playMidiFile(std::string mapgame);
        void setupMapper(std::string mapgame);

    private:
        bool isButton(int row, int col);
        bool isKey(int row, int col);
        bool isButton(int code);
        bool isKey(int code);
        void maproutine(void);
        std::string game_to_map;

};

class LaunchpadS : public LaunchpadBase {
	public:
		LaunchpadS();
		int connect();
		void disconnect();
		bool isConnected();
		void setColor(unsigned char light, unsigned char color);
		void setPulse(unsigned char light, unsigned char color);
		unsigned char pro_to_s_note(unsigned char pro_note, unsigned char msg_type);
		unsigned char pro_to_s_color(unsigned char pro_color);
};

