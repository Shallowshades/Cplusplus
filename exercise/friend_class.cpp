#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Tv {
public:
	friend class remote;
	enum { off, on };
	enum { MinVal, MaxVal = 20 };
	enum { Antenna, Cable };		//有线 无线 
	enum { TV, DVD };

	Tv(int s = off, int mc = 125) : state(s), volume(5), max_channel(mc), channel(2), mode(Cable), input(TV) {}
	
	void onoff() { state = (state == on) ? off : on; }

	bool ison() const { return state == on; }

	bool volup();

	bool voldown();

	void chanup();

	void chandown();

	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }

	void set_input() { input = (input == TV) ? DVD : TV; }

	void settings() const;	//display all settings

protected:

private:
	int state;			//on or off
	int volume;			//assumed to be digitized
	int max_channel;	//maximum number of channels
	int channel;		//current channel setting
	int mode;			//broadcast or cable
	int input;			//TV or DVD
};

class remote {
public:
	remote(int m = Tv::TV) : mode(m) {}

	bool volup(Tv& t) const { return t.volup(); }

	bool voldown(Tv& t) const { return t.voldown(); }
	
	void onoff(Tv& t) const { t.onoff(); }

	void chanup(Tv& t) const { t.chanup(); }

	void chandown(Tv& t) const { t.chandown(); }

	void set_chan(Tv& t, const int c) const { t.channel = c; }

	void set_mode(Tv& t) const { t.set_mode(); }

	void set_input(Tv& t) const { t.set_mode(); }

private:
	int mode;	//control TV or DVD
};

bool Tv::volup(){
	if (volume < MaxVal) {
		++volume;
		return true;
	}
	return false;
}

bool Tv::voldown(){
	if (volume > MinVal) {
		--volume;
		return true;
	}
	return false;
}

void Tv::chanup() { channel = (channel == MaxVal) ? 1 : channel + 1; }

void Tv::chandown() { channel = (channel == 1) ? MaxVal : channel - 1; }

void Tv::settings() const {
	using std::cout;
	using std::endl;
	cout << "TV is " << (state == off ? "Off" : "On") << endl;
	if (state == on) {
		cout << "Volume setting = " << volume << endl;
		cout << "Channel settings = " << channel << endl;
		cout << "Mode = " << (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
	}
}

int main() {

	Tv s42;
	cout << "Initial settings for 42\"Tv:\n";
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "\nAdjusted settings for 42\"TV:\n";
	s42.settings();

	remote grey;
	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n42\" settings after using remote:\n";
	s42.settings();

	Tv s58(Tv::on);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "\n58\" settings:\n";
	s58.settings();

	return 0;
}