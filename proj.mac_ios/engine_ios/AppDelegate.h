//
//  AppDelegate.h
//  engine_ios
//
//  Created by El Mehdi KHALLOUKI on 10/8/15.
//
//

#import <UIKit/UIKit.h>

#include "OGame.hpp"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property OGame *game;

+ (AppDelegate *)appDelegate;

@end

