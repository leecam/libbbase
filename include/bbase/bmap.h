/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBBBASE_INCLUDE_BMAP_H_
#define LIBBBASE_INCLUDE_BMAP_H_

#include <stddef.h>
#include <stdint.h>

#include <bbase/bstring.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* BMap;

  BMap BMap_create();
  size_t BMap_size(BMap obj);
  void BMap_insert(BMap obj, void* key, void* val);
  void* BMap_find(BMap obj, void* key);
  void BMap_erase(BMap obj, void* key);
  BString BMap_createJson(BMap obj);

#ifdef __cplusplus
}
#endif

#endif