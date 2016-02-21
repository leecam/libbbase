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

#include "common.h"

#include <stdio.h>

#include <bbase/bbase.h>

BType::BType() : type_(BTYPE_INVALID), free_flag_(nullptr) {
}

BType::~BType() {
  if (free_flag_) {
    *free_flag_ = 1;
  }
}

void BBase_autoFree(void* obj) {
  void** p = (void**)obj;
  BBase_free(*p);
}

void BBase_free(void* obj) {
  std::shared_ptr<BType>* bobj = reinterpret_cast<std::shared_ptr<BType>*>(obj);
  delete bobj;
}

int BBase_equal(void* lhs, void* rhs) {
  std::shared_ptr<BType>* blhs = reinterpret_cast<std::shared_ptr<BType>*>(lhs);
  std::shared_ptr<BType>* brhs = reinterpret_cast<std::shared_ptr<BType>*>(rhs);
  return *(blhs->get()) == *(brhs->get());
}

int BBase_type(void* obj) {
  std::shared_ptr<BType>* bobj = reinterpret_cast<std::shared_ptr<BType>*>(obj);
  return (*bobj)->GetType();
}

void BBase_setFreeFlag(void* obj, int* flag) {
  std::shared_ptr<BType>* bobj = reinterpret_cast<std::shared_ptr<BType>*>(obj);
  (*bobj)->SetFreeFlag(flag);
}

BString BBase_createJson(void* obj) {
  std::shared_ptr<BType>* bobj = reinterpret_cast<std::shared_ptr<BType>*>(obj);
  switch((*bobj)->GetType()) {
    case BTYPE_STRING:
      return BString_createJson(obj);
    case BTYPE_VECTOR:
      return BVector_createJson(obj);
    case BTYPE_DATA:
      break;
    case BTYPE_NUMBER:
      break;
    case BTYPE_MAP:
      return BMap_createJson(obj);
    default:
      return nullptr;
  }
  return nullptr;
}

