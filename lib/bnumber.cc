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

#include "common.h"

class BNumberStore {
 public:
  BNumberStore() : base_type_(NumberTypes::U32), u32val_(0) {}
  ~BNumberStore() {}

  bool operator==(const BNumberStore& rhs) const {
    (void)rhs;
    return true;
  }

  bool operator<(const BNumberStore& rhs) const {
    (void)rhs;
    return true;
  }

  template<typename B> 
  B ConvertVal() {
    switch(base_type_) {
      case NumberTypes::U32:
        return (B)u32val_;
        break;
      case NumberTypes::S32:
        return (B)s32val_;
        break;
      default:
        return 0;
    }
    return 0;
  }

  void SetU32(uint32_t val) {
    u32val_ = val;
    base_type_ = NumberTypes::U32;
  }

  uint32_t GetU32() {
    return ConvertVal<uint32_t>();
  }

  void SetS32(int32_t val) {
    s32val_ = val;
    base_type_ = NumberTypes::S32;
  }

  uint32_t GetS32() {
    return ConvertVal<int32_t>();
  }

 private:
  enum class NumberTypes {U32, S32, FLOAT};
  NumberTypes base_type_;
  union {
    uint32_t u32val_;
    int32_t s32val_;
  };
};

BNumberStore* GetNumberStore(BData obj) {
  std::shared_ptr<BTypeImpl<BNumberStore>>* bobj =
      reinterpret_cast<std::shared_ptr<BTypeImpl<BNumberStore>>*>(obj);
  return (*bobj)->GetObj();
}

BNumber BNumber_createU32(uint32_t val) {
  std::shared_ptr<BTypeImpl<BNumberStore>>* obj =
      new std::shared_ptr<BTypeImpl<BNumberStore>>(new BTypeImpl<BNumberStore>());
  (*obj)->SetType(BTYPE_NUMBER);
  (void)val;
  BNumberStore* ns = (*obj)->GetObj();
  ns->SetU32(val);
  return reinterpret_cast<BNumber>(obj);
}

BNumber BNumber_createS32(int32_t val) {
  (void)val;
  return nullptr;
}

uint32_t BNumber_getU32(BNumber obj) {
  BNumberStore* ns = GetNumberStore(obj);
  return ns->GetU32();
}

int32_t BNumber_getS32(BNumber obj) {
  BNumberStore* ns = GetNumberStore(obj);
  return ns->GetS32();
}
