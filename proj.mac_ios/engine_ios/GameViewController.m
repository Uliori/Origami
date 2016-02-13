//
//  GameViewController.m
//  engine_ios
//
//  Created by El Mehdi KHALLOUKI on 10/8/15.
//
//

#import "GameViewController.h"
#import "AppDelegate.h"

#include <Core/ODirector.hpp>



#define BUFFER_OFFSET(i) ((char *)NULL + (i))


@interface GameViewController () {
    
}
@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;
@end

@implementation GameViewController

//- (NSUInteger)supportedInterfaceOrientations {
//    return UIInterfaceOrientationMaskLandscape;
//}
//
//- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
//    return UIInterfaceOrientationLandscapeLeft;
//}

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
    
    self.preferredFramesPerSecond = [AppDelegate appDelegate].game->getPreferredFPS();
    
    DESIRED_FRAMETIME  = 1000.0f / [AppDelegate appDelegate].game->getPreferredFPS();
    
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
    [AppDelegate appDelegate].game = new OGame("",screenRect.size.width * [[UIScreen mainScreen] scale], screenRect.size.height * [[UIScreen mainScreen] scale]);
    [AppDelegate appDelegate].game->start();
    

    previousTicks   = ODirector::director()->getTimer()->getTime();
    tickCounter     = 0;
    updates         = 0;
    currentTicks    = 0;
    accumulator     = 0;
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
     SAFE_DELETE([AppDelegate appDelegate].game);

}
#pragma mark - Orientation detection
- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [[NSNotificationCenter defaultCenter] addObserver:self  selector:@selector(orientationChanged:)    name:UIDeviceOrientationDidChangeNotification  object:nil];
}

-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    [[NSNotificationCenter defaultCenter]removeObserver:self name:UIDeviceOrientationDidChangeNotification object:nil];
}

- (void)orientationChanged:(NSNotification *)notification{
    [self adjustViewsForOrientation:[[UIDevice currentDevice] orientation]];
}

- (void) adjustViewsForOrientation:(UIDeviceOrientation) orientation {
    
    if (ODirector::director()->getCurrentScene()) {
        CGRect screenRect = [[UIScreen mainScreen] bounds];
        ODirector::director()->setFrameSize(screenRect.size.width * [[UIScreen mainScreen] scale], screenRect.size.height * [[UIScreen mainScreen] scale]);
    
        OSize designResolutionSize = ODirector::director()->getDesignResolutionSize();
        
        if (screenRect.size.width > screenRect.size.height) { //Landscape
            ODirector::director()->setDesignResolutionSize(MAX(designResolutionSize.width, designResolutionSize.height), MIN(designResolutionSize.width, designResolutionSize.height), ResolutionPolicy::FIXED_HEIGHT);
        }
        else
        {
            ODirector::director()->setDesignResolutionSize(MIN(designResolutionSize.width, designResolutionSize.height), MAX(designResolutionSize.width, designResolutionSize.height), ResolutionPolicy::FIXED_WIDTH);
        }

        
        OSize fS = ODirector::director()->getFrameSize();
        glViewport(0, 0, fS.width, fS.height);
    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    double startTicks = ODirector::director()->getTimer()->getTime();
    double passedTime = startTicks - previousTicks;
    previousTicks = startTicks;
    
    if (![AppDelegate appDelegate].game->isSupended()) {
        accumulator += passedTime;
        int   loops = 0;
        
        while(accumulator >= DESIRED_FRAMETIME && loops < 10)
        {
            accumulator -= DESIRED_FRAMETIME;
            loops++;
            [AppDelegate appDelegate].game->update(DESIRED_FRAMETIME / 1000.0f);
            updates ++;
            [AppDelegate appDelegate].game->refresh();
        }
    }
    
#ifdef O_MODE_DEBUG    
    tickCounter += passedTime;
    
    if (tickCounter >= 1000.0f) {
        [AppDelegate appDelegate].game->setFPS((uint)self.framesPerSecond);
        [AppDelegate appDelegate].game->setUPS(updates);
        
        updates = 0;
        tickCounter -= 1000.0f;
        
        if (![AppDelegate appDelegate].game->isSupended()) [AppDelegate appDelegate].game->tick();
    }
    
#endif

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    float interpolation = float(ODirector::director()->getTimer()->getTime() + DESIRED_FRAMETIME - previousTicks )/ float( DESIRED_FRAMETIME );
    [AppDelegate appDelegate].game->render(interpolation);
}


#pragma mark - Touch Handling
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
