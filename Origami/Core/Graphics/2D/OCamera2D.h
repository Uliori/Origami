//
//  OCamera2D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/24/15.
//
//

#pragma once

#include <Core/Maths/OMaths.h>

namespace Origami {

    class OCamera2D
    {
    public:
        OCamera2D(int screenWidth, int screenHeight);
        virtual ~OCamera2D();
        
    private:
        int m_screenWidth, m_screenHeight;
        bool m_needsMatrixUpdate;
//        float m_scale;
        
        maths::vec2 m_position;
        maths::mat4 m_cameraMatrix;
        maths::mat4 m_orthoMatrix;
        
    public:
        
        //setters
        void setPosition(const maths::vec2& newPosition) { m_position = newPosition; m_needsMatrixUpdate = true; }
//        void setScale(float newScale) { m_scale = newScale; m_needsMatrixUpdate = true; }
        void setProjection(int screenWidth, int screenHeight);
                           
        //getters
        maths::vec2 getPosition() { return m_position; }
//        float getScale() { return _scale; }
        maths::mat4 getCameraMatrix() { return m_cameraMatrix; }
        
        
        //Camera culling
        virtual bool isBoxInView(const maths::vec3& position, const maths::vec2& dimensions);
        virtual maths::vec2 convertScreenToWorld(maths::vec2 screenCoords);
        
        virtual void update(float deltaTime);
    };

}