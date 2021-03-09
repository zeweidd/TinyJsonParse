#include "Parse.h"

using std::string;
using std::vector;

Parse::Parse(const string& text, Jstruct& deq):m_text(text),m_deq(deq)
{
	vector<string> elems = splict( text_init(m_text,'{','}'),',');
#if DEBUG
	for (auto i : elems)
	{
		cout << i << endl;
	}
#endif
	for (auto i : elems)
	{
		lept_type type = witch_type(i);
		switch (type)
		{
		case LEPT_BOOL:
			m_deq.insert(
				parse_bool(i)
			);
			break;
		case LEPT_STRING:
			m_deq.insert(
				parse_string(i)
			);
			break;
		case	LEPT_ARRAY:
			m_deq.insert(
				parse_array(i)
			);
			break;
		case	LEPT_OBJECT:
			m_deq.insert(
				parse_object(i)
			);
			break;
		case	LEPT_NULL:
			//......
			break;
		case LEPT_NUMBER:
			m_deq.insert(
				parse_double(i)
			);
			break;
		default:
			break;
		}
	}
}

/*���value�ĵ�һ���ַ��ж�������*/
lept_type Parse::witch_type(const string& part)
{
	size_t index = part.find(':');
	if (index == part.npos)
		return LEPT_NULL;
	switch (part[index + 1])
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '-': return LEPT_NUMBER;
	case '[': return LEPT_ARRAY;
	case '{': return LEPT_OBJECT;
	case '"': return LEPT_STRING;
	case 't':
	case 'f': return LEPT_BOOL;
	default:
		return LEPT_NULL;
	}
}

//  �������ͺ��������͵Ĵ���  
vector<string> Parse::splict(const string& str, const char fix)
{
	vector<string> temp;

	if (str.find(fix) == str.npos) {
		temp.push_back(str);//���û���ҵ���Ƭ��point������������������������Ȼ�󷵻�
		return temp;
	}
	/*index==��ʼ���ҵ�λ�ã�i==find����ÿ�β��ҷ��صĽ����j == ���ڴ���valueΪ����Ͷ���*/
	int index = 0, i = 0,j;
	while ((i = str.find(fix, index)) != str.npos)
	{
		if ((j = str.find('[', index)) < i && j != str.npos)					//
		{																							//
			int first = str.find_last_of(',', j)+1,										//
				last = str.find(']', index);												//
			temp.push_back(str.substr(first, last - first + 1));			//
			index = last + 2;																//
 			continue;																			//			����valueֵΪ����Ͷ���
		}																							//	
		else if ((j = str.find('{', index)) < i && j != str.npos)				//
		{																							//
			int first = str.find_last_of(',', j) + 1,									//
				last = str.find('}', index);												//
			temp.push_back(str.substr(first, last - first + 1));			//
			index = last + 2;																//
			continue;																			//
		}																							//
		/*����Ƭ��������vector,�´β��Ҵ��ϴ�point+1��ʼ��ֱ������������û��point*/
		temp.push_back(str.substr(index, i - index));
		index = i + 1;												  
	}
	if(str.size() >= index)
		temp.push_back(str.substr(index, str.size() - index));//��ʣ�ಿ���Ӵ�Ҳ����������
	return temp;
}

string Parse::text_init(const string& str, const char left, const char right)
{
	bool a = false, b = a;
	size_t i = 0, j = str.size();
	while (i < j)
	{
		if (str[i] != left)
			++i;
		else
			a = true;
		if (str[j] != right)
			--j;
		else
			b = true;
		if (a && b)
			break;
	}
	if (i >= j)
		return string();
	i += 1;
	return string(str.substr(i, j - i));
}

pair<string, BaseInterface*> Parse::parse_bool(const string& str)
{
	pair<string, BaseInterface*> temp;//���ڷ������ݵ���ʱpair����
	vector<string> line;  //��Ƭ�󴢴�key��value�ַ���������
	auto v = new Value<bool>();//����valueֵ��Value��
	/*��֤�Ƿ�Ϊ��Ч���ݲ���������Ƭ*/
	if (str.find(':') == str.npos)
		throw str + "����ЧJson��ʽ��";
	line = splict(str, ':');
	
	/*��ʼ��keyֵ����ֵ��temp.first*/
	temp.first = text_init(line[0], '"', '"');
	/*����valueֵ�ĳ�ʼ��*/
	if (line[1][0] == 'f' && line[1][3] == 's')
	{
		v->set_data(false);
	}
	else if (line[1][0] == 't' && line[1][3] == 'e')
	{
		v->set_data(true);
	}
	temp.second = v;

	return temp;
}

pair<string, BaseInterface*> Parse::parse_double(const string& str)
{
	pair<string, BaseInterface*> temp;
	vector<string> line;
	auto v = new Value<double>();

	if (str.find(':') == str.npos)
		throw str + "����ЧJson��ʽ��";
	line = splict(str, ':');
	
	temp.first = text_init(line[0], '"', '"');
	v->set_data(atof(line[1].c_str()));
	temp.second = v;

	return temp;
}

pair<string, BaseInterface*> Parse::parse_string(const string& str)
{
	pair<string, BaseInterface*> temp;
	vector<string> elem;
	auto value = new Value<String>();

	if (str.find(':') == str.npos)
		throw str + "��ЧJson��ʽ";
	elem = splict(str, ':');
	
	temp.first = text_init(elem[0], '"', '"');
	value->set_data( text_init(elem[1], '"', '"') );
	temp.second = value;

	return temp;
}

pair<string, BaseInterface*> Parse::parse_array(const string& str)
{
	if (str.find(':') == str.npos)
		throw str + "Json��ʽ����";
	pair<string, BaseInterface*> temp;
	vector<string> line, elem;
	strarray sdata;
	numberarray ndata;
	Jsonarray jdata;
	Json jdeq;

	line = splict(str, ':');

	temp.first = text_init(line[0], '"', '"');
	elem = splict(
		text_init(line[1], '[', ']'),
		',');
	if (elem[0][0] == '"')
	{
		auto v = new Value<strarray>();
		for (auto i : elem)
		{
			sdata.push_back(text_init(i, '"', '"'));
		}
		v->set_data(sdata);
		temp.second = v;
	}
	else if (elem[0][0] > '0' && elem[0][0] < '9')
	{
		auto v = new Value<numberarray>();
		for (auto i : elem)
		{
			ndata.push_back(
				atof(i.c_str())
			);
		}
		v->set_data(ndata);
		temp.second = v;
	}
	else if (elem[0][0] == '{')
	{
		auto v = new Value<Jsonarray>();

		for (auto i : elem)
		{
			vector<string> jelems;
			jelems = splict(text_init(i, '{', '}'), ',');
			for (auto j : jelems)
			{
				lept_type type = witch_type(j);
				switch (type)
				{
				case LEPT_BOOL:
					jdeq.insert(
						parse_bool(j)
					);
					break;
				case LEPT_STRING:
					jdeq.insert(
						parse_string(j)
					);
					break;
				case	LEPT_ARRAY:
					jdeq.insert(
						parse_array(j)
					);
					break;
				case	LEPT_OBJECT:
					jdeq.insert(
						parse_object(j)
					);
					break;
				case	LEPT_NULL:
					//......
					break;
				case LEPT_NUMBER:
					jdeq.insert(
						parse_double(j)
					);
					break;
				default:
					break;
				}
			}
			jdata.push_back(jdeq);
			jdeq.clear();
		}
		v->set_data(jdata);
		temp.second = v;
	}
	return temp;
}

pair<string, BaseInterface*> Parse::parse_object(const string& str)
{
	if (str.find(':') == str.npos)
		throw str + "Json��ʽ����";
	pair<string, BaseInterface*> temp;
	vector<string> elem;
	Json deq;
	auto value = new Value<Json>();

	elem = splict(str, ':');

	temp.first = text_init(elem[0], '"', '"');
	elem[1] = text_init(elem[1], '{', '}');
		for (auto i = elem.begin() + 1; i != elem.end(); ++i)
		{
			lept_type type = witch_type(*i);
			switch (type)
			{
			case LEPT_BOOL:
				deq.insert(
					parse_bool(*i)
				);
				break;
			case LEPT_STRING:
				deq.insert(
					parse_string(*i)
				);
				break;
			case	LEPT_ARRAY:
				deq.insert(
					parse_array(*i)
				);
				break;
			case	LEPT_OBJECT:
				deq.insert(
					parse_object(*i)
				);
				break;
			case	LEPT_NULL:
				//......
				break;
			case LEPT_NUMBER:
				deq.insert(
					parse_double(*i)
				);
				break;
			default:
				break;
			}
		}
		value->set_data(deq);
		temp.second = value;
		return temp;
}

