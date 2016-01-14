/****************************************************************************
 ORef.cpp

 Created by El Mehdi KHALLOUKI on 1/12/16.
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

#include "ORef.hpp"
#include <Core/OMacros.h>
#include <Core/Utils/OLog.h>

ORef::ORef():m_ReferenceCount(1)
{

}

ORef::~ORef()
{

}

void ORef::retain()
{
    ++m_ReferenceCount;
    OLog("retaining");
}

void ORef::release()
{
    OLog("releasing");
    if (-- m_ReferenceCount == 0) {
      OLog("deleting");
      delete this;
    }
}

unsigned int ORef::getReferenceCount() const
{
    return m_ReferenceCount;
}
