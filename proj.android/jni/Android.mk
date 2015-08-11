LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/CustomFollow.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/Stage.cpp \
                   ../../Classes/VirtualPad.cpp \
                   ../../Classes/Enemy.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES +=cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static       
include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
$(call import-module,editor-support/cocostudio)        
#$(call import-module,.)