#pragma once
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
using namespace std;
static SDL_Joystick* gGameController = NULL;
static SDL_Event sdl_event;
static const int JOYSTICK_DEAD_ZONE = 2000;
static const int JOYSTICK_MAXIMUM_ZONE = 33000;
static int xAnalog_left = 0;
static int yAnalog_left = 0;
string gamepad_command = "";
int gamepad_value_1 = 0;
int gamepad_value_2 = 0;

void InitializeGamepad()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if (SDL_NumJoysticks() < 1)
        cout << "Warning: No joysticks connected!\n";
    else
        gGameController = SDL_JoystickOpen(0);
}

void UpdateAnalog()
{
	while (SDL_PollEvent(&sdl_event) != 0)
    {
		if (sdl_event.type == SDL_JOYBUTTONDOWN)
		{
			int buttonId = sdl_event.jbutton.button;
			switch (buttonId)
			{
			case 4:
				gamepad_command = "previous_camera";
				return;
				break;
			case 5:
				gamepad_command = "next_camera";
				return;
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
					xAnalog_left = sdl_event.jaxis.value / pwm_to_joystick_zone;
				else
					xAnalog_left = 0;
				break;
			case 1:
				if (abs(sdl_event.jaxis.value) > abs(JOYSTICK_DEAD_ZONE))
					yAnalog_left = -(sdl_event.jaxis.value / pwm_to_joystick_zone);
				else
					yAnalog_left = 0;
				break;
			}
        }
    }
}

void UpdateGamepadInput()
{
	int pwm = max(abs(xAnalog_left), abs(yAnalog_left));
	double theta = atan2(yAnalog_left, xAnalog_left);
	if (theta < 0)
		theta += 2 * M_PI;
	if (xAnalog_left == 0 && yAnalog_left == 0)
	{
		gamepad_command = "MotorsStop";
	}
	else 
	{
		gamepad_command = "MotorsMove";
		if (xAnalog_left >= 0 && yAnalog_left >= 0)
		{
			gamepad_value_1 = int(pwm);
			gamepad_value_2 = int(pwm*((4*theta/M_PI) - 1));
		}
		else if (xAnalog_left < 0 && yAnalog_left >= 0)
		{
			gamepad_value_1 = int(pwm*(1 - (4*(theta-(M_PI/2))/M_PI)));
			gamepad_value_2 = int(pwm);
		}
		else if (xAnalog_left < 0 && yAnalog_left < 0)
		{
			gamepad_value_1 = -int(pwm);
			gamepad_value_2 = int(pwm*(1 - (4*(theta-M_PI)/M_PI)));
		}
		else 
		{
			gamepad_value_1 = -int(pwm*(1 - (4*(theta-(3*M_PI/2))/M_PI)));
			gamepad_value_2 = -int(pwm);
		}
	}
	UpdateAnalog();
}