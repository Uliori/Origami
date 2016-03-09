//
//  OMacros.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 12/30/15.
//
//

#ifndef OMacros_h
#define OMacros_h

#ifdef __cplusplus
    #define NS_O_BEGIN                     namespace Origami {
    #define NS_O_END                       }
    #define USING_NS_O                     using namespace Origami;
#else
    #define NS_O_BEGIN
    #define NS_O_END
    #define USING_NS_O
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define SAFE_DELETE(x)          { if (x) { delete (x); x = nullptr; } }
#define SAFE_DELETE_ARRAY(x)    { if (x) { delete[] x; x = nullptr; } }
#define SAFE_RELEASE(x)         { if (x) { (x)->release(); } }

#if !defined(MIN)
  #define MIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(MAX)
  #define MAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#define P_BOTTOM_LEFT(frameSize, size)    maths::vec2(0                           , 0)
#define P_BOTTOM_RIGHT(frameSize, size)   maths::vec2(frameSize.width - size.x    , 0)
#define P_TOP_LEFT(frameSize, size)       maths::vec2(0                           , frameSize.height - size.y)
#define P_TOP_RIGHT(frameSize, size)      maths::vec2(frameSize.width - size.x    , frameSize.height - size.y)
#define P_CENTER(frameSize, size)         maths::vec2(frameSize.width/2 - size.x/2, frameSize.height/2 - size.y/2)
#define P_BOTTOM(frameSize, size)         maths::vec2(frameSize.width/2 - size.x/2, 0)
#define P_TOP(frameSize, size)            maths::vec2(frameSize.width/2 - size.x/2, frameSize.height - size.y)
#define P_LEFT(frameSize, size)           maths::vec2(0                           , frameSize.height/2 - size.y/2)
#define P_RIGHT(frameSize, size)          maths::vec2(frameSize.width - size.x    , frameSize.height/2 - size.y/2)

#endif /* OMacros_h */
