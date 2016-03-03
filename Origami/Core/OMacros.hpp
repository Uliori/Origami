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
    #define NS_O                           ::Origami
#else
    #define NS_O_BEGIN
    #define NS_O_END
    #define USING_NS_O
    #define NS_O
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

#define BOTTOM_LEFT(frameSize, size)    maths::vec2(0        , 0)
#define BOTTOM_RIGHT(frameSize, size)   maths::vec2(frameSize.width - size.x, 0)
#define TOP_LEFT(frameSize, size)       maths::vec2(0        , frameSize.height - size.y)
#define TOP_RIGHT(frameSize, size)      maths::vec2(frameSize.width - size.x, frameSize.height - size.y)


#endif /* OMacros_h */
