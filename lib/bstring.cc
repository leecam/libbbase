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

#include <bbase/bbase.h>

#include <stdio.h>

#include <string>

#include "common.h"

std::string* GetString(BString obj) {
  std::shared_ptr<BTypeImpl<std::string>>* bstr = reinterpret_cast<std::shared_ptr<BTypeImpl<std::string>>*>(obj);
  return (*bstr)->GetObj();
}

BString BString_create(const char* str) {
  std::shared_ptr<BTypeImpl<std::string>>* new_string =
      new std::shared_ptr<BTypeImpl<std::string>>(new BTypeImpl<std::string>());
  (*new_string)->SetType(BTYPE_STRING);
  *((*new_string)->GetObj()) = str;
  return reinterpret_cast<BString>(new_string);
}

const char* BString_getCStr(BString obj) {
  return GetString(obj)->c_str();
}

BString BString_createJson(BString obj) {
  std::string json = "\"" + *(GetString(obj)) + "\"";
  return BString_create(json.c_str());
}

