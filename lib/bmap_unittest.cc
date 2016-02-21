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

TEST(LibBBaseBMap, BasicCreate) {  
  BAutoFree BMap obj = BMap_create();
  ASSERT_EQ(BTYPE_MAP, BBase_type(obj));
  ASSERT_EQ(0U, BMap_size(obj));
}

TEST(LibBBaseBMap, SimpleAdd) {  
  BAutoFree BMap obj = BMap_create();
  BAutoFree BString key = BString_create(kTestString);
  BAutoFree BString val = BString_create(kTestString);

  ASSERT_EQ(0U, BMap_size(obj));
  BMap_insert(obj, key, val);
  ASSERT_EQ(1U, BMap_size(obj));  
}

TEST(LibBBaseBMap, AddTwo) {  
  BAutoFree BMap obj = BMap_create();
  BAutoFree BString key1 = BString_create("Key1");
  BAutoFree BString key2 = BString_create("Key2");
  BAutoFree BString val1 = BString_create("Val1");
  BAutoFree BString val2 = BString_create("Val2");

  ASSERT_EQ(0U, BMap_size(obj));
  BMap_insert(obj, key1, val1);
  BMap_insert(obj, key2, val2);
  ASSERT_EQ(2U, BMap_size(obj));

  BString ref1 = BMap_find(obj, key1);
  ASSERT_TRUE(BBase_equal(ref1, val1));
  BString ref2 = BMap_find(obj, key2);
  ASSERT_TRUE(BBase_equal(ref2, val2));
}

TEST(LibBBaseBMap, NotFound) {  
  BAutoFree BMap obj = BMap_create();
  BAutoFree BString key1 = BString_create("Key1");
  BAutoFree BString val1 = BString_create("Val1");
  BAutoFree BString bad1 = BString_create("Bad1");

  BMap_insert(obj, key1, val1);

  BString ref1 = BMap_find(obj, key1);
  ASSERT_TRUE(BBase_equal(ref1, val1));
  
  BString ref2 = BMap_find(obj, bad1);
  ASSERT_EQ(nullptr, ref2);
}

TEST(LibBBaseBMap, DoubleAdd) {  
  BAutoFree BMap obj = BMap_create();
  BAutoFree BString key1 = BString_create("Key1");
  BAutoFree BString val1 = BString_create("Val1");
  BAutoFree BString val2 = BString_create("Val2");

  BMap_insert(obj, key1, val1);
  ASSERT_EQ(1U, BMap_size(obj));

  BMap_insert(obj, key1, val2);
  ASSERT_EQ(1U, BMap_size(obj));

  BString ref1 = BMap_find(obj, key1);
  ASSERT_TRUE(BBase_equal(ref1, val2));
}

TEST(LibBBaseBMap, Erase) {  
  BAutoFree BMap obj = BMap_create();
  BAutoFree BString key = BString_create("Key1");
  BAutoFree BString val = BString_create("Val1");

  ASSERT_EQ(0U, BMap_size(obj));
  BMap_insert(obj, key, val);
  ASSERT_EQ(1U, BMap_size(obj));
  BMap_erase(obj, key);
  ASSERT_EQ(0U, BMap_size(obj));
}



