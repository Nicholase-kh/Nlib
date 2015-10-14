#include <SDL2/SDL.h>

#include "timer.h"

void timer::Start()
{
	_start = true;
	_pause = false;
	_TimerStart = SDL_GetTicks();
}

int timer::Stop()
{
	int time = Time();
	_start = false;
	_pause = false;
	return time;
}

void timer::Pause()
{
	if (_start && !_pause )
	{
		_pause = true;
		_TimerPause = SDL_GetTicks() - _TimerStart;
	}
}

void timer::Continue()
{
	if (_pause)
	{
		_pause = false;
		_TimerStart = SDL_GetTicks() - _TimerPause;
		_TimerPause = 0;
	}
}

int timer::Time() const
{
	if (_start)
		if (_pause)
			return _TimerPause;
		else
			return SDL_GetTicks() - _TimerStart;
	return 0;
}

bool timer::IsPause() const
{
	return _pause;
}

bool timer::IsStart() const
{
	return _start;
}