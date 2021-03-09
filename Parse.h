#pragma once
#include "Jstruct.h"
#include "BaseInterface.h"
#include "Value.h"
/*
using boolen = bool;
using number = double;
using Json = map<string, BaseInterface*>; //Json
using numberarray = vector<double>;//数值数组
using strarray = vector<string>;//字符串数组
using Jsonarray = vector<Json>;//Json数组

*/
class Parse
{
	Jstruct& m_deq;
	string m_text;
public:
	Parse(const string& text,Jstruct& deq);
	~Parse() {};

private:
	/*	some tools*/
	//数据段的类型
	lept_type witch_type(const string& part);
	/*对Json文本切片*/
	vector<string> splict(const string& str,const char fix);
	//Json文本或key值，string值初始化   “key”==> key   "string" ==> string  {"key":value} ==> key : value
	string text_init(const string& text,const char left,const char right);
private:
	/*
		每一个BaseInterface都是new出来的（包括嵌套） 需要在Jstruct中释放，避免内存泄漏！
	*/
	pair<string,BaseInterface* >  parse_bool(const string& str);

	pair<string, BaseInterface* > parse_double(const string& str);

	pair<string, BaseInterface* > parse_string(const string& str);

	pair<string, BaseInterface* > parse_array(const string& str);

	// return valuetype --- <string,Json>
	pair<string, BaseInterface* > parse_object(const string& str);
};

