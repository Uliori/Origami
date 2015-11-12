//
//  OSprite.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/21/15.
//
//

#pragma once

#include <Core/Utils/OGLUtils.h>
#include <Core/Maths/OMaths.h>
#include <Core/Graphics/OTexture.h>
#include <Core/Graphics/Renderers/ORenderer2D.h>



namespace Origami {
    
    class ORenderer2D;
    class OSprite {
    private:
        maths::vec2 m_Size;
        maths::vec4 m_UV;
        
        GLuint m_vaoID;
        GLuint m_vboID;
        
        GLuint m_Texture;
        std::string m_texturePath;
    protected:
        maths::vec3 m_Position;
        unsigned int m_Color;
        OSprite(){}
    public:
        OSprite(float x, float y, float width, float height, std::string texturePath);
        ~OSprite();
        
        void create();
        void draw();
        
//        OTexture _texture;
        
        //setters
        inline void SetColor(unsigned int color) { m_Color = color; }
        inline void SetColor(const maths::vec4& color)
        {
            uint r = (uint)(color.x * 255.0f);
            uint g = (uint)(color.y * 255.0f);
            uint b = (uint)(color.z * 255.0f);
            uint a = (uint)(color.w * 255.0f);
            
            m_Color = a << 24 | b << 16 | g << 8 | r;
        }
        
        inline void setPosition(const maths::vec3& position)
        {
            m_Position = position;
        }
        
        inline void setSize(const maths::vec2& size)
        {
            m_Size = size;
        }
        
        inline void setTexture(GLuint texture)
        {
            m_Texture = texture;
        }
        
        inline void SetUV(const maths::vec4& uv)
        {
            m_UV = uv;
        }
        
        //getters
        inline const maths::vec3& GetPosition() const { return m_Position; }
        inline const maths::vec2& GetSize() const { return m_Size; }
        inline const unsigned int GetColor() const { return m_Color; }
        inline const maths::vec4& GetUV() const { return m_UV; }
        inline const GLuint GetTID() const { return m_Texture; }
        
        virtual void Submit(ORenderer2D* renderer) const
        {
            renderer->Submit(this);
        }
        
    private:
        void SetUVDefaults()
        {
            m_UV = maths::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        }

        
    };
}

