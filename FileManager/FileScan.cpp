#include "FileScan.h"

//不遍历子目录
void transferDir(const string& folderPath, unordered_set<string>& fileString) {
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L) {
		cout << "can not match the folder path" << endl;
		exit(-1);
	}
	do {
		//判断是否有子目录  
		if (FileInfo.attrib & _A_SUBDIR) {
			continue;
		}
		else {
			fileString.insert(folderPath + "\\" + FileInfo.name);
			//cout << folderPath.c_str() << "\\" << FileInfo.name << endl;
		}
	} while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
}

//遍历文件夹及其子文件夹下所有文件。操作系统中文件夹目录是树状结构，使用深度搜索策略遍历所有文件。用到_A_SUBDIR属性
//在判断有无子目录的if分支中，由于系统在进入一个子目录时，匹配到的头两个文件(夹)是"."(当前目录)，".."(上一层目录)。
//需要忽略掉这两种情况。当需要对遍历到的文件做处理时，在else分支中添加相应的代码就好

void dfsFolder(const string& folderPath, unordered_set<string>& fileString) {
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L) {
		cout << "can not match the folder path" << endl;
		exit(-1);
	}
	do {
		//判断是否有子目录  
		if (FileInfo.attrib & _A_SUBDIR) {
			//这个语句很重要  
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0)) {
				string newPath = folderPath + "\\" + FileInfo.name;
				dfsFolder(newPath, fileString);
			}
		}
		else {
			fileString.insert(folderPath + "\\" + FileInfo.name);
			//cout << folderPath.c_str() << "\\" << FileInfo.name << endl;
		}
	} while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
}