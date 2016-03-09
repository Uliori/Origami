//
//  OLayer2D.hpp
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 10/13/15.
//
//

#pragma once

#include <Core/Graphics/2D/OCamera2D.hpp>

#include <Core/Graphics/Renderers/ORenderer2D.hpp>
#include <Core/Graphics/2D/OSprite.hpp>
#include <Core/Graphics/2D/OParticleEngine2D.hpp>

#include <vector>

#include <Core/OMacros.hpp>

NS_O_BEGIN

class OLayer2D {
private:

    std::vector<OSprite *> m_Renderables;

    ORenderer2D* m_CurrentRenderer    = nullptr;
    OCamera2D* m_Camera               = nullptr;
public:
    OParticleEngine2D *particleEngine = nullptr;

public:
    OLayer2D();
    OLayer2D(ORenderer2D* renderer);

    virtual ~OLayer2D();

    inline void addSprite(OSprite* sprite) {m_Renderables.push_back(sprite);}

    inline void setRenderer(ORenderer2D* renderer) { m_CurrentRenderer = renderer; }

    inline OCamera2D* getCamera() const { return m_Camera; }

    virtual void create();
    virtual void clear();
    virtual void updateResolution();
    virtual void update(float deltaTime);
    virtual void render(float interpolation);

};
NS_O_END
