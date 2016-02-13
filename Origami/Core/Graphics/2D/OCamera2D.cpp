//
//  OCamera2D.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#include "OCamera2D.hpp"
#include <Core/Utils/OLog.hpp>

NS_O_BEGIN

OCamera2D::OCamera2D(int screenWidth, int screenHeight):m_Position(0.0f, 0.0f),m_NeedsMatrixUpdate(true)
//    _scale(1.0f),
{
    setProjection(screenWidth, screenHeight);
}

OCamera2D::~OCamera2D()
{

}

void OCamera2D::setProjection(int screenWidth, int screenHeight)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;
    m_Scale = 1;
    m_OrthoMatrix = maths::ortho(0.0f, (float) screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    m_NeedsMatrixUpdate = true;
    update(1);
}


void OCamera2D::update(float deltaTime)
{
    if (m_NeedsMatrixUpdate) {

        maths::vec3 translate(-m_Position.x, -m_Position.y, 0.0f);
        maths::vec3 scale(m_Scale, m_Scale, 0.0f);

        maths::mat4 mt = maths::translate(translate);
        maths::mat4 ms = maths::scale(scale);

        m_CameraMatrix = m_OrthoMatrix * mt * ms;

        m_NeedsMatrixUpdate = false;
    }
}

maths::vec2 OCamera2D::convertScreenToWorld(maths::vec2 screenCoords) {
    // Invert Y direction
    screenCoords.y = m_ScreenHeight - screenCoords.y;
    // Make it so that 0 is the center
    //screenCoords -= maths::vec2(_screenWidth / 2, _screenHeight / 2);
    // Scale the coordinates
//        screenCoords /= _scale;
    // Translate with the camera position
    screenCoords += m_Position;
    return screenCoords;
}



//TODO : correct a bug when scaling camera
bool OCamera2D::isBoxInView(const maths::vec2& position, const maths::vec2& dimensions)
{
    maths::vec2 scaledScreenDimensions = maths::vec2((float)m_ScreenWidth, (float)m_ScreenHeight);// / (_scale);

    // The minimum distance before a collision occurs
    const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
    const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

    // Center position of the parameters
    maths::vec2 centerPos = position + dimensions / 2.0f;
    // Center position of the camera
    maths::vec2 centerCameraPos = m_Position + maths::vec2(m_ScreenWidth / 2.0f, m_ScreenHeight / 2.0f);
    // Vector from the input to the camera
    maths::vec2 distVec = centerPos - centerCameraPos;

    float offset = 0.01f;
    // Get the depth of the collision
    float xDepth = MIN_DISTANCE_X - fabs(distVec.x - (distVec.x * offset));
    float yDepth = MIN_DISTANCE_Y - fabs(distVec.y - (distVec.y * offset));

    // If both the depths are > 0, then we collided
    if (xDepth > 0 && yDepth > 0) {
        // There was a collision
        return true;
    }
    return false;
}

NS_O_END
