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

TEST(LibBBaseBString, BasicCreate) {  
  BAutoFree BString obj = BString_create(kTestString);
  ASSERT_EQ(BTYPE_STRING, BBase_type(obj));

  const char* c_string = BString_getCStr(obj);
  ASSERT_EQ(0, strcmp(kTestString, c_string));
}

TEST(LibBBaseBString, Equallity) {  
  BAutoFree BString obj1 = BString_create(kTestString);
  BAutoFree BString obj2 = BString_create(kTestString);
  BAutoFree BString obj3 = BString_create(kTestString2);
  
  ASSERT_TRUE(BBase_equal(obj1, obj1));
  ASSERT_TRUE(BBase_equal(obj1, obj2));
  ASSERT_FALSE(BBase_equal(obj1, obj3));
}
