#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include<io.h>

using namespace std;

class Filecount
{
public:
	Filecount();
	void recount();
	~Filecount();
	void wordcount(string &filename);
	void charcount(string &filename);
	void linecount(string &filename);
	void codelinecount();
	void emptylinecount();
	void notelinecount();
	int search(string &srcPath, string &filename,string s[],int &i);
	void filesearch(string &srcPath, string &filename,string s[],int &i);
	void filecount(string filename, string order);

private:

	int words;    //������
	int lines;    //������
	int charnums; //�ַ���

	int emptylines;  //����
	int notelines;  //ע����
	int codelines;  //������
};