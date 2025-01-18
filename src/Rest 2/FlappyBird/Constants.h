#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 830
#define GROUND_HEIGHT 149          // Height of the ground from bottom
#define PLAYABLE_HEIGHT (WINDOW_HEIGHT - GROUND_HEIGHT)  // Height of playable area
#define GRAVITY 750.0f
#define FPS 60
#define BIRD_WIDTH 55
#define BIRD_HEIGHT 40
#define PIPE_WIDTH 70
#define PIPE_GAP 265              // Increased from 220 for easier gameplay
#define PIPE_SPACING (WINDOW_WIDTH * 0.4f)
#define INITIAL_SCROLL_SPEED 3.0f
#define FLAP_FORCE -350.0f
#define BACKGROUND_SCROLL_SPEED 1.0f

#endif