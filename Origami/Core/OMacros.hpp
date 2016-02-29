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

#define SAFE_DELETE(x)          { if (x) { delete (x); x = nullptr; } }
#define SAFE_DELETE_ARRAY(x)    { if (x) { delete[] x; x = nullptr; } }
#define SAFE_RELEASE(x)         { if (x) { (x)->release(); } }

#if !defined(MIN)
  #define MIN(A,B)	((A) < (B) ? (A) : (B))
#endif

#if !defined(MAX)
  #define MAX(A,B)	((A) > (B) ? (A) : (B))
#endif

#define fromBottomLeft(frameSize, position) maths::vec2(-frameSize.width / 2, -frameSize.height / 2) + position
#define fromCenter(frameSize, position) maths::vec2(-frameSize.width / 2, 0) + position


#endif /* OMacros_h */
