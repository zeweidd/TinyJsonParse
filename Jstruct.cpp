#include "Jstruct.h"

BaseInterface* Jstruct::find(const string& k)
{
	auto ite = k_v.find(k);
	if (ite == k_v.end())//如果ite到达尾后位置，说明此key值不存在，返回nullptr
		return nullptr;
	return ite->second;
}

void Jstruct::insert(pair<string, BaseInterface*>  elem)
{
	k_v.insert(elem);
}

Jstruct::~Jstruct()
{
	for (auto i : k_v)
	{
		Myfree(i);
	}
}

void Jstruct::Myfree(pair<string, BaseInterface*> target)
{
	//重构
	Json js;
	Jsonarray v_js;
		switch (target.second->get_type())
		{
		case LEPT_BOOL:
		case LEPT_NUMBER:
		case LEPT_NULL:
		case LEPT_STRING:
		case LEPT_ARRAY:
			delete target.second;
			break;
		case LEPT_OBJECT:
			js = *target.second;
			for (auto j : js)
			{
				Myfree(j);
			}
			delete target.second;
			break;
		case LEPT_OBJECT_ARRAY:
			v_js = *target.second;
			for (auto i : v_js)
			{
				for (auto j : i)
				{
					Myfree(j);
				}
			}
			delete target.second;
			break;
		default:
			break;
		}
}
