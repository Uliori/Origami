//
//  GameViewController.h
//  engine_ios
//
//  Created by El Mehdi KHALLOUKI on 10/8/15.
//
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface GameViewController : GLKViewController{
    
    int updates;
    double tickCounter;
    
    double currentTicks;
    double previousTicks;
    double accumulator;
    
    float  DESIRED_FRAMETIME;
}

@end
