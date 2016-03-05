//
//  OTouchInputs.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 3/3/16.
//
//

#pragma once

#include <Core/OMacros.hpp>
#include "OInputsManager.hpp"

NS_O_BEGIN

class OTouchInputs {
    
public:
    virtual void touchEvent(int touchID, TouchPoint::TouchEvent state, const maths::vec2& position, const maths::vec2& lastPosition) {}
};

NS_O_END