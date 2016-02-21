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

TEST(LibBBaseCommon, Freeing) {
  int flag = 0;
  
  BString obj = BString_create(kTestString);
  BBase_setFreeFlag(obj, &flag);
  ASSERT_EQ(flag, 0);
  
  BBase_free(obj);
  ASSERT_EQ(flag, 1);
}

TEST(LibBBaseCommon, AutoFree) {
  int flag = 0;
  {
    BAutoFree BString obj = BString_create(kTestString);
    BBase_setFreeFlag(obj, &flag);
  }
  ASSERT_EQ(flag, 1);
}

TEST(LibBBaseCommon, TypeEquality) {
  BAutoFree BString obj1 = BString_create(kTestString);
  BAutoFree BVector obj2 = BVector_create();
  ASSERT_FALSE(BBase_equal(obj1, obj2));
}