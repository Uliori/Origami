/****************************************************************************
 O2DColorShader.cpp
 
 Created by El Mehdi KHALLOUKI on 2/10/16.
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

#include "O2DColorShader.hpp"

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

const std::string vertcolor2d =
OGL_LAYOUT(0)  OGL_ATTR " vec2 a_position;\n"
OGL_LAYOUT(1)  OGL_ATTR " vec4 a_color;\n"

OGL_VARYO               " vec4 v_fragColor;\n"
"uniform mat4 u_MVP;\n"
"void main()\n"
"{\n"
"   gl_Position = u_MVP * vec4(a_position, 0.0, 1.0);\n"
"	v_fragColor = a_color;\n"
"}\n";

const std::string fragcolor2d =
OGL_VARYI               " vec4 v_fragColor;\n"
OGL_FragColorDec
"void main()\n"
"{\n"
OGL_FragColor " =  v_fragColor;\n"
"}\n";

O2DColorShader::O2DColorShader()
{
    
    
}

void O2DColorShader::init()
{
    m_Name = "O2DColorShader";
    
    std::string vs = GLSLHEADER + vertcolor2d;
    std::string fs = GLSLHEADER + PRECISION_H + fragcolor2d;
    
    this->load(vs, fs);
}

void O2DColorShader::bindLocations()
{
    m_Program->bindLocation(0, "a_position");
    m_Program->bindLocation(1, "a_color");
}

void O2DColorShader::prepare(OCamera2D *camera)
{
    setUniformMat4("u_MVP", camera->getCameraMatrix());
}
NS_O_END