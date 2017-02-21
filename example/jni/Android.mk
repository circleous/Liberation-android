LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := liberation
LOCAL_SRC_FILES := ../../source/obj/local/$(TARGET_ARCH_ABI)/liberation.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := demon
LOCAL_SRC_FILES := \
	../hooker.cpp
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../includes/
LOCAL_LDLIBS := -llog -latomic -ldl
LOCAL_STATIC_LIBRARIES := liberation

include $(BUILD_SHARED_LIBRARY)