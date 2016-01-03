//
//  OCamera2D.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#include "OCamera2D.h"
#include <Core/Utils/OLog.h>

NS_O_BEGIN

OCamera2D::OCamera2D(int screenWidth, int screenHeight):m_position(0.0f, 0.0f),
//    _scale(1.0f),
m_needsMatrixUpdate(true)
{
    setProjection(screenWidth, screenHeight);
}

OCamera2D::~OCamera2D()
{
    
}

void OCamera2D::setProjection(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_orthoMatrix = maths::ortho(0.0f, (float) screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    m_needsMatrixUpdate = true;
    update(1);
}


void OCamera2D::update(float deltaTime)
{
    if (m_needsMatrixUpdate) {
        
        maths::vec3 translate(-m_position.x, -m_position.y, 0.0f);
//            maths::vec3 scale(m_scale, m_scale, 0.0f);
        
        maths::mat4 mt = maths::translate(translate);
//            maths::mat4 ms = maths::scale(scale);
        
        m_cameraMatrix = m_orthoMatrix * mt;// * ms;
        
        m_needsMatrixUpdate = false;
    }
}

maths::vec2 OCamera2D::convertScreenToWorld(maths::vec2 screenCoords) {
    // Invert Y direction
    screenCoords.y = m_screenHeight - screenCoords.y;
    // Make it so that 0 is the center
    //screenCoords -= maths::vec2(_screenWidth / 2, _screenHeight / 2);
    // Scale the coordinates
//        screenCoords /= _scale;
    // Translate with the camera position
    screenCoords += m_position;
    return screenCoords;
}



//TODO : correct a bug when scaling camera
bool OCamera2D::isBoxInView(const maths::vec3& position, const maths::vec2& dimensions)
{
    maths::vec2 scaledScreenDimensions = maths::vec2((float)m_screenWidth, (float)m_screenHeight);// / (_scale);
    
    // The minimum distance before a collision occurs
    const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
    const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;
    
    // Center position of the parameters
    maths::vec2 centerPos = maths::vec2(position.x, position.y) + dimensions / 2.0f;
    // Center position of the camera
    maths::vec2 centerCameraPos = m_position + maths::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f);
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