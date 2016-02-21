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

#ifndef LIBBBASE_LIB_COMMON_H_
#define LIBBBASE_LIB_COMMON_H_

#include <memory>
#include <string>

class BType {
 public:
  BType();
  virtual ~BType();

  virtual bool operator==(const BType& rhs) {
    printf("Comparing BType\n");
    if (type_ != rhs.GetType()) {
      return false;
    }
    return true;
  }

  virtual bool operator<(const BType& rhs) = 0;

  int GetType() const { return type_; }
  void SetType(int type) { type_ = type; }
  void SetFreeFlag(int* flag) { free_flag_ = flag; }

 private:
  int type_;
  int* free_flag_;
};

template <class T>
class BTypeImpl : public BType {
 public:
  BTypeImpl() {}
  ~BTypeImpl() override {}
  
  T* GetObj() { return &obj_; }
  const T& GetConstObj() const { return obj_;} 
  bool operator==(const BType& rhs) override {
    if (GetType() != rhs.GetType()) {
      return false;
    }
    const BTypeImpl<T>* tmp = static_cast<const BTypeImpl<T>*>(&rhs);
    return obj_ == tmp->GetConstObj();
  }

  bool operator<(const BType& rhs) override {
    if (GetType() != rhs.GetType()) {
      return false;
    }
    const BTypeImpl<T>* tmp = static_cast<const BTypeImpl<T>*>(&rhs);
    return obj_ < tmp->GetConstObj();
  }

 private:
  T obj_;
};




#endif

