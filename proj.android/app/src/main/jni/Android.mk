LOCAL_PATH := $(call my-dir)
MY_LOCAL_PATH := $(call my-dir)

Origami_SRC_PATH		:= ../../../../../Origami/
OrigamiCore_SRC_PATH	:= ../../../../../Origami/Core
Game_SRC_PATH			:= ../../../../../Game/AppSrc

SOIL_SRC_PATH			:= ../../../../../Origami/Dependencies/SOIL2
BOX2D_HEA_PATH	 		:= ../../../../../Origami/Dependencies/Box2D
BOX2D_SRC_PATH	 		:= ../../../../../Origami/Dependencies/Box2D/Box2D/
FREETYPE_HEA_PATH	 	:= ../../../../../Origami/Dependencies/FreeType/include
FREETYPE_SRC_PATH	 	:= ../../../../../Origami/Dependencies/FreeType/
FREETYPEGL_SRC_PATH		:= ../../../../../Origami/Dependencies/FreeType-gl
#HARFBUZZ_HEA_PATH	 	:= ../../../../../Origami/Dependencies/harfbuzz-ng/src
#HARFBUZZ_SRC_PATH	 	:= ../../../../../Origami/Dependencies/harfbuzz-ng/

############################################ libSOIL2 ############################################
include $(CLEAR_VARS)

LOCAL_MODULE    		:= soil2
LOCAL_SRC_FILES			:= \
   							$(SOIL_SRC_PATH)/SOIL2/etc1_utils.c $(SOIL_SRC_PATH)/SOIL2/image_DXT.c \
							$(SOIL_SRC_PATH)/SOIL2/image_helper.c $(SOIL_SRC_PATH)/SOIL2/SOIL2.c

include $(BUILD_STATIC_LIBRARY)

############################################ libOrigami ############################################
include $(CLEAR_VARS)
LOCAL_MODULE   			:= origami
LOCAL_CFLAGS    		:= -DO_TARGET_MOBILE -DO_TARGET_MOBILE_ANDROID -DO_MODE_DEBUG
#-g
CORE_LIST 				:= $(OrigamiCore_SRC_PATH)
PROJECT_LIST 			:= $(Game_SRC_PATH)
GAME_SRC_LIST 			:= $(wildcard $(LOCAL_PATH)/$(Game_SRC_PATH)/*.cpp)

LOCAL_C_INCLUDES  		:=  \
							$(LOCAL_PATH)/native_app_glue \
							$(LOCAL_PATH)/$(SOIL_SRC_PATH) \
							$(LOCAL_PATH)/$(BOX2D_HEA_PATH) \
							$(LOCAL_PATH)/$(FREETYPE_HEA_PATH) \
                            $(LOCAL_PATH)/$(FREETYPEGL_SRC_PATH) \
							$(LOCAL_PATH)/$(Origami_SRC_PATH) \
							$(LOCAL_PATH)/$(Game_SRC_PATH)\
							$(NDK_APP_PROJECT_PATH)/jni/$(HARFBUZZ_HEA_PATH) \



LOCAL_SRC_FILES 		:= 	main.cpp \
							Game.cpp \
                            native_engine.cpp \
							native_app_glue/android_native_app_glue.c \
							$(CORE_LIST)/ODirector.cpp \
							$(CORE_LIST)/ORef.cpp \
							$(CORE_LIST)/App/OApplication.cpp \
							$(CORE_LIST)/Embedded/Embedded.cpp \
							$(CORE_LIST)/Inputs/OInputsManager.cpp \
							$(CORE_LIST)/Maths/OMaths.cpp \
							$(CORE_LIST)/Maths/OGeometry.cpp \
							$(CORE_LIST)/Physics/2D/B2DDebugDraw.cpp \
							$(CORE_LIST)/Physics/2D/OB2DSprite.cpp \
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
							$(CORE_LIST)/Graphics/GUI/OWidget.cpp \
							$(CORE_LIST)/Graphics/GUI/OLabel.cpp \
							$(CORE_LIST)/Graphics/GUI/OButton.cpp \
							$(CORE_LIST)/Graphics/Layers/OLayerGUI.cpp \
							$(CORE_LIST)/Graphics/Layers/OLayer2D.cpp \
							$(CORE_LIST)/Graphics/Layers/OLayer3D.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORenderer2D.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORendererFactory.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORendererPrimitives.cpp \
							$(CORE_LIST)/Graphics/Renderers/ORendererSpriteBatch.cpp \
							$(CORE_LIST)/Graphics/Scenes/OScene.cpp \
							$(CORE_LIST)/Graphics/Shaders/OShader.cpp \
							$(CORE_LIST)/Graphics/Shaders/OTextShader.cpp \
							$(CORE_LIST)/Graphics/Shaders/O2DColorShader.cpp \
							$(CORE_LIST)/Graphics/Shaders/O2DTextureShader.cpp \
							$(FREETYPEGL_SRC_PATH)/texture-font.cpp $(FREETYPEGL_SRC_PATH)/platform.c \
							$(FREETYPEGL_SRC_PATH)/texture-atlas.c $(FREETYPEGL_SRC_PATH)/vector.c \
							$(GAME_SRC_LIST:$(LOCAL_PATH)/%=%)\

LOCAL_STATIC_LIBRARIES  := soil2 box2d_static freetype2_static
#LOCAL_SHARED_LIBRARIES 	:=
							#libharfbuzz


LOCAL_LDLIBS    		:= -landroid -lGLESv2 -lEGL -llog
# -ldl  -lz
include $(BUILD_SHARED_LIBRARY)

############################################ libBox2D   ############################################
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/$(BOX2D_SRC_PATH)Android.mk

############################################ libFreeType2 ##########################################
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/$(FREETYPE_SRC_PATH)Android.mk

############################################ libHarfBuzz ############################################
#include $(NDK_APP_PROJECT_PATH)/jni/$(HARFBUZZ_SRC_PATH)Android.mk
