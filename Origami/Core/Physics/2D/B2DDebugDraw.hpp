#pragma once


#include <Box2D/Box2D.h>
#include <Core/OGL.hpp>
struct b2AABB;

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class B2DDebugDraw : public b2Draw
{
	float32 mRatio;
	GLint		mColorLocation;

	void initShader( void );
public:
	B2DDebugDraw();

	B2DDebugDraw( float32 ratio );

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawTransform(const b2Transform& xf);

    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

    void DrawString(int x, int y, const char* string, ...);

    void DrawAABB(b2AABB* aabb, const b2Color& color);
};

