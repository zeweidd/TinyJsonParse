#pragma once
#include "BaseInterface.h"
/*
	用一个自定义类管理解析后的数据，实际是对map的一个封装
*/
class Jstruct
{
	Json k_v;
public:
	BaseInterface* find(const string& k);
	void insert(pair<string,BaseInterface*>);
public:
	~Jstruct(); //根据BaseInterface->get_type() 函数获取Value类型决定析构方式
private:
	void Myfree(pair<string, BaseInterface*>);
};

