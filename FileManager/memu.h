#pragma once
#include "FileManager.h"
using std::cin;

class menu {
public:
	char init() {
		cout << "******************************************************" << endl;
		cout << "\t\t管理重复内容的文件工具" << endl;
		cout << "\t\t  1. 扫描当前目录下文件" << endl;
		cout << "\t\t  2. 递归扫描当前目录下所有文件" << endl;
		cout << "******************************************************" << endl;
		cout << "请选择:" << endl;
		char c = getchar();
		char tmp = getchar();
		return c;
	}

	void press(const char& c) {
		string dir;
		if (c == '1') {
			cout << "请输入要扫描的目录路径 : " << endl;
			getline(cin, dir);
			fmer.scanFileNoR(dir);
		} else if(c == '2') {
			cout << "请输入要扫描的目录路径 : " << endl;
			getline(cin, dir);
			fmer.scanFolder(dir);
		} else {
			cout << "违规操作， 请重新选择" << endl;
			char ch = init();
			press(ch);
		}
	}

	char deletOptions() {
		cout << endl << "  删除选项" << endl;
		cout << "\t 1. 打印所有相同文件" << endl;
		cout << "\t 2. 通过文件名删除文件" << endl;
		cout << "\t 3. 通过MD5删除文件（随机保留一个文件）" << endl;
		cout << "\t 4. 通过MD5删除文件（选择要保留的文件）" << endl;
		cout << "\t 5. 删除所有重复文件" << endl;
		cout << "\t 6. 返回上一级" << endl;
		cout << "请选择：" << endl;
		char c = getchar();
		char tmp = getchar();
		return c;
	}

	void deletPress(const char& c) {
		string filename;
		string md5;
		char re;
		switch (c) {
		case '1' :
			fmer.showRepetitiveFile();
			re = deletOptions();
			deletPress(re);
			break;
		case '2' :
			cout << "请输入要删除的文件名:" << endl;
			getline(cin, filename);
			fmer.deleteFileByName(filename);
			break;
		case '3' :
			cout << "请输入要删除的MD5值:" << endl;
			getline(cin, md5);
			fmer.deleteFileByMD5(md5);
			break;
		case '4' :
			cout << "请输入要删除的MD5值:" << endl;
			getline(cin, md5);
			cout << "请输入要保留的文件名:" << endl;
			getline(cin, filename);
			/*debug
			for (const auto& e : fmer.MD5_file) {
				cout << e.first << "---" << e.second << endl;
			}
			*/
			fmer.deleteFileRemainOne(md5, filename);
			/*
			for (const auto& e : fmer.MD5_file) {
				cout << e.first << "---" << e.second << endl;
			}
			*/
			break;
		case '5' :
			fmer.deleteAllRepetitive();
			break;
		case '6' :
			break;
		default:
			cout << "输入违规, 请重新输入" << endl;
			re = deletOptions();
			deletPress(re);
			break;
		}
		return;
	}

private:
	FileManager fmer;
};