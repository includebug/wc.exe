#include "Filecountclass.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	string Path = "D:\\vs代码\\fileline\\fileline";
	string testorder = "-a";
	string testfilename = "*.txt";
	string s[20] = { "" };
	string orders[5] = { "-c","-w","-l" ,"-a","-s"};        //总命令和
	string trueorder[5] = {};
	string orderline = "";

	Filecount testfile ;
	cout << "请输入要在哪里搜索文件（如D:\\vs代码\\fileline\\fileline）" << endl;
	getline(cin,Path);
	cout << "请输入要执行的指令行（可连续输入,重复输入同一个无效）" << endl;
	cout <<"-c返回字符数  -w返回单词数 -l返回行数 -a返回复杂的行数数据 -s查找符合条件的文件返回"<<endl;
	getline(cin, orderline);
	cout << "请输入要搜索的文件名(如 *.txt /test.txt)" << endl;
	getline(cin, testfilename);

	int p = 0;            //记录指令的真正个数
	for (int t = 0; t < 5; t++)
	{
		if (orderline.find(orders[t]) != string::npos)
		{
			trueorder[p] = orders[t];
			p++;
		}	
	}

	int i = 0;
	testfile.filesearch(Path, testfilename, s, i); //在Path里搜索符合的文件名
	if (i == 0)
		cout << "无符合的文件，输入错误！" << endl;
	if (p == 0)
		cout << "无效指令，无法执行!" << endl;
	for (int j = 0; j < i; j++)
	{
		cout << "文件" << s[j] << "的数据:" << endl;
		for (int k = 0; trueorder[k] != ""&& k< p ;k++)
		{
			testfile.filecount(s[j], trueorder[k]);
		}
	}
		//Filecount对象只有一个却对应多个文件
	system("pause");
	return 0;
}