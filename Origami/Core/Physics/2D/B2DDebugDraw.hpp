#pragma once


#include <Core/OMacros.hpp>

#include <Core/Physics/2D/O2DPhysics.hpp>
#include <Core/OGL.hpp>
#include <Core/Maths/OMaths.hpp>
#include <Core/Graphics/2D/OCamera2D.hpp>

NS_O_BEGIN

struct PhysicsVertexData2D
{
    maths::vec2  m_Vertex;
    unsigned int m_Color;
};

/// B2DDebugDraw implements debug drawing callbacks that are invoked
/// inside b2World::DrawDebugData.
class B2DDebugDraw : public b2Draw
{
    OCamera2D* m_Camera = nullptr;
    float m_Ratio = 1;
	void init();
    
    GLuint m_VboID = 0;
    GLuint m_VaoID = 0;
    void createVertexArray();

    void bind();
    void unbind();
public:

    
	B2DDebugDraw(OCamera2D* camera, float ratio = 1);

    ~B2DDebugDraw();
    
    
    void drawWorld(b2World* world);

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

NS_O_END