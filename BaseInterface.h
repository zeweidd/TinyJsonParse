#pragma once
#include "tool.h"

struct BaseInterface
{
	//����ת����������ʵ�֡�ͨ������ֵ���غ�����
	virtual operator number() { return number(); };
	virtual operator boolen() {return boolen();};
	virtual operator string() { return string(); };
	virtual operator Json() { return Json(); };
	virtual operator numberarray() { return numberarray(); };
	virtual operator strarray() { return strarray(); };
	virtual operator Jsonarray() { return Jsonarray(); }

	virtual lept_type get_type() = 0;
};


