#ifndef _TIMER_H
#define _TIMER_H

#include <SDL2/SDL.h>

class timer {
public:
	//Start & Stop  Pause & Continue
	void Start();
	int Stop();
	void Pause();
	void Continue();
	//clock
	int Time() const;
	//state
	bool IsPause() const;
	bool IsStart() const;
private:
	bool _start = false;
	bool _pause = false;
	int _TimerStart = 0;
	int _TimerPause = 0;
};

#endif