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

#include <map>

#include "common.h"

class BMapElement {
 public:
  BMapElement(const std::shared_ptr<BType>& data) : data_(data) {}
  ~BMapElement() {}
  BMapElement() {}
  std::shared_ptr<BType> data_;
  bool operator==(const BMapElement& rhs) const {
    return *(data_.get()) == *(rhs.data_.get());
  }

  bool operator<(const BMapElement& rhs) const {
    return *(data_.get()) < *(rhs.data_.get());
  }
};

std::map<BMapElement, BMapElement>* GetBMap(BMap obj) {
  std::shared_ptr<BTypeImpl<std::map<BMapElement, BMapElement>>>* bobj = reinterpret_cast<std::shared_ptr<BTypeImpl<std::map<BMapElement, BMapElement>>>*>(obj);
  return (*bobj)->GetObj();
}

BMap BMap_create() {
  std::shared_ptr<BTypeImpl<std::map<BMapElement,BMapElement>>>* new_obj =
      new std::shared_ptr<BTypeImpl<std::map<BMapElement,BMapElement>>>(new BTypeImpl<std::map<BMapElement, BMapElement>>());
  (*new_obj)->SetType(BTYPE_MAP);
  return reinterpret_cast<BMap>(new_obj);
}

size_t BMap_size(BMap obj) {
  return GetBMap(obj)->size();
}

void BMap_insert(BMap obj, void* key, void* val) {
  std::map<BMapElement, BMapElement>* bmap = GetBMap(obj);

  std::shared_ptr<BType>* bkey = reinterpret_cast<std::shared_ptr<BType>*>(key);
  std::shared_ptr<BType>* bval = reinterpret_cast<std::shared_ptr<BType>*>(val);

  BMapElement ekey(*bkey);

  (*bmap)[ekey].data_ = *bval;

  //bmap->insert(std::pair<BMapElement, BMapElement>(ekey, eval));
}

void* BMap_find(BMap obj, void* key) {
  std::map<BMapElement, BMapElement>* bmap = GetBMap(obj);
  std::shared_ptr<BType>* bkey = reinterpret_cast<std::shared_ptr<BType>*>(key);
  BMapElement ekey(*bkey);

  auto it = bmap->find(ekey);
  if (it == bmap->end())
    return nullptr;
  return &(it->second.data_);
}

void BMap_erase(BMap obj, void* key) {
  std::map<BMapElement, BMapElement>* bmap = GetBMap(obj);
  std::shared_ptr<BType>* bkey = reinterpret_cast<std::shared_ptr<BType>*>(key);
  BMapElement ekey(*bkey);
  bmap->erase(ekey);
}

BString BMap_createJson(BMap obj) {
  std::string json = "{";
  bool first = true;
  for (auto& i : *(GetBMap(obj)) ) {
    if (!first) {
      json += ", ";
    } else {
      first = false;
    }
    BAutoFree BString jkey = BBase_createJson((void*)&(i.first.data_));
    BAutoFree BString jval = BBase_createJson(&(i.second.data_));
    json += BString_getCStr(jkey);
    json += ":";
    json += BString_getCStr(jval);
  }
  json += "}";
  return BString_create(json.c_str());
}