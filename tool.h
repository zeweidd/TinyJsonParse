#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>
using namespace std;
constexpr bool DEBUG = true;
typedef enum {
LEPT_BOOL, 
LEPT_STRING, 
LEPT_ARRAY, 
LEPT_OBJECT_ARRAY,
LEPT_OBJECT, 
LEPT_NULL, 
LEPT_NUMBER
} lept_type;

struct BaseInterface;
using boolen = bool;
using number = double;
using String = string;
using Json = map<string, BaseInterface*>; //Json
using numberarray = vector<double>;//数值数组
using strarray = vector<string>;//字符串数组
using Jsonarray = vector<Json>;//Json数组
