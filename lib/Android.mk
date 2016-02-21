#
# Copyright (C) 2016 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

libbbase_CommonCFlags := -Wall -Werror
libbbase_CommonCIncludes := $(LOCAL_PATH)/../include

# libbbase shared library
# ========================================================

include $(CLEAR_VARS)
LOCAL_MODULE := libbbase
LOCAL_CPP_EXTENSION := .cc
LOCAL_CFLAGS := $(libbbase_CommonCFlags)
LOCAL_C_INCLUDES := $(libbbase_CommonCIncludes)
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/../include
LOCAL_SRC_FILES := \
  bdata.cc \
  bmap.cc \
  bnumber.cc \
  bstring.cc \
  bvector.cc \
  common.cc \

include $(BUILD_HOST_SHARED_LIBRARY)


# libbbase unitests
# ========================================================

include $(CLEAR_VARS)
LOCAL_MODULE := libbbase_unittests
ifdef BRILLO
  LOCAL_MODULE_TAGS := debug
endif
LOCAL_CPP_EXTENSION := .cc
LOCAL_SHARED_LIBRARIES := libbbase
LOCAL_SRC_FILES := \
  bdata_unittest.cc \
  bmap_unittest.cc \
  bnumber_unittest.cc \
  bstring_unittest.cc \
  bvector_unittest.cc \
  common_unittest.cc \

include $(BUILD_HOST_NATIVE_TEST)