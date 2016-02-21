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

static const char kTestString[] = "FingersCrossed";
static const char kTestString2[] = "FOO";

TEST(LibBBaseBVector, BasicCreate) {  
  BAutoFree BVector obj = BVector_create();
  ASSERT_EQ(BTYPE_VECTOR, BBase_type(obj));
  ASSERT_EQ(0U, BVector_size(obj));
}

TEST(LibBBaseBVector, PushString) {  
  BAutoFree BVector obj = BVector_create();
  BAutoFree BString str_obj = BString_create(kTestString);
  
  BVector_pushBack(obj, str_obj);
  ASSERT_EQ(1U, BVector_size(obj));

  BString ref = BVector_at(obj, 0);
  ASSERT_NE(nullptr, ref);
  ASSERT_TRUE(BBase_equal(str_obj, ref));
}

TEST(LibBBaseBVector, BadAt) {  
  BAutoFree BVector obj = BVector_create();
  BAutoFree BString str_obj = BString_create(kTestString);
  
  BVector_pushBack(obj, str_obj);
  BVector_pushBack(obj, str_obj);

  ASSERT_EQ(2U, BVector_size(obj));

  ASSERT_NE(nullptr, BVector_at(obj, 0));
  ASSERT_NE(nullptr, BVector_at(obj, 1));
  ASSERT_EQ(nullptr, BVector_at(obj, 2));
  ASSERT_EQ(nullptr, BVector_at(obj, 3));
}

TEST(LibBBaseBVector, FreeingSimple) {
  int flag = 0;
  BVector obj = BVector_create();
  
  BString str_obj = BString_create(kTestString);
  BBase_setFreeFlag(str_obj, &flag);
  BVector_pushBack(obj, str_obj);

  BBase_free(str_obj);
  // Vector should hold a reference
  ASSERT_EQ(0, flag);

  BBase_free(obj);
  // String should be free'ed with vector
  ASSERT_EQ(1, flag);
}

TEST(LibBBaseBVector, FreeingDoubleRef) {
  int flag = 0;
  BVector obj = BVector_create();
  
  BString str_obj = BString_create(kTestString);
  BBase_setFreeFlag(str_obj, &flag);
  BVector_pushBack(obj, str_obj);
  BVector_pushBack(obj, str_obj);

  BBase_free(str_obj);
  // Vector should hold two references
  ASSERT_EQ(0, flag);

  BBase_free(obj);
  // String should be free'ed with vector
  ASSERT_EQ(1, flag);
}

TEST(LibBBaseBVector, FreeingVectorFirst) {
  int flag = 0;
  BVector obj = BVector_create();
  
  BString str_obj = BString_create(kTestString);
  BBase_setFreeFlag(str_obj, &flag);
  BVector_pushBack(obj, str_obj);

  BBase_free(obj);
  // str_obj should still hold a ref
  ASSERT_EQ(0, flag);

  BBase_free(str_obj);
  ASSERT_EQ(1, flag);
}

TEST(LibBBaseBVector, EquallityEmpty) {
  BAutoFree BVector obj1 = BVector_create();
  BAutoFree BVector obj2 = BVector_create();
  
  ASSERT_TRUE(BBase_equal(obj1, obj1));
  ASSERT_TRUE(BBase_equal(obj1, obj2));
}


TEST(LibBBaseBVector, EquallityOneString) {
  BAutoFree BVector obj1 = BVector_create();
  BAutoFree BVector obj2 = BVector_create();
  
  BAutoFree BString str_obj = BString_create(kTestString);
  BVector_pushBack(obj1, str_obj);
  ASSERT_FALSE(BBase_equal(obj1, obj2));

  BVector_pushBack(obj2, str_obj);
  ASSERT_TRUE(BBase_equal(obj1, obj2));
}

TEST(LibBBaseBVector, EquallityOneStringSeperateRefs) {
  BAutoFree BVector obj1 = BVector_create();
  BAutoFree BVector obj2 = BVector_create();
  
  BAutoFree BString str_obj1 = BString_create(kTestString);
  BAutoFree BString str_obj2 = BString_create(kTestString);
  
  BVector_pushBack(obj1, str_obj1);
  BVector_pushBack(obj2, str_obj2);
  ASSERT_TRUE(BBase_equal(obj1, obj2));
}
