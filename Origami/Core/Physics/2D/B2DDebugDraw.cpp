#include "B2DDebugDraw.hpp"

#include <cstdio>
#include <cstdarg>

#include <cstring>

#include <Core/Graphics/Renderers/ORendererFactory.hpp>

NS_O_BEGIN

B2DDebugDraw::B2DDebugDraw(OCamera2D* camera, float ratio)
:m_Camera(camera), m_VboID(0), m_VaoID(0),m_Ratio(ratio)
{
    init();
}


B2DDebugDraw::~B2DDebugDraw()
{
    if (m_VboID != 0) {
        glDeleteBuffers(1, &m_VboID);
    }
    
    if (m_VaoID != 0) {
        glDeleteVertexArrays(1, &m_VaoID);
    }
    m_Camera = nullptr;
}

void B2DDebugDraw::init()
{
    createVertexArray();
}

void B2DDebugDraw::drawWorld(b2World* world)
{
    bind();
    world->DrawDebugData();
    unbind();
}

void B2DDebugDraw::createVertexArray()
{
    // Generate the VAO if it isn't already generated
    if (m_VaoID == 0) {
        glGenVertexArrays(1, &m_VaoID);
    }
    
    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(m_VaoID);
    
    //G enerate the VBO if it isn't already generated
    if (m_VboID == 0) {
        glGenBuffers(1, &m_VboID);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    
    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(0, 2, GL_FLOAT,         GL_FALSE, sizeof(PhysicsVertexData2D), (void *)offsetof(PhysicsVertexData2D, m_Vertex));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(PhysicsVertexData2D), (void *)offsetof(PhysicsVertexData2D, m_Color));
    
    glBindVertexArray(0);
    
}

void B2DDebugDraw::bind()
{
    glBindVertexArray(m_VaoID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
    
    ORendererFactory::OShader_Color2D->bind();
    ORendererFactory::OShader_Color2D->setUniformMat4("u_MVP", m_Camera->getCameraMatrix());
}

void B2DDebugDraw::unbind()
{
    glBindVertexArray(0);
}

void B2DDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<PhysicsVertexData2D> vertices(vertexCount);

	for( int i=0;i<vertexCount;i++) {
		b2Vec2 tmp = old_vertices[i];
        tmp *= m_Ratio;
		vertices[i].m_Vertex.x = tmp.x;
        vertices[i].m_Vertex.y = tmp.y;
        vertices[i].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
	}

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void B2DDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<PhysicsVertexData2D> vertices(vertexCount);
    
    for( int i=0;i<vertexCount;i++) {
        b2Vec2 tmp = old_vertices[i];
        tmp *= m_Ratio;
        vertices[i].m_Vertex.x = tmp.x;
        vertices[i].m_Vertex.y = tmp.y;
        vertices[i].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    }
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}

void B2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

    std::vector<PhysicsVertexData2D> vertices(vertexCount);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		vertices[i].m_Vertex.x = v.x * m_Ratio;
		vertices[i].m_Vertex.y = v.y * m_Ratio;
        vertices[i].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
		theta += k_increment;
	}
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
    
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void B2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    const float32 k_segments = 16.0f;
    int vertexCount=16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    std::vector<PhysicsVertexData2D> vertices(vertexCount);
    
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        vertices[i].m_Vertex.x = v.x * m_Ratio;
        vertices[i].m_Vertex.y = v.y * m_Ratio;
        vertices[i].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
        theta += k_increment;
    }
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

//	// Draw the axis line
	DrawSegment(center,center+radius*axis,color);
}

void B2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    std::vector<PhysicsVertexData2D> vertices(2);
    
    vertices[0].m_Vertex = maths::vec2(p1.x, p1.y) * m_Ratio;
    vertices[1].m_Vertex = maths::vec2(p2.x, p2.y) * m_Ratio;
    vertices[0].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    vertices[1].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
}

void B2DDebugDraw::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSegment(p1, p2, b2Color(1,0,0));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
    DrawSegment(p1,p2,b2Color(0,1,0));
}

void B2DDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    std::vector<PhysicsVertexData2D> vertices(1);
    
    vertices[0].m_Vertex = maths::vec2(p.x, p.y) * m_Ratio;
    vertices[0].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);
}

void B2DDebugDraw::DrawString(int x, int y, const char *string, ...)
{
	//	NSLog(@"DrawString: unsupported: %s", string);
	//printf(string);
	/* Unsupported as yet. Could replace with bitmap font renderer at a later date */
}

void B2DDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    std::vector<PhysicsVertexData2D> vertices(4);
    
    vertices[0].m_Vertex = maths::vec2(aabb->lowerBound.x, aabb->lowerBound.y) * m_Ratio;
    vertices[0].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    vertices[1].m_Vertex = maths::vec2(aabb->upperBound.x, aabb->lowerBound.y) * m_Ratio;
    vertices[1].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    vertices[2].m_Vertex = maths::vec2(aabb->upperBound.x, aabb->upperBound.y) * m_Ratio;
    vertices[2].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    vertices[3].m_Vertex = maths::vec2(aabb->lowerBound.x, aabb->upperBound.y) * m_Ratio;
    vertices[3].m_Color = OColorRGBA8(color.r, color.g, color.b).getColorUint();
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PhysicsVertexData2D), vertices.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, 8);
}

NS_O_END