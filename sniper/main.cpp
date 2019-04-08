#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <direct.h>
#include <sqlite3.h>

using namespace std;
void fileRead(const char *addr);
void insertDB(vector<string> elements);
string getFilePath();
//删除字符串中空格，制表符tab等无效字符
string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

int main()
{
	string filePath;
	//TODO：调试用，需删除
	char tmp;

	//获取文件路径
	filePath = getFilePath();
	
	//读取CSV文件并入库
	fileRead(filePath.c_str());

	//TODO：查询数据库并返回List

	//TODO：调试用，需删除
	cin >> tmp;

	return EXIT_SUCCESS;
}

string getFilePath() {
	char path[200] = { 0 };
	char buff[200] = { 0 };
	if ((_getcwd(buff, 200)) == NULL) {
		cout << "未读取到工程目录，使用绝对路径'C:\'" << endl;
		memcpy(buff, "C:\\", 3);
	}
	memcpy(path, buff, strlen(buff));
	memcpy(path + strlen(buff), "\\a.csv", 6);
	//cout << "当前路径是：" << path << "\n";

	return path;
}

void fileRead(const char *addr) {
	string line;
	char buffer[256];

	ifstream fin(addr); //打开文件流操作
	if (!fin.is_open()) {
		cout << "no file readed" << endl;
	}

	while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		string field;
		vector<string> elements;
		//cout << "原始字符串：" << line << endl; 整行输出

		//将整行字符串line读入到字符串流istringstream中
		istringstream sin(line); 
		//声明一个字符串向量
		vector<string> fields; 
		//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		while (getline(sin, field, ',')) 
		{
			//将刚刚读取的字符串添加到向量fields中
			fields.push_back(field);
		}
		//清除掉向量fields中第一个元素的无效字符，并赋值给变量name
		string name = Trim(fields[0]); 
		elements.push_back(name);
		//清除掉向量fields中第二个元素的无效字符，并赋值给变量phoneNo
		string phoneNo = Trim(fields[1]); 
		elements.push_back(phoneNo);
		//清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
		//string birthday = Trim(fields[2]); 
		//cout << "处理之后的字符串：" << name << "\t" << phoneNo << endl;

		//TODO：入库
		insertDB(elements);
	}
}
/**
* 入库
*/
void insertDB(vector<string> elements) {
	int i;
	string preSQL = "insert into tb_info values(";
	//迭代器遍历
	for (i = 0; i < (elements.size()-1); i++) {
		preSQL = preSQL.append("\"");
		preSQL = preSQL.append(elements[i]);
		preSQL = preSQL.append("\",");
	}
	preSQL = preSQL.append("\"");
	preSQL = preSQL.append(elements[i]);
	preSQL = preSQL.append("\");");

	cout << preSQL << endl;

	//TODO：执行preSQL将数据插入sqlite
}