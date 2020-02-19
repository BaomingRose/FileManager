#pragma once
#include "FileManager.h"
using std::cin;

class menu {
public:
	char init() {
		cout << "******************************************************" << endl;
		cout << "\t\t�����ظ����ݵ��ļ�����" << endl;
		cout << "\t\t  1. ɨ�赱ǰĿ¼���ļ�" << endl;
		cout << "\t\t  2. �ݹ�ɨ�赱ǰĿ¼�������ļ�" << endl;
		cout << "******************************************************" << endl;
		cout << "��ѡ��:" << endl;
		char c = getchar();
		char tmp = getchar();
		return c;
	}

	void press(const char& c) {
		string dir;
		if (c == '1') {
			cout << "������Ҫɨ���Ŀ¼·�� : " << endl;
			getline(cin, dir);
			fmer.scanFileNoR(dir);
		} else if(c == '2') {
			cout << "������Ҫɨ���Ŀ¼·�� : " << endl;
			getline(cin, dir);
			fmer.scanFolder(dir);
		} else {
			cout << "Υ������� ������ѡ��" << endl;
			char ch = init();
			press(ch);
		}
	}

	char deletOptions() {
		cout << endl << "  ɾ��ѡ��" << endl;
		cout << "\t 1. ��ӡ������ͬ�ļ�" << endl;
		cout << "\t 2. ͨ���ļ���ɾ���ļ�" << endl;
		cout << "\t 3. ͨ��MD5ɾ���ļ����������һ���ļ���" << endl;
		cout << "\t 4. ͨ��MD5ɾ���ļ���ѡ��Ҫ�������ļ���" << endl;
		cout << "\t 5. ɾ�������ظ��ļ�" << endl;
		cout << "\t 6. ������һ��" << endl;
		cout << "��ѡ��" << endl;
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
			cout << "������Ҫɾ�����ļ���:" << endl;
			getline(cin, filename);
			fmer.deleteFileByName(filename);
			break;
		case '3' :
			cout << "������Ҫɾ����MD5ֵ:" << endl;
			getline(cin, md5);
			fmer.deleteFileByMD5(md5);
			break;
		case '4' :
			cout << "������Ҫɾ����MD5ֵ:" << endl;
			getline(cin, md5);
			cout << "������Ҫ�������ļ���:" << endl;
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
			cout << "����Υ��, ����������" << endl;
			re = deletOptions();
			deletPress(re);
			break;
		}
		return;
	}

private:
	FileManager fmer;
};