//
//  Origami.h
//  Origami
//
//  Created by El Mehdi KHALLOUKI on 2/3/16.
//
//

#pragma once

#include <Core/Utils/OGLUtils.hpp>

#include <Core/OTypes.hpp>
#include <Core/ODirector.hpp>
#include <Core/ORef.hpp>

#include <Core/Utils/cpp14Ext.hpp>

//App folder
#include <Core/App/OApplication.hpp>

//Graphics folder
#include <Core/Graphics/OTexture.hpp>
#include <Core/Graphics/OColorRGBA8.hpp>
#include <Core/Graphics/OWindow.hpp>

//Graphics/2D folder
#include <Core/Graphics/2D/Vertex2D.hpp>
#include <Core/Graphics/2D/OSprite.hpp>
#include <Core/Graphics/2D/OCamera2D.hpp>
#include <Core/Graphics/2D/OParticleBatch2D.hpp>
#include <Core/Graphics/2D/OParticleEngine2D.hpp>

//Graphics/3D folder

//Graphics/GUI folder
#include <Core/Graphics/GUI/OFont.hpp>
#include <Core/Graphics/GUI/OFontManager.hpp>
#include <Core/Graphics/GUI/OLabel.hpp>

//Graphics/Layers folder
#include <Core/Graphics/Layers/OLayer2D.hpp>
#include <Core/Graphics/Layers/OLayer3D.hpp>

//Graphics/Scenes folder
#include <Core/Graphics/Scenes/OScene.hpp>

//Graphics/Renderers folder
#include <Core/Graphics/Renderers/ORenderer2D.hpp>
#include <Core/Graphics/Renderers/ORendererFactory.hpp>
#include <Core/Graphics/Renderers/ORendererSpriteBatch.hpp>

//Graphics/Shaders folder
#include <Core/Graphics/Shaders/program.hpp>
#include <Core/Graphics/Shaders/OShader.hpp>
#include <Core/Graphics/Shaders/O2DColorShader.hpp>
#include <Core/Graphics/Shaders/O2DTextureShader.hpp>

//Maths folder
#include <Core/Maths/OMaths.hpp>
#include <Core/Maths/OGeometry.hpp>

//Physics folder
#include <Core/Physics/2D/B2DDebugDraw.hpp>
#include <Core/Physics/2D/OB2DSprite.hpp>
#include <Core/Physics/2D/O2DPhysics.hpp>

//Inputs folder
#include <Core/Inputs/OInputsManager.hpp>

//Utils Folder
#include <Core/Utils/OEException.hpp>
#include <Core/Utils/OResourceManager.hpp>
#include <Core/Utils/OTextureCache.hpp>
#include <Core/Utils/OTime.hpp>
#include <Core/Utils/ResourcesUtils.hpp>
#include <Core/Utils/ShaderUtils.hpp>
#include <Core/Utils/TextureUtils.hpp>
