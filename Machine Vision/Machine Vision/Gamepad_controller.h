#pragma once
#include <iostream>
#include <SDL.h>
using namespace std;
static SDL_Joystick* gGameController = NULL;
static SDL_Event sdl_event;
static const int JOYSTICK_DEAD_ZONE = 8000;
static const int JOYSTICK_MAXIMUM_ZONE = 32900;
static int xAnalog = 0;
static int yAnalog = 0;
bool image_processing = false;

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

string GamepadCommand()
{
    while (SDL_PollEvent(&sdl_event) != 0)
    {
		if (sdl_event.type == SDL_JOYBUTTONDOWN)
		{
			int buttonId = sdl_event.jbutton.button;
			switch (buttonId)
			{
			case 2:
				return "ExtendArm\n";
				break;
			case 3:
				return "RetractArm\n";
				break;
			case 4:
				return "previous_camera";
				break;
			case 5:
				return "next_camera";
				break;
			case 6:
			case 7:
				image_processing = !image_processing;
				return "";
				break;
			}
		}
		else if (sdl_event.type == SDL_JOYAXISMOTION)
        {
			float pwm_to_joystick_zone = JOYSTICK_MAXIMUM_ZONE / 255;
			switch (sdl_event.jaxis.axis)
			{
			case 0:
				if (abs(sdl_event.jaxis.value) > abs(JOYSTICK_DEAD_ZONE))
				{
					xAnalog = sdl_event.jaxis.value / pwm_to_joystick_zone;
				}
				else
				{
					xAnalog = 0;
				}
				break;
			case 1:
				if (abs(sdl_event.jaxis.value) > abs(JOYSTICK_DEAD_ZONE))
				{
					yAnalog = -(sdl_event.jaxis.value / pwm_to_joystick_zone);
				}
				else
				{
					yAnalog = 0;
				}
				break;
			}
        }
    }
	if (xAnalog == 0 && yAnalog == 0)
	{
		return "MotorsStop\n";
	}
	else if (abs(yAnalog) >= abs(xAnalog))
	{
		if (yAnalog > 0)
		{
			return "MoveForward," + to_string(yAnalog) + "\n";
		}
		else if (yAnalog < 0)
		{
			return "MoveBackwards," + to_string(abs(yAnalog)) + "\n";
		}
	}
	else
	{
		if (xAnalog > 0)
		{
			return "RotateRight," + to_string(xAnalog) + "\n";
		}
		else if (xAnalog < 0)
		{
			return "RotateLeft," + to_string(abs(xAnalog)) + "\n";
		}
	}
}