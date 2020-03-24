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

void Filecount::recount()      //置零，因为前面计算的文件数据还保留着，否则会一直累加
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
		cout << "文件名可能有错，无法打开" << endl;
		return;
	}
	int count = 0;
	while (!file.eof())   //判断条件为file时，会重复读最后一行，最后一行为回车时正常行数
	{
		getline(file, str);//从文件中读取一行
		isWord = false;              //重置，错误原因，没有回到false导致计算单词数少了，
									//每行末尾置isWord为true，导致下一行第一个单词不能计算
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ' || str[i] == '\n' || str[i] == '(' || str[i] == ')' || str[i] == '\0') //单词末尾的标志
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
		cout << "文件名可能有错，无法打开" << endl;
		return;
	}
	int count = 0;
	while (!file.eof())   //判断条件为file时，会重复读最后一行，最后一行为回车时正常行数
	{
		getline(file, str);//从文件中读取一行
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0')
				;     //如果是这些字符什么都不做
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
		cout << "文件名可能有错，无法打开" << endl;
		return;
	}
	while (!file.eof())
	{
		getline(file, str);//从文件中读取一行
		lines++;
		remove(str.begin(), str.end(), ' ');   //这个算法函数在algorithm头文件中，删除一行中的空格
		remove(str.begin(), str.end(), '\t');  //删除一行中的制表符，因为制表符和空格都是空的
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

int Filecount::search(string &srcPath, string &filename, string s[], int &i)     //在指定文件夹搜索符合的文件，不能查子文件夹的
{
	long handle; //用于查找句柄
	struct _finddata_t fileinfo; //文件信息的结构体

	string Name = srcPath + "\\" + filename;      //路径加上模糊搜索文件名

	handle = _findfirst(Name.c_str(), &fileinfo); //第一次查找
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
	_findclose(handle);//别忘了关闭句柄
	return 0;
}

void Filecount::filesearch(string &srcPath, string &filename, string s[], int &i)  //搜索文件夹内所有符合条件的文件
{
	if (srcPath == "")
		return;

	_finddata_t FileInfo;

	string startFindPath = srcPath + "\\*";       //文件路径下的所有文件

	long handle = _findfirst(startFindPath.c_str(), &FileInfo); //

	search(srcPath, filename, s, i);                    //在这个文件夹下搜索符合的文件

	if (handle == -1L)
		return; 
	//逐层递进搜索子目录
	do {
		if (FileInfo.attrib == _A_SUBDIR) //判断是否为子文件夹
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
		cout << "文件的字符数为" << charnums << endl;
	}
	else if (order.compare("-w") == 0)
	{
		wordcount(filename);
		cout << "文件的单词数为" << words << endl;
	}
	else if (order.compare("-l") == 0)
	{
		linecount(filename);
		cout << "文件的行数为" << lines << endl;
	}
		
	else if (order.compare("-a") == 0)
	{
		linecount(filename);
		cout << "文件的空行" << emptylines << endl;
		cout << "文件的注释行" << notelines << endl;
		cout << "文件的代码行" << codelines << endl;
	}
	else if (order.compare("-s") == 0)
	{
		//该操作在main函数里完成
	}
	else
		cout << "命令有错误，无法识别" << endl;
	recount();
}
