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
#include <string.h>

#include <vector>

#include "common.h"

class BDataStore {
 public:
  BDataStore() {}
  ~BDataStore() {}

  bool operator==(const BDataStore& rhs) const {
    if (GetSize() != rhs.GetSize()) {
      return false;
    }
    if (memcmp(GetConstPtr(), rhs.GetConstPtr(), GetSize())) {
      return false;
    }
    return true;
  }

  bool operator<(const BDataStore& rhs) const {
    if (GetSize() < rhs.GetSize()) {
      return true;
    }
    if (memcmp(GetConstPtr(), rhs.GetConstPtr(), GetSize()) < 0) {
      return true;
    }
    return false;
  }

  void* GetPtr() {
    if (storage_.size() == 0) {
      return nullptr;
    }
    return &(storage_[0]);
  }

  const void* GetConstPtr() const {
    if (storage_.size() == 0) {
      return nullptr;
    }
    return &(storage_[0]);
  }

  void SetData(const void* data, size_t len) {
    storage_.resize(len, 0);
    if (len > 0) {
      memcpy(GetPtr(), data, len);
    }
  }

  size_t GetSize() const { return storage_.size(); }

  void Resize(size_t len) {
    storage_.resize(len, 0);
  }

 private:
  std::vector<char> storage_;
};

BDataStore* GetDataStore(BData obj) {
  std::shared_ptr<BTypeImpl<BDataStore>>* bobj =
      reinterpret_cast<std::shared_ptr<BTypeImpl<BDataStore>>*>(obj);
  return (*bobj)->GetObj();
}

BData BData_create(const void* data, size_t len) {
  std::shared_ptr<BTypeImpl<BDataStore>>* obj =
      new std::shared_ptr<BTypeImpl<BDataStore>>(new BTypeImpl<BDataStore>());
  (*obj)->SetType(BTYPE_DATA);
  BDataStore* ds = (*obj)->GetObj();
  ds->SetData(data, len);
  return reinterpret_cast<BData>(obj);
}

size_t BData_size(BData obj) {
  BDataStore* ds = GetDataStore(obj);
  return ds->GetSize();
}

void* BData_getPtr(BData obj) {
  BDataStore* ds = GetDataStore(obj);
  return ds->GetPtr();
}

void BData_resize(BData obj, size_t len) {
  BDataStore* ds = GetDataStore(obj);
  return ds->Resize(len);
}

uint8_t BData_getByte(BData obj, size_t index) {
  BDataStore* ds = GetDataStore(obj);
  if (index >= ds->GetSize()) {
    return 0;
  }
  return ((uint8_t*)ds->GetPtr())[index];
}

void BData_setData(BData obj, const void* data, size_t len) {
  BDataStore* ds = GetDataStore(obj);
  ds->SetData(data, len);
}