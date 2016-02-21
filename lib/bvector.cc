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

#include <string>
#include <vector>

#include "common.h"

class BVectorElement {
 public:
  BVectorElement(const std::shared_ptr<BType>& data) : data_(data) {}
  ~BVectorElement() {}
  std::shared_ptr<BType> data_;
  bool operator==(const BVectorElement& rhs) const {
    printf("element compare\n");
    return *(data_.get()) == *(rhs.data_.get());
  }

  bool operator<(const BVectorElement& rhs) const {
    printf("element < compare\n");
    return *(data_.get()) < *(rhs.data_.get());
  }
};

std::vector<BVectorElement>* GetVector(BVector obj) {
  std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>* bobj = reinterpret_cast<std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>*>(obj);
  return (*bobj)->GetObj();
}

BVector BVector_create() {
  std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>* new_obj =
      new std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>(new BTypeImpl<std::vector<BVectorElement>>());
  (*new_obj)->SetType(BTYPE_VECTOR);
  return reinterpret_cast<BVector>(new_obj);
}

size_t BVector_size(BVector obj) {
  std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>* bobj = reinterpret_cast<std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>*>(obj);
  std::vector<BVectorElement>* vec = (*bobj)->GetObj();
  return vec->size();
}

void BVector_pushBack(BVector obj, void* val) {
  std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>* bobj = reinterpret_cast<std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>*>(obj);
  std::vector<BVectorElement>* vec = (*bobj)->GetObj();
  std::shared_ptr<BType>* bval = reinterpret_cast<std::shared_ptr<BType>*>(val);
  BVectorElement test(*bval);
  vec->push_back(test);
}

void* BVector_at(BVector obj, size_t index) {
  std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>* bobj = reinterpret_cast<std::shared_ptr<BTypeImpl<std::vector<BVectorElement>>>*>(obj);
  std::vector<BVectorElement>* vec = (*bobj)->GetObj();
  if (index >= vec->size()) {
    return nullptr;
  }

  return reinterpret_cast<void*>(&(vec->at(index).data_)); 
}

BString BVector_createJson(BVector obj) {
  std::vector<BVectorElement>* vec = GetVector(obj);
  std::string json = "[";
  bool first = true;
  for (auto& i : *vec) {
    if (!first) {
      json += ", ";
    } else {
      first = false;
    }
    BAutoFree BString jelement = BBase_createJson(&(i.data_));
    json += BString_getCStr(jelement);
  }

  json += "]";

  return BString_create(json.c_str());
}