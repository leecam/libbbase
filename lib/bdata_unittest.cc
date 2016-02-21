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

#include <stdio.h>

#include <gtest/gtest.h>

#include <bbase/bbase.h>

static const uint8_t kTestData[] = {0xAA, 0xBB, 0xCC, 0xDD};
static const uint8_t kTestData2[] = {0x11, 0x22, 0x33, 0x44};

TEST(LibBBaseBData, EmptyCreate) {
  BAutoFree BData obj = BData_create(nullptr, 0);
  ASSERT_EQ(BTYPE_DATA, BBase_type(obj));

  ASSERT_EQ(0U, BData_size(obj));
  ASSERT_EQ(nullptr, BData_getPtr(obj));
}

TEST(LibBBaseBData, BasicCreate) {
  BAutoFree BData obj = BData_create(kTestData, sizeof(kTestData));
  ASSERT_EQ(BTYPE_DATA, BBase_type(obj));

  ASSERT_EQ(sizeof(kTestData), BData_size(obj));

  const void* ref = BData_getPtr(obj);
  ASSERT_EQ(0, memcmp(ref, kTestData, sizeof(kTestData)));
}

TEST(LibBBaseBData, SetData) {
  BAutoFree BData obj = BData_create(kTestData, sizeof(kTestData));

  BData_setData(obj, kTestData2, sizeof(kTestData2));
  ASSERT_EQ(sizeof(kTestData2), BData_size(obj));
  const void* ref = BData_getPtr(obj);
  ASSERT_EQ(0, memcmp(ref, kTestData2, sizeof(kTestData2)));
}

TEST(LibBBaseBData, Equallity) {
  BAutoFree BData obj1 = BData_create(kTestData, sizeof(kTestData));
  BAutoFree BData obj2 = BData_create(kTestData, sizeof(kTestData));
  BAutoFree BData obj3 = BData_create(kTestData2, sizeof(kTestData2));

  ASSERT_TRUE(BBase_equal(obj1, obj1));
  ASSERT_TRUE(BBase_equal(obj1, obj2));
  ASSERT_FALSE(BBase_equal(obj1, obj3));
}

TEST(LibBBaseBData, GetByte) {
  BAutoFree BData obj = BData_create(kTestData, sizeof(kTestData));

  for (size_t i = 0; i < sizeof(kTestData); i++) {
    ASSERT_EQ(kTestData[i], BData_getByte(obj, i));
  }

  ASSERT_EQ(0, BData_getByte(obj, 0xFFFFF));
}

TEST(LibBBaseBData, Resize) {
  BAutoFree BData obj = BData_create(kTestData, sizeof(kTestData));
  ASSERT_EQ(sizeof(kTestData), BData_size(obj));

  // Reduce size
  BData_resize(obj, sizeof(kTestData) - 1);
  ASSERT_EQ(sizeof(kTestData) - 1, BData_size(obj));
  ASSERT_EQ(0, memcmp(BData_getPtr(obj), kTestData, sizeof(kTestData) - 1));

  // Increase size
  BData_resize(obj, sizeof(kTestData) + 128);
  ASSERT_EQ(sizeof(kTestData) + 128, BData_size(obj));
  ASSERT_EQ(0, memcmp(BData_getPtr(obj), kTestData, sizeof(kTestData) - 1));
  for (int i = 0; i < 128; i++) {
    ASSERT_EQ(0, BData_getByte(obj, i+sizeof(kTestData)));
  }

  BData_resize(obj, 0);
  ASSERT_EQ(0U, BData_size(obj));
}
