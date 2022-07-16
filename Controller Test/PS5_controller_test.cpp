#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"
using namespace std;
static SDL_Joystick* gGameController = NULL;
static SDL_Event sdl_event;
static const int JOYSTICK_DEAD_ZONE = 2000;
static const int JOYSTICK_MAXIMUM_ZONE = 33000;

void InitializeGamepad()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    gGameController = SDL_JoystickOpen(0);
}

void UpdateAnalog()
{
	while (SDL_PollEvent(&sdl_event) != 0)
    {
		if (sdl_event.type == SDL_JOYBUTTONDOWN)
		{
			int buttonId = sdl_event.jbutton.button;
			cout << "Button " << buttonId << " pressed\n";
		}
		else if (sdl_event.type == SDL_JOYAXISMOTION && abs(sdl_event.jaxis.value) > JOYSTICK_DEAD_ZONE)
        {   
			switch (sdl_event.jaxis.axis)
			{
			case 0:
				cout << "X axis: " << sdl_event.jaxis.value << endl;
                break;
			case 1:
				cout << "Y axis: " << sdl_event.jaxis.value << endl;
                break;
			}
        }
    }
}

int main()
{
    while (true)
    {
        if (SDL_NumJoysticks() < 1)
        {
            try
            {
                InitializeGamepad();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        UpdateAnalog();
    }
    return 0;
}