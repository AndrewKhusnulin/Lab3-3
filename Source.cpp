#include<io.h>       
#include<string>
#include<iostream>
#include<ctime>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<experimental\filesystem>
#include<sys/stat.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;
using namespace std::experimental::filesystem;
namespace fs = std::experimental::filesystem;
void Dir()
{

	char path[70];
	cout << "Enter path`s name: ";
	cin >> path;
	cout << endl;
	char mask[] = "*.*";
	strcat_s(path , 70, mask);
	 _finddata_t *fileinfo = new _finddata_t;
	unsigned int count = 0;
	intptr_t done;
	string pathfile, pathfile1;
	pathfile = static_cast<string>(path);
	pathfile.erase(pathfile.size()- strlen(mask), strlen(mask));
	char time[30];
	struct stat buf;
	
	if ((done = _findfirst(path, fileinfo)) == -1L)
	{
		cout << "Cant open directory" << endl;
	}
	else
	{
		do
		{
			if ((fileinfo->name[0] == 46))
				continue;
			count++;
			cout << "File Name: " << fileinfo->name << endl << "Size: " << fileinfo->size << " bytes \n" << "Time of creation: ";
			ctime_s(time, _countof(time), &fileinfo->time_write);
			cout << time ;
			cout << "Access: \n";
			pathfile1 = pathfile + fileinfo->name;
			stat(pathfile1.c_str(), &buf);
			(buf.st_mode & _S_IEXEC) ? (cout << "permission for the expansion / search, the owner" << endl) : cout << "permission to expand / search is forbidden" << endl;
			(buf.st_mode & _S_IWRITE) ? (cout << "permission to write, the owner" << endl) : cout << "permission to write is forbidden" << endl;
			(buf.st_mode & _S_IREAD) ? (cout << "permission to read, owner\n" << endl) : cout << "permission to read is forbidden\n" << endl;
		} while (_findnext(done, fileinfo) == 0);
		_findclose(done);
	}
	cout << "\nInformation: was found " << count;
	cout << " file(s) in folder..." << path << "\n\n";
	delete fileinfo;
}
void CopyFile(std::string& basepath, std::string& destpath)
{
	for (const fs::directory_entry& x : fs::directory_iterator(basepath))
	{
		try
		{
		fs::copy(x.path(), destpath / x.path().filename(), fs::copy_options::recursive);
		}
		catch (fs::filesystem_error& e)
		{
			std::cout << e.what() << std::endl << "There is a problem with the file: "
				<< destpath / x.path().filename() << std::endl;
		}
	}
}
void searchInFile(string str, string word)
{
	string str1;
	size_t j = 0;
	int k = 0;
	for (auto &p : recursive_directory_iterator(str))
	{
		string pp;
		pp = p.path().string();
		ifstream in(pp.c_str(), ios::in | ios::binary);
		if (in)
		{
			for (unsigned int i = 0; !in.eof(); ++i)
			{
				getline(in, str1);
				j = str1.find(word);
				if (j != string::npos)
				{
					cout << "Path`s name: ";
					cout << pp.c_str() << endl;
					cout << str1 << endl;
					break;	
				}
			}
		}
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	string path1, path2, word;
	int ch;
	while (1)
	{
		system("cls");
		cout << "Please, select preffer number...\n";
		cout << "1. Check directory\n";
		cout << "2. Copy files" << endl;
		cout << "3. Search words in files" << endl;
		cout << "0. Exit\n\n";
		cin >> ch;
		switch (ch)
		{
		case 1:
			Dir();
			_getch();
			break;
		case 2:
			cout << "Copying.\n";
			cout << "First directory: ";
			cin >> path1;
			cout << "Second directory: ";
			cin >> path2;
			CopyFile(path1, path2);
			_getch();
			break;
		case 3:
			cout << "Searching.\n";
			cout << "Directory: ";
			cin >> path1;
			cout << "Word: ";
			cin >> word;
			searchInFile(path1, word);
			_getch();
			break;
		case 0:
			return 0;
			break;
		}
	}
}