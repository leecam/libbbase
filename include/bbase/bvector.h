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

#ifndef LIBBBASE_INCLUDE_BVECTOR_H_
#define LIBBBASE_INCLUDE_BVECTOR_H_

#include <stddef.h>

#include <bbase/bstring.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* BVector;

  BVector BVector_create();
  size_t BVector_size(BVector obj);
  void BVector_pushBack(BVector obj, void* val);
  void* BVector_at(BVector obj, size_t index);
  BString BVector_createJson(BVector obj);

#ifdef __cplusplus
}
#endif

#define BVECTOR_PUSH_STRING(obj, str) \
{ \
  BAutoFree BString ___tmp_str = BString_create(str); \
  BVector_pushBack(obj, ___tmp_str); \
}

#endif