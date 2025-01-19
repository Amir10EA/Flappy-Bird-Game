#ifndef KEYBOARD_SHORTCUTS_H
#define KEYBOARD_SHORTCUTS_H
#include <SDL2/SDL.h>
void togglePause(bool &paused);
void toggleMute(bool &muted);
void adjustVolume(int delta);
#endif
