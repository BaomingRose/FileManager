#include "FileScan.h"

//��������Ŀ¼
void transferDir(const string& folderPath, unordered_set<string>& fileString) {
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L) {
		cout << "can not match the folder path" << endl;
		exit(-1);
	}
	do {
		//�ж��Ƿ�����Ŀ¼  
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

//�����ļ��м������ļ����������ļ�������ϵͳ���ļ���Ŀ¼����״�ṹ��ʹ������������Ա��������ļ����õ�_A_SUBDIR����
//���ж�������Ŀ¼��if��֧�У�����ϵͳ�ڽ���һ����Ŀ¼ʱ��ƥ�䵽��ͷ�����ļ�(��)��"."(��ǰĿ¼)��".."(��һ��Ŀ¼)��
//��Ҫ���Ե����������������Ҫ�Ա��������ļ�������ʱ����else��֧�������Ӧ�Ĵ���ͺ�

void dfsFolder(const string& folderPath, unordered_set<string>& fileString) {
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L) {
		cout << "can not match the folder path" << endl;
		exit(-1);
	}
	do {
		//�ж��Ƿ�����Ŀ¼  
		if (FileInfo.attrib & _A_SUBDIR) {
			//���������Ҫ  
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