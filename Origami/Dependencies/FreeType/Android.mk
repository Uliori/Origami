LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libfreetype2_static

LOCAL_SRC_FILES:= \
	src/base/ftbbox.c src/base/ftbitmap.c src/base/ftfstype.c \
	src/base/ftglyph.c src/base/ftlcdfil.c src/base/ftstroke.c \
	src/base/fttype1.c src/base/ftxf86.c src/base/ftbase.c \
	src/base/ftsystem.c src/base/ftinit.c src/base/ftgasp.c \
	src/raster/raster.c src/sfnt/sfnt.c src/smooth/smooth.c \
	src/autofit/autofit.c src/truetype/truetype.c \
	src/cff/cff.c src/psnames/psnames.c src/pshinter/pshinter.c \

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_CFLAGS += -W -Wall
LOCAL_CFLAGS += -fPIC -DPIC
LOCAL_CFLAGS += "-DDARWIN_NO_CARBON"
LOCAL_CFLAGS += "-DFT2_BUILD_LIBRARY"

include $(BUILD_STATIC_LIBRARY)
