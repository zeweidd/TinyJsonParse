#pragma once
#include "BaseInterface.h"
/*
	��һ���Զ�����������������ݣ�ʵ���Ƕ�map��һ����װ
*/
class Jstruct
{
	Json k_v;
public:
	BaseInterface* find(const string& k);
	void insert(pair<string,BaseInterface*>);
public:
	~Jstruct(); //����BaseInterface->get_type() ������ȡValue���;���������ʽ
private:
	void Myfree(pair<string, BaseInterface*>);
};

