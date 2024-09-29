LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

# Add your application source files here...
LOCAL_SRC_FILES := \
    YourSourceHere.c \
    Main.cpp

SDL_PATH := ../SDL  # SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include  # SDL

LOCAL_SHARED_LIBRARIES := SDL3

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid  # SDL
LOCAL_CPPFLAGS += -std=c++17 -fexceptions -frtti  # C++
LOCAL_LDLIBS += -lc++_shared -latomic  # C++

include $(BUILD_SHARED_LIBRARY)
