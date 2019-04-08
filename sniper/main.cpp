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
//ɾ���ַ����пո��Ʊ��tab����Ч�ַ�
string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"\t\r\n"��λ��
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

int main()
{
	string filePath;
	//TODO�������ã���ɾ��
	char tmp;

	//��ȡ�ļ�·��
	filePath = getFilePath();
	
	//��ȡCSV�ļ������
	fileRead(filePath.c_str());

	//TODO����ѯ���ݿⲢ����List

	//TODO�������ã���ɾ��
	cin >> tmp;

	return EXIT_SUCCESS;
}

string getFilePath() {
	char path[200] = { 0 };
	char buff[200] = { 0 };
	if ((_getcwd(buff, 200)) == NULL) {
		cout << "δ��ȡ������Ŀ¼��ʹ�þ���·��'C:\'" << endl;
		memcpy(buff, "C:\\", 3);
	}
	memcpy(path, buff, strlen(buff));
	memcpy(path + strlen(buff), "\\a.csv", 6);
	//cout << "��ǰ·���ǣ�" << path << "\n";

	return path;
}

void fileRead(const char *addr) {
	string line;
	char buffer[256];

	ifstream fin(addr); //���ļ�������
	if (!fin.is_open()) {
		cout << "no file readed" << endl;
	}

	while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
	{
		string field;
		vector<string> elements;
		//cout << "ԭʼ�ַ�����" << line << endl; �������

		//�������ַ���line���뵽�ַ�����istringstream��
		istringstream sin(line); 
		//����һ���ַ�������
		vector<string> fields; 
		//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
		while (getline(sin, field, ',')) 
		{
			//���ոն�ȡ���ַ�����ӵ�����fields��
			fields.push_back(field);
		}
		//���������fields�е�һ��Ԫ�ص���Ч�ַ�������ֵ������name
		string name = Trim(fields[0]); 
		elements.push_back(name);
		//���������fields�еڶ���Ԫ�ص���Ч�ַ�������ֵ������phoneNo
		string phoneNo = Trim(fields[1]); 
		elements.push_back(phoneNo);
		//���������fields�е�����Ԫ�ص���Ч�ַ�������ֵ������birthday
		//string birthday = Trim(fields[2]); 
		//cout << "����֮����ַ�����" << name << "\t" << phoneNo << endl;

		//TODO�����
		insertDB(elements);
	}
}
/**
* ���
*/
void insertDB(vector<string> elements) {
	int i;
	string preSQL = "insert into tb_info values(";
	//����������
	for (i = 0; i < (elements.size()-1); i++) {
		preSQL = preSQL.append("\"");
		preSQL = preSQL.append(elements[i]);
		preSQL = preSQL.append("\",");
	}
	preSQL = preSQL.append("\"");
	preSQL = preSQL.append(elements[i]);
	preSQL = preSQL.append("\");");

	cout << preSQL << endl;

	//TODO��ִ��preSQL�����ݲ���sqlite
}