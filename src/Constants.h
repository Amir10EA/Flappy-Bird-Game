#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 750.0f          // Reduced from 980.0f for easier gameplay
#define FPS 60
#define BIRD_WIDTH 55          // Changed from 50 to 55 to maintain proportions
#define BIRD_HEIGHT 40         // Reduced from 50 to 40 for slightly smaller bird
#define PIPE_WIDTH 70
#define PIPE_GAP 220           // Increased from 180 to 220 for easier passage
#define PIPE_SPACING (WINDOW_WIDTH * 0.4f)
#define INITIAL_SCROLL_SPEED 3.0f
#define FLAP_FORCE -350.0f     // Reduced magnitude since gravity is lower

#endif