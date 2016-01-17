LOCAL_PATH := $(call my-dir)

Origami_SRC_PATH		:= ../../Origami/
OrigamiCore_SRC_PATH	:= ../../Origami/Core
Game_SRC_PATH			:= ../../Game

SOIL_SRC_PATH			:= ../../Origami/Dependencies/SOIL2
#FREETYPE_HEA_PATH	 	:= ../../Origami/Dependencies/FreeType/include
#FREETYPE_SRC_PATH	 	:= ../../Origami/Dependencies/FreeType/
#FREETYPEGL_SRC_PATH	:= ../../Origami/Dependencies/FreeType-gl
#HARFBUZZ_HEA_PATH	 	:= ../../Origami/Dependencies/harfbuzz-ng/src
#HARFBUZZ_SRC_PATH	 	:= ../../Origami/Dependencies/harfbuzz-ng/

############################################ libSOIL2 ############################################
include $(CLEAR_VARS)

LOCAL_MODULE    		:= libsoil2
LOCAL_SRC_FILES			:= \
   							$(SOIL_SRC_PATH)/SOIL2/etc1_utils.c $(SOIL_SRC_PATH)/SOIL2/image_DXT.c \
							$(SOIL_SRC_PATH)/SOIL2/image_helper.c $(SOIL_SRC_PATH)/SOIL2/SOIL2.c

LOCAL_LDLIBS    		:= -lGLESv2 -lEGL

include $(BUILD_SHARED_LIBRARY)

############################################ libOrigami ############################################
include $(CLEAR_VARS)
LOCAL_MODULE   			:= origami
LOCAL_CFLAGS    		:= -std=c++11 -DO_TARGET_MOBILE -DO_TARGET_MOBILE_ANDROID -DO_MODE_DEBUG
#-g
CORE_LIST 				:= $(OrigamiCore_SRC_PATH)
PROJECT_LIST 			:= $(Game_SRC_PATH)

LOCAL_C_INCLUDES  		:=  \
							$(NDK_APP_PROJECT_PATH)/jni/$(SOIL_SRC_PATH) \
							$(NDK_APP_PROJECT_PATH)/jni/$(Origami_SRC_PATH) \
							$(NDK_APP_PROJECT_PATH)/jni/$(Game_SRC_PATH)
							#$(NDK_APP_PROJECT_PATH)/jni/$(FREETYPE_HEA_PATH) \
							$(NDK_APP_PROJECT_PATH)/jni/$(HARFBUZZ_HEA_PATH) \
							$(NDK_APP_PROJECT_PATH)/jni/$(FREETYPEGL_SRC_PATH) \


LOCAL_SRC_FILES 		:= 	Game.cpp Origami.cpp \
							$(CORE_LIST)/ODirector.cpp \
							$(CORE_LIST)/ORef.cpp \
							$(CORE_LIST)/App/OApplication.cpp \
							$(CORE_LIST)/Inputs/OInputsManager.cpp \
							$(CORE_LIST)/Maths/OMaths.cpp \
							$(CORE_LIST)/Maths/OGeometry.cpp \
							$(CORE_LIST)/Utils/OEException.cpp \
							$(CORE_LIST)/Utils/OResourceManager.cpp \
							$(CORE_LIST)/Utils/OTextureCache.cpp \
							$(CORE_LIST)/Utils/ResourcesUtils.cpp \
							$(CORE_LIST)/Utils/ShaderUtils.cpp \
							$(CORE_LIST)/Utils/TextureUtils.cpp \
							$(CORE_LIST)/Platform/Android/OApplicationAndroid.cpp \
							$(CORE_LIST)/Platform/Android/OWindowAndroid.cpp \
							$(CORE_LIST)/Graphics/OWindow.cpp \
							$(CORE_LIST)/Graphics/2D/OCamera2D.cpp \
							$(CORE_LIST)/Graphics/2D/OSprite.cpp \
							$(CORE_LIST)/Graphics/2D/OParticleBach2D.cpp \
							$(CORE_LIST)/Graphics/2D/OParticleEngine2D.cpp \
							$(CORE_LIST)/Graphics/GUI/OFont.cpp \
							$(CORE_LIST)/Graphics/GUI/OFontManager.cpp \
							$(CORE_LIST)/Graphics/GUI/OLabel.cpp \
							$(CORE_LIST)/Graphics/Layers/OLayer2D.cpp \
							$(CORE_LIST)/Graphics/Layers/OLayer3D.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORendererFactory.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORendererSpriteBatch.cpp \
							$(CORE_LIST)/Graphics/Scenes/OScene.cpp \
							$(CORE_LIST)/Graphics/Shaders/OShader.cpp \
							$(CORE_LIST)/Graphics/Shaders/OSimple2DShader.cpp \
							$(Game_SRC_PATH)/OGame.cpp \
							$(Game_SRC_PATH)/BeachScene.cpp \
							$(Game_SRC_PATH)/BeachNMScene.cpp \
							$(Game_SRC_PATH)/CloudsScene.cpp \
							$(Game_SRC_PATH)/BambooScene.cpp \
							#$(FREETYPEGL_SRC_PATH)/texture-font.cpp $(FREETYPEGL_SRC_PATH)/platform.c \
							$(FREETYPEGL_SRC_PATH)/texture-atlas.c $(FREETYPEGL_SRC_PATH)/vector.c \


LOCAL_SHARED_LIBRARIES 	:= \
							libsoil2
							#libfreetype2\
							#libharfbuzz


LOCAL_LDLIBS    		:= -landroid -lGLESv2 -lEGL -llog
# -ldl  -lz
include $(BUILD_SHARED_LIBRARY)

############################################ libFreeType2 ############################################
#include $(NDK_APP_PROJECT_PATH)/jni/$(FREETYPE_SRC_PATH)Android.mk

############################################ libHarfBuzz ############################################
#include $(NDK_APP_PROJECT_PATH)/jni/$(HARFBUZZ_SRC_PATH)Android.mk
