#include "Filecountclass.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	string Path = "D:\\vs����\\fileline\\fileline";
	string testorder = "-a";
	string testfilename = "*.txt";
	string s[20] = { "" };
	string orders[5] = { "-c","-w","-l" ,"-a","-s"};        //�������
	string trueorder[5] = {};
	string orderline = "";

	Filecount testfile ;
	cout << "������Ҫ�����������ļ�����D:\\vs����\\fileline\\fileline��" << endl;
	getline(cin,Path);
	cout << "������Ҫִ�е�ָ���У�����������,�ظ�����ͬһ����Ч��" << endl;
	cout <<"-c�����ַ���  -w���ص����� -l�������� -a���ظ��ӵ��������� -s���ҷ����������ļ�����"<<endl;
	getline(cin, orderline);
	cout << "������Ҫ�������ļ���(�� *.txt /test.txt)" << endl;
	getline(cin, testfilename);

	int p = 0;            //��¼ָ�����������
	for (int t = 0; t < 5; t++)
	{
		if (orderline.find(orders[t]) != string::npos)
		{
			trueorder[p] = orders[t];
			p++;
		}	
	}

	int i = 0;
	testfile.filesearch(Path, testfilename, s, i); //��Path���������ϵ��ļ���
	if (i == 0)
		cout << "�޷��ϵ��ļ����������" << endl;
	if (p == 0)
		cout << "��Чָ��޷�ִ��!" << endl;
	for (int j = 0; j < i; j++)
	{
		cout << "�ļ�" << s[j] << "������:" << endl;
		for (int k = 0; trueorder[k] != ""&& k< p ;k++)
		{
			testfile.filecount(s[j], trueorder[k]);
		}
	}
		//Filecount����ֻ��һ��ȴ��Ӧ����ļ�
	system("pause");
	return 0;
}