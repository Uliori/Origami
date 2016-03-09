/****************************************************************************
 OLayerGUI.hpp
 
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



#include <vector>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OWidget;
class ORenderer2D;
class OCamera2D;

class OLayerGUI {
    friend class ODirector;
private:
    
    std::vector<OWidget *> m_Renderables;
    
    ORenderer2D* m_CurrentRenderer    = nullptr;
    OCamera2D* m_Camera               = nullptr;
    
public:
    OLayerGUI();
    
    virtual ~OLayerGUI();
    
    inline void addSubview(OWidget* sprite) {m_Renderables.push_back(sprite);}
    inline void setRenderer(ORenderer2D* renderer) { m_CurrentRenderer = renderer; }
    
    inline OCamera2D* getCamera() const { return m_Camera; }
    
    virtual void create();
    virtual void clear();
    virtual void updateResolution();
    virtual void update(float deltaTime);
    virtual void render(float interpolation);
    
};
NS_O_END
