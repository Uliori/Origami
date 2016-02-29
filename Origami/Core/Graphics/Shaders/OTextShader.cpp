/****************************************************************************
 OTextShader.cpp
 
 Created by El Mehdi KHALLOUKI on 2/26/16.
 Copyright (c) 2016 __MyCompanyName__.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "OTextShader.hpp"

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

const std::string verttext =
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

const std::string fragtext =
OGL_VARYI               " vec4 v_fragColor;\n"
OGL_VARYI               " vec2 v_UV;\n"
OGL_FragColorDec
"uniform sampler2D u_diffuse;\n"
"void main()\n"
"{\n"
"float a = " OGL_TEXTURE"(u_diffuse, v_UV).r;\n"
OGL_FragColor " = vec4(v_fragColor.xyz, a * v_fragColor.a);\n"
"}\n";





OTextShader::OTextShader()
{
    
    
}

void OTextShader::init()
{
    m_Name = "OTextShader";
    
    std::string vs = GLSLHEADER + verttext;
    std::string fs = GLSLHEADER + PRECISION_H + fragtext;
    
    this->load(vs, fs);
}

void OTextShader::bindLocations()
{
    m_Program->bindLocation(0, "a_position");
    m_Program->bindLocation(1, "a_color");
    m_Program->bindLocation(2, "a_UV");
    
}

void OTextShader::prepare(OCamera2D *camera)
{
    glActiveTexture(GL_TEXTURE0);
    setUniform1i("u_diffuse", 0);
    setUniformMat4("u_MVP", camera->getCameraMatrix());
}
NS_O_END