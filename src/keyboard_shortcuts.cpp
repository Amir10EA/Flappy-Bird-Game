#include "keyboard_shortcuts.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>

void togglePause(bool &paused)
{
    paused = !paused;
}
void toggleMute(bool &muted)
{
    muted = !muted;
    static int previousvolume = MIX_MAX_VOLUME;
    if (muted)
    {
        previousvolume = Mix_Volume(-1, -1);
        Mix_Volume(-1, 0);
    }
    else
    {
        Mix_Volume(-1, previousvolume);
    }
}
void adjustVolume(int x)
{
    int currentvolume = Mix_Volume(-1, -1);
    Mix_Volume(-1, std::max(0, std::min(MIX_MAX_VOLUME, currentvolume + x)));
}