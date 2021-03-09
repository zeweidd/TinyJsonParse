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
	string text = "{\"name\":\"mark\",\"age\":22,\"生日\":\"1999-03-17\", \"性别\":\"男\",\"幸运数字\":[23,45,12,1]}";
	Jstruct structure;
	Parse(text, structure);
	String name = *structure.find("name");
	number age = *structure.find("age");
	String birth = *structure.find("生日");
	String sex = *structure.find("性别");
	numberarray luck = *structure.find("幸运数字"), nums = { 23,45,12,1 };

	if (name == "mark" &&
		birth == "1999-03-17" &&
		age == 22 &&
		sex == "男" &&
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
	Jsonarray result = *json.find("客人");
	auto information1 = result[0];
	auto information2 = result[1];
	auto information3 = result[2];
	string name = *(information1.find("姓名")->second);
	number age = *(information1.find("年龄")->second);
	string sex =*( information1.find("性别")->second);
	string type = *(information2.find("型号")->second);
	number size =*( information2.find("尺码")->second);
	number price =*( information2.find("价格")->second);
	string addr = *(information3.find("地址")->second);
	string payway = *(information3.find("到付")->second);
	string pack = *(information3.find("包装")->second);

	if (
		name == "mark" &&
		age == 23 &&
		sex == "男" &&
		type == "NikeAirMax" &&
		size == 42 &&
		price == 1400 &&
		addr == "成都市" &&
		payway == "否" &&
		pack == "盒"
		)
		return true;
	else
		return false;
}

void test() 
{
	
	if (test_bool())
		cout << "bool解析成功！" << endl;
	else
		cout << "bool解析失败。" << endl;
	if (test_double())
		cout << "double解析成功！" << endl;
	else
		cout << "double解析失败。"<<endl;
	if (test_string())
		cout << "string解析成功！" << endl;
	else
		cout << "string解析失败。" << endl;
	if (test_object())
		cout << "object解析成功！" << endl;
	else
		cout << "object解析失败。" << endl;
	if (test_string_array())
		cout << "string_array解析成功！" << endl;
	else
		cout << "string_array解析失败。" << endl;
	if (test_double_array())
		cout << "double_array解析成功！" << endl;
	else
		cout << "double_array解析失败。" << endl;
	if (test_object_array())
		cout << "object_array解析成功！" << endl;
	else
		cout << "object_array解析失败。" << endl;
}