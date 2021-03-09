#pragma once
#include "Jstruct.h"
#include "BaseInterface.h"
#include "Value.h"
/*
using boolen = bool;
using number = double;
using Json = map<string, BaseInterface*>; //Json
using numberarray = vector<double>;//��ֵ����
using strarray = vector<string>;//�ַ�������
using Jsonarray = vector<Json>;//Json����

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
	//���ݶε�����
	lept_type witch_type(const string& part);
	/*��Json�ı���Ƭ*/
	vector<string> splict(const string& str,const char fix);
	//Json�ı���keyֵ��stringֵ��ʼ��   ��key��==> key   "string" ==> string  {"key":value} ==> key : value
	string text_init(const string& text,const char left,const char right);
private:
	/*
		ÿһ��BaseInterface����new�����ģ�����Ƕ�ף� ��Ҫ��Jstruct���ͷţ������ڴ�й©��
	*/
	pair<string,BaseInterface* >  parse_bool(const string& str);

	pair<string, BaseInterface* > parse_double(const string& str);

	pair<string, BaseInterface* > parse_string(const string& str);

	pair<string, BaseInterface* > parse_array(const string& str);

	// return valuetype --- <string,Json>
	pair<string, BaseInterface* > parse_object(const string& str);
};

