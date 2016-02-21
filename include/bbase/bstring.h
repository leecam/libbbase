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

#ifndef LIBBBASE_INCLUDE_BSTRING_H_
#define LIBBBASE_INCLUDE_BSTRING_H_

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* BString;

  BString BString_create(const char* str);
  const char* BString_getCStr(BString obj);
  BString BString_createJson(BString obj);

#ifdef __cplusplus
}
#endif

#endif