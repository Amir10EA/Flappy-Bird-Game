#include "keyboard_shortcuts.h"
#include <SDL2/SDL_mixer.h>
#include <algorithm>

void togglePause(bool& isPaused) {
    isPaused = !isPaused;
}

void toggleMute(bool& isMuted) {
    isMuted = !isMuted;
    // Restore previous volume when unmuting
    static int previousVolume = MIX_MAX_VOLUME;
    if (isMuted) {
        previousVolume = Mix_Volume(-1, -1); // Store current volume
        Mix_Volume(-1, 0);
    } else {
        Mix_Volume(-1, previousVolume); // Restore previous volume
    }
}

void adjustVolume(int delta) {
    int currentVolume = Mix_Volume(-1, -1);
    Mix_Volume(-1, std::max(0, std::min(MIX_MAX_VOLUME, currentVolume + delta)));
}