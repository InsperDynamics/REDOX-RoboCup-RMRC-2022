#pragma once
#include <iostream>
#include <SDL.h>
using namespace std;
static SDL_Joystick* gGameController = NULL;
static SDL_Event sdl_event;
static const int JOYSTICK_DEAD_ZONE = 8000;
static int xDir = 0;
static int yDir = 0;

void InitializeGamepad()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if (SDL_NumJoysticks() < 1)
    {
        cout << "Warning: No joysticks connected!\n";
    }
    else
    {
        gGameController = SDL_JoystickOpen(0);
    }
}

void UpdateGamepad()
{
    while (SDL_PollEvent(&sdl_event) != 0)
    {
        if (sdl_event.type == SDL_JOYAXISMOTION)
        {
			if (sdl_event.jaxis.axis == 0)
			{
				if (sdl_event.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					xDir = -1;
				}
				else if (sdl_event.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					xDir = 1;
				}
				else
				{
					xDir = 0;
				}
			}
			else if (sdl_event.jaxis.axis == 1)
			{
				if (sdl_event.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					yDir = -1;
				}
				else if (sdl_event.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					yDir = 1;
				}
				else
				{
					yDir = 0;
				}
			}
        }
    }
	cout << xDir << yDir << "\n";
}