#include "Filecountclass.h"
#include <algorithm>

using namespace std;

Filecount::Filecount()
{
	words = 0;
	charnums = 0;
	lines = 0;
	codelines = 0;
	emptylines = 0;
	notelines = 0;
}

void Filecount::recount()      //���㣬��Ϊǰ�������ļ����ݻ������ţ������һֱ�ۼ�
{
	words = 0;
	charnums = 0;
	lines = 0;
	codelines = 0;
	emptylines = 0;
	notelines = 0;
}

Filecount::~Filecount()
{
	;
}

void Filecount::wordcount(string &filename)
{
	string str;
	bool isWord = false;
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "�ļ��������д��޷���" << endl;
		return;
	}
	int count = 0;
	while (!file.eof())   //�ж�����Ϊfileʱ�����ظ������һ�У����һ��Ϊ�س�ʱ��������
	{
		getline(file, str);//���ļ��ж�ȡһ��
		isWord = false;              //���ã�����ԭ��û�лص�false���¼��㵥�������ˣ�
									//ÿ��ĩβ��isWordΪtrue��������һ�е�һ�����ʲ��ܼ���
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ' || str[i] == '\n' || str[i] == '(' || str[i] == ')' || str[i] == '\0') //����ĩβ�ı�־
			{
				isWord = false;
			}
			else
			{
				if (isWord == false)
				{
					isWord = true;
					words++;
				}
			}
		}
	}
	file.close();
}

void Filecount::charcount(string &filename)
{
	string str;
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "�ļ��������д��޷���" << endl;
		return;
	}
	int count = 0;
	while (!file.eof())   //�ж�����Ϊfileʱ�����ظ������һ�У����һ��Ϊ�س�ʱ��������
	{
		getline(file, str);//���ļ��ж�ȡһ��
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0')
				;     //�������Щ�ַ�ʲô������
			else
				charnums++;
		}
	}
	file.close();
}

void Filecount::linecount(string &filename)
{
	string str;
	int count = 0;
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "�ļ��������д��޷���" << endl;
		return;
	}
	while (!file.eof())
	{
		getline(file, str);//���ļ��ж�ȡһ��
		lines++;
		remove(str.begin(), str.end(), ' ');   //����㷨������algorithmͷ�ļ��У�ɾ��һ���еĿո�
		remove(str.begin(), str.end(), '\t');  //ɾ��һ���е��Ʊ������Ϊ�Ʊ���Ϳո��ǿյ�
		string notechar = "//";
		string::size_type idx;
		if (str.size() <= 1)
			emptylinecount();
		else if ((idx = str.find(notechar)) != string::npos)
			notelinecount();
		int count = 0;
		for (int j = 0; (j < str.size()) && (count <= 2); j++)
		{
			if ((str[j] >= 65 && str[j] <= 90) || (str[j] >= 97 && str[j] <= 122))
				count++;
		}
		if (count >= 2)
			codelinecount();
	}
	file.close();
}
	

void Filecount::codelinecount()
{
	codelines++;
}

void Filecount::emptylinecount()
{
	emptylines++;
}

void Filecount::notelinecount()
{
	notelines++;
}

int Filecount::search(string &srcPath, string &filename, string s[], int &i)     //��ָ���ļ����������ϵ��ļ������ܲ����ļ��е�
{
	long handle; //���ڲ��Ҿ��
	struct _finddata_t fileinfo; //�ļ���Ϣ�Ľṹ��

	string Name = srcPath + "\\" + filename;      //·������ģ�������ļ���

	handle = _findfirst(Name.c_str(), &fileinfo); //��һ�β���
	if (-1L == handle)
		return 1;
	else
	{
		s[i] = srcPath + "\\" + fileinfo.name;
		i++;
	}
		
	while (!_findnext(handle, &fileinfo))
	{
		s[i] = srcPath + "\\" + fileinfo.name;
		i++;
	}
	_findclose(handle);//�����˹رվ��
	return 0;
}

void Filecount::filesearch(string &srcPath, string &filename, string s[], int &i)  //�����ļ��������з����������ļ�
{
	if (srcPath == "")
		return;

	_finddata_t FileInfo;

	string startFindPath = srcPath + "\\*";       //�ļ�·���µ������ļ�

	long handle = _findfirst(startFindPath.c_str(), &FileInfo); //

	search(srcPath, filename, s, i);                    //������ļ������������ϵ��ļ�

	if (handle == -1L)
		return; 
	//���ݽ�������Ŀ¼
	do {
		if (FileInfo.attrib == _A_SUBDIR) //�ж��Ƿ�Ϊ���ļ���
		{
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				string newPath = srcPath + "\\" + FileInfo.name;
				filesearch(newPath,filename,s , i);
			}
		}

	} while (_findnext(handle, &FileInfo) == 0);

	_findclose(handle);
}


void Filecount::filecount(string filename, string order)
{
	if (order.compare("-c") == 0)
	{
		charcount(filename);
		cout << "�ļ����ַ���Ϊ" << charnums << endl;
	}
	else if (order.compare("-w") == 0)
	{
		wordcount(filename);
		cout << "�ļ��ĵ�����Ϊ" << words << endl;
	}
	else if (order.compare("-l") == 0)
	{
		linecount(filename);
		cout << "�ļ�������Ϊ" << lines << endl;
	}
		
	else if (order.compare("-a") == 0)
	{
		linecount(filename);
		cout << "�ļ��Ŀ���" << emptylines << endl;
		cout << "�ļ���ע����" << notelines << endl;
		cout << "�ļ��Ĵ�����" << codelines << endl;
	}
	else if (order.compare("-s") == 0)
	{
		//�ò�����main���������
	}
	else
		cout << "�����д����޷�ʶ��" << endl;
	recount();
}
