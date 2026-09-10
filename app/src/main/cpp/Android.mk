LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := libtermux-bootstrap
LOCAL_SRC_FILES := termux-bootstrap-zip.S termux-bootstrap.c
LOCAL_ASMFLAGS += -I$(LOCAL_PATH)
include $(BUILD_SHARED_LIBRARY)
