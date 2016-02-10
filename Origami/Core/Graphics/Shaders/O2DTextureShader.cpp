//
//  O2DTextureShader.cpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/20/15.
//
//

#include "O2DTextureShader.hpp"

NS_O_BEGIN

const std::string PRECISION_H =
                                "#ifdef GL_ES\n"
                                "     #ifndef GL_FRAGMENT_PRECISION_HIGH\n"
                                "       precision mediump float;\n"
                                "       precision mediump int;\n"
                                "     #else\n"
                                "       precision highp float;\n"
                                "       precision highp int;\n"
                                "     #endif\n"
                                "#endif\n";

const std::string vertsimple2d =
                                OGL_LAYOUT(0)  OGL_ATTR " vec2 a_position;\n"
                                OGL_LAYOUT(1)  OGL_ATTR " vec4 a_color;\n"
                                OGL_LAYOUT(2)  OGL_ATTR " vec2 a_UV;\n"

                                OGL_VARYO               " vec4 v_fragColor;\n"
                                OGL_VARYO               " vec2 v_UV;\n"
                                "uniform mat4 u_MVP;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = u_MVP * vec4(a_position, 0.0, 1.0);\n"
                                "	  v_fragColor = a_color;\n"
                                "	  v_UV = a_UV;\n"
                                "}\n";

const std::string fragsimple2d =
                                OGL_VARYI               " vec4 v_fragColor;\n"
                                OGL_VARYI               " vec2 v_UV;\n"
                                OGL_FragColorDec
                                "uniform sampler2D u_diffuse;\n"
                                "void main()\n"
                                "{\n"
                                    OGL_FragColor " =  v_fragColor * " OGL_TEXTURE "(u_diffuse, v_UV);\n"
//                                    OGL_FragColor " =  vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                "}\n";

//Text Rendering
//    "void main()\n"
//    "{\n"
//    "float a = " OGL_TEXTURE"(u_diffuse, v_UV).r;\n"
//    OGL_FragColor " = vec4(v_fragColor.xyz, a * v_fragColor.a);\n"
//    "}\n";





O2DTextureShader::O2DTextureShader()
{


}

void O2DTextureShader::init()
{
    m_Name = "O2DTextureShader";

    std::string vs = GLSLHEADER + vertsimple2d;
    std::string fs = GLSLHEADER + PRECISION_H + fragsimple2d;

    this->load(vs, fs);
}

void O2DTextureShader::bindLocations()
{
    m_Program->bindLocation(0, "a_position");
    m_Program->bindLocation(1, "a_color");
    m_Program->bindLocation(2, "a_UV");

}

NS_O_END
