#include "Jstruct.h"
#include "Parse.h"
#include<fstream>
#include<sstream>

bool test_bool();
bool test_double();
bool test_string();
bool test_object();
bool test_string_array();
bool test_double_array();
bool test_object_array();
void test();
int main()
{
	test();
	return 0;
}

bool test_bool()
{
	Jstruct structure;
	string Json_text = " {\"true\":true,\"false\":false}";
	Parse(Json_text, structure);
	boolen result = *structure.find("true");
	boolen result1 = *structure.find("false");
	if (result && !result1)
		return true;
	else
		return false;
}
bool test_double() 
{
	Jstruct structure;
	string Json_text = " {\"num1\":12.098,\"num2\":0.11}";
	Parse (Json_text, structure);
	number result = *structure.find("num1");
	number result1 = *structure.find("num2");
	if (result == 12.098 && result1 == 0.11)
		return true;
	else
		return false;
}
bool test_string()
{
	Jstruct structure;
	string Json_text = " {\"name\":\"mark\",\"data\":\"1998-03-17\"}";
	Parse(Json_text, structure);
	String result = *structure.find("name");
	String result1 = *structure.find("data");
	if (result == "mark" && result1 == "1998-03-17")
		return true;
	else
		return false;
}
bool test_object()
{
	string text = "{\"name\":\"mark\",\"age\":22,\"����\":\"1999-03-17\", \"�Ա�\":\"��\",\"��������\":[23,45,12,1]}";
	Jstruct structure;
	Parse(text, structure);
	String name = *structure.find("name");
	number age = *structure.find("age");
	String birth = *structure.find("����");
	String sex = *structure.find("�Ա�");
	numberarray luck = *structure.find("��������"), nums = { 23,45,12,1 };

	if (name == "mark" &&
		birth == "1999-03-17" &&
		age == 22 &&
		sex == "��" &&
		luck == nums
		)
		return true;
	else
		return false;
}
bool test_string_array()
{
	string text = " {\"life\":[\"mark\",\"data\",\"1999-03-17\"]}";
	Jstruct structure;
	Parse(text, structure);
	strarray result = *structure.find("life"), des = {"mark","data","1999-03-17"};
	if (result == des)
		return true;
	else
		return false;
}
bool test_double_array()
{
	string text = " {\"life\":[23,1,55,873,0.1133,11.333]}";
	Jstruct structure;
	Parse(text, structure);
	numberarray result = *structure.find("life"), des = { 23, 1, 55, 873, 0.1133, 11.333 };
	if (result == des)
		return true;
	else
		return false;
}
bool test_object_array()
{
	ifstream text("./JsonData.txt");
	string data,temp;
	if (text.is_open())
		while (getline(text, temp))
			data += temp;
	Jstruct json;
	Parse(data, json);
	Jsonarray result = *json.find("����");
	auto information1 = result[0];
	auto information2 = result[1];
	auto information3 = result[2];
	string name = *(information1.find("����")->second);
	number age = *(information1.find("����")->second);
	string sex =*( information1.find("�Ա�")->second);
	string type = *(information2.find("�ͺ�")->second);
	number size =*( information2.find("����")->second);
	number price =*( information2.find("�۸�")->second);
	string addr = *(information3.find("��ַ")->second);
	string payway = *(information3.find("����")->second);
	string pack = *(information3.find("��װ")->second);

	if (
		name == "mark" &&
		age == 23 &&
		sex == "��" &&
		type == "NikeAirMax" &&
		size == 42 &&
		price == 1400 &&
		addr == "�ɶ���" &&
		payway == "��" &&
		pack == "��"
		)
		return true;
	else
		return false;
}

void test() 
{
	
	if (test_bool())
		cout << "bool�����ɹ���" << endl;
	else
		cout << "bool����ʧ�ܡ�" << endl;
	if (test_double())
		cout << "double�����ɹ���" << endl;
	else
		cout << "double����ʧ�ܡ�"<<endl;
	if (test_string())
		cout << "string�����ɹ���" << endl;
	else
		cout << "string����ʧ�ܡ�" << endl;
	if (test_object())
		cout << "object�����ɹ���" << endl;
	else
		cout << "object����ʧ�ܡ�" << endl;
	if (test_string_array())
		cout << "string_array�����ɹ���" << endl;
	else
		cout << "string_array����ʧ�ܡ�" << endl;
	if (test_double_array())
		cout << "double_array�����ɹ���" << endl;
	else
		cout << "double_array����ʧ�ܡ�" << endl;
	if (test_object_array())
		cout << "object_array�����ɹ���" << endl;
	else
		cout << "object_array����ʧ�ܡ�" << endl;
}