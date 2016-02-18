//
//  OCamera2D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#pragma once

#include <Core/Maths/OMaths.hpp>

#include <Core/OMacros.hpp>

NS_O_BEGIN
class OSprite;
class OCamera2D
{
public:
    OCamera2D(int screenWidth, int screenHeight);
    virtual ~OCamera2D();

private:
    int m_ScreenWidth, m_ScreenHeight;
    float m_Scale;
    bool m_NeedsMatrixUpdate;

    maths::vec2 m_Position;
    maths::mat4 m_CameraMatrix;
    maths::mat4 m_OrthoMatrix;

public:

    //setters
    void setPosition(const maths::vec2& newPosition) { m_Position = newPosition; m_NeedsMatrixUpdate = true; }
    void setScale(float newScale) { m_Scale = newScale; m_NeedsMatrixUpdate = true; }
    void setProjection(int screenWidth, int screenHeight);
    
    void setTarget(const maths::vec2& target, const maths::vec2& offset);
    
    void moveBy(float x, float y) { m_Position.x += x; m_Position.y += y;  m_NeedsMatrixUpdate = true;}

    //getters
    const maths::vec2& getPosition() { return m_Position; }
    float getScale() { return m_Scale; }
    const maths::mat4& getCameraMatrix() { return m_CameraMatrix; }


    //Camera culling
    virtual bool isBoxInView(const maths::vec2& position, const maths::vec2& dimensions);
    virtual maths::vec2 convertScreenToWorld(maths::vec2 screenCoords);

    virtual void update(float deltaTime);
};

NS_O_END
