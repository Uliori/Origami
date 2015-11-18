//
//  GameViewController.m
//  engine_ios
//
//  Created by El Mehdi KHALLOUKI on 10/8/15.
//
//

#import "GameViewController.h"




#define BUFFER_OFFSET(i) ((char *)NULL + (i))


@interface GameViewController () {
    
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;
@end

@implementation GameViewController

- (NSUInteger)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscape;
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    return UIInterfaceOrientationLandscapeLeft;
}

- (BOOL)shouldAutorotate{
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
    self.preferredFramesPerSecond = game->GetPreferredFPS();
    
    DESIRED_FRAMETIME  = 1.0f / game->GetPreferredFPS();
    
    [((GLKView *)self.view) bindDrawable];
    
    
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    game = new OGame("",screenRect.size.width, screenRect.size.height, [[UIScreen mainScreen] scale]);
    game->Start();
    

    lastTime      = game->getTimer()->getTime();
    tickCounter = 0;
    updates = 0;
    currentTicks = 0;
    previousTicks = 0;
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
     SAFE_DELETE(game);

}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
#ifdef O_MODE_DEBUG
    double startTime = game->getTimer()->getTime();
    double passedTime = startTime - lastTime;
    lastTime = startTime;
    
    tickCounter += passedTime;
    
    if (tickCounter >= 1.0f) {
        game->setFPS(self.framesPerSecond);
        game->setUPS(updates);
        
        updates = 0;
        tickCounter -= 1.0f;
        
        game->Tick();
    }
    
#endif

    currentTicks += self.timeSinceLastUpdate;
    while (currentTicks - previousTicks > DESIRED_FRAMETIME) {
        game->Update(DESIRED_FRAMETIME);
        previousTicks += DESIRED_FRAMETIME;
        updates ++;
    }
    game->Refresh();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    game->Render();
}


- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    unsigned int touchID = 0;
    for(UITouch* touch in touches)
    {
        CGPoint touchPoint = [touch locationInView:self.view];
        if(self.view.multipleTouchEnabled == YES)
        {
            touchID = [touch hash];
        }
        
        // Nested loop efficiency shouldn't be a concern since both loop sizes are small (<= 10)
        int i = 0;
        while (i < TOUCH_POINTS_MAX && __touchPoints[i].down)
        {
            i++;
        }
        
        if (i < TOUCH_POINTS_MAX)
        {
//            vec2 pos = vec2(touchPoint.x, OWindow::s_height - touchPoint.y);
//            __touchPoints[i].hashId = touchID;
//            __touchPoints[i].lastX = pos.x;
//            __touchPoints[i].lastY = pos.y;
//            __touchPoints[i].down = true;
            
//            OEScenesManager::currentS->touchEvent(__touchPoints[i].hashId, touchState::BEGIN, pos, pos);
        }
        
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    unsigned int touchID = 0;
    for(UITouch* touch in touches)
    {
//        CGPoint touchPoint = [touch locationInView:self.view];
//        vec2 pos = vec2(touchPoint.x, OWindow::s_height - touchPoint.y);
//        if(self.view.multipleTouchEnabled == YES)
//            touchID = [touch hash];
//        
//        // Nested loop efficiency shouldn't be a concern since both loop sizes are small (<= 10)
//        bool found = false;
//        for (int i = 0; !found && i < TOUCH_POINTS_MAX; i++)
//        {
//            if (__touchPoints[i].down && __touchPoints[i].hashId == touchID)
//            {
//                __touchPoints[i].down = false;
////                OEScenesManager::currentS->touchEvent(__touchPoints[i].hashId, touchState::END, pos, pos);
//                found = true;
//            }
//        }
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    // No equivalent for this in GamePlay -- treat as touch end
    [self touchesEnded:touches withEvent:event];
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    unsigned int touchID = 0;
    for(UITouch* touch in touches)
    {
        CGPoint touchPoint = [touch locationInView:self.view];
//        
//        vec2 pos = vec2(touchPoint.x, OWindow::s_height - touchPoint.y);
//        if(self.view.multipleTouchEnabled == YES)
//            touchID = [touch hash];
//        
//        // Nested loop efficiency shouldn't be a concern since both loop sizes are small (<= 10)
//        for (int i = 0; i < TOUCH_POINTS_MAX; i++)
//        {
//            if (__touchPoints[i].down && __touchPoints[i].hashId == touchID)
//            {
//                __touchPoints[i].x = pos.x;
//                __touchPoints[i].y = pos.y;
//                __touchPoints[i].dx = __touchPoints[i].x - __touchPoints[i].lastX;
//                __touchPoints[i].dy = __touchPoints[i].y - __touchPoints[i].lastY;
////                OEScenesManager::currentS->touchEvent(__touchPoints[i].hashId, touchState::MOVE, pos, vec2(__touchPoints[i].dx, __touchPoints[i].dy));
//                __touchPoints[i].lastX = __touchPoints[i].x;
//                __touchPoints[i].lastY = __touchPoints[i].y;
//                break;
//            }
//        }
    }
}



@end
