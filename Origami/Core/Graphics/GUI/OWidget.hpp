/****************************************************************************
 OWidget.hpp
 
 Created by El Mehdi KHALLOUKI on 3/7/16.
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

#pragma once

#include <Core/Graphics/2D/OSprite.hpp>
#include <Core/Inputs/OInputEvents.hpp>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OWidget : public OSprite, public OInputEvents {
    
    
public:
    virtual void update(){}
    
    virtual void touchEvent(int touchID, TouchPoint::TouchEvent state, const maths::vec2& position, const maths::vec2& lastPosition) {}
    virtual bool isTouchInside(const maths::vec2& position);
};

NS_O_END

