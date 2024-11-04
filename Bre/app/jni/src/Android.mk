LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

# Add your application source files here...
LOCAL_SRC_FILES := \
    YourSourceHere.c \
    Main.cpp \
    controller/systems/InGameEventSystem.cpp # This cpp is necessary to avoid cyclic dependencies

SDL_PATH := ../SDL  # SDL
SDL_IMAGE_PATH := ../SDL_image  # SDL_image
SDL_TTF_PATH := ../SDL_ttf  # SDL_ttf

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include  # SDL
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_IMAGE_PATH)/include  # SDL_image
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_TTF_PATH)/include  # SDL_ttf

LOCAL_SHARED_LIBRARIES := SDL3
LOCAL_SHARED_LIBRARIES += SDL3_image
LOCAL_SHARED_LIBRARIES += SDL3_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid  # SDL
LOCAL_CPPFLAGS += -std=c++17 -fexceptions -frtti  # C++
LOCAL_LDLIBS += -lc++_shared -latomic  # C++

include $(BUILD_SHARED_LIBRARY)
