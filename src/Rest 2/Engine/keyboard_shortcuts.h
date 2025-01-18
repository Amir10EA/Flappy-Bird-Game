#ifndef KEYBOARD_SHORTCUTS_H
#define KEYBOARD_SHORTCUTS_H

#include <SDL2/SDL.h>

// Free functions for keyboard shortcuts
void togglePause(bool& isPaused);
void toggleMute(bool& isMuted);
void adjustVolume(int delta);

#endif
