//
//  GameViewController.h
//  engine_ios
//
//  Created by El Mehdi KHALLOUKI on 10/8/15.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include "OGame.hpp"

class TouchPoint
{
public:
    unsigned int hashId;
    int lastX, lastY;
    int dx, dy;
    int x, y;
    bool down;
    
    TouchPoint()
    {
        hashId = 0;
        x = 0;
        y = 0;
        lastX = 0;
        lastY = 0;
        dx = 0;
        dy = 0;
        down = false;
    }
};

#define TOUCH_POINTS_MAX (10)
static TouchPoint __touchPoints[TOUCH_POINTS_MAX];

@interface GameViewController : GLKViewController{
    OGame *game;
    
    int updates;
    double lastTime;
    double tickCounter;
}

@end
