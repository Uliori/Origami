//
//  OEException.cpp
//  Katana
//
//  Created by Sephiroth on 5/21/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#include "OEException.hpp"

OEException::OEException()
{
    m_msg = "OEException";
}

OEException::OEException(const std::string& msg)
{
    this->m_msg = msg;
}

OEException::~OEException()
{
    
}

const char* OEException::what()
{
    return m_msg.c_str();
}