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
#include <bbase/bbase.h>

BMap CreateSoldierOfFortune(char* first_name, char* last_name) {
  BAutoFree BString fn_key = BString_create("FirstName");
  BAutoFree BString ln_key = BString_create("LastName");

  BAutoFree BString fn_string = BString_create(first_name);
  BAutoFree BString ln_string = BString_create(last_name);

  BMap map = BMap_create();
  BMap_insert(map, fn_key, fn_string);
  BMap_insert(map, ln_key, ln_string);
  return map;
}

int main() {
  printf("In 1972, a crack commando unit was sent to prison for a...\n");

  /* Simple BBase example creating a BVector of crack commandos.
   * Each entry of the BVector is a BMap, consisting of two
   * BString keys: "FirstName" & "LastName". The values are also
   * BStrings.
   *
   * Finally we add the BVector to a BMap. Here the key is a
   * BString and the val is a BVector. This demostrates how
   * keys and values can be of any BBase type.
   *
   * Note there is little memory managment house keeping and no
   * calls to free(). Each BBase type is free'ed automatically.
   * This program runs under valgrind with no leaks.
   *
   * Finally a call to BBase_createJson can convert any BBase
   * type to a JSON string. Here we convert the A-Team map to
   * JSON and print it.
   * This will print:
   *
   * {"A-Team":[{"FirstName":"John", "LastName":"Smith"},
   * {"FirstName":"Templeton", "LastName":"Peck"},
   * {"FirstName":"Bosco", "LastName":"Baracus"},
   * {"FirstName":"HM", "LastName":"Murdock"}]}
   */

  BAutoFree BVector commandos = BVector_create();

  BAutoFree BMap hannibal = CreateSoldierOfFortune("John", "Smith");
  BVector_pushBack(commandos, hannibal);

  BAutoFree BMap faceman = CreateSoldierOfFortune("Templeton", "Peck");
  BVector_pushBack(commandos, faceman);

  BAutoFree BMap ba = CreateSoldierOfFortune("Bosco", "Baracus");
  BVector_pushBack(commandos, ba);

  BAutoFree BMap murdock = CreateSoldierOfFortune("HM", "Murdock");
  BVector_pushBack(commandos, murdock);

  BAutoFree BMap a_team = BMap_create();
  BAutoFree BString a_team_key = BString_create("A-Team");
  BMap_insert(a_team, a_team_key, commandos);

  BAutoFree BString json = BBase_createJson(a_team);

  printf("%s\n", BString_getCStr(json));
  return 0;
}