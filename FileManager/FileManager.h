#pragma once
#include "MD5.h"
#include "FileScan.h"
#include <unordered_map>
#include <unordered_set>
using std::unordered_set;
using std::unordered_map;
using std::unordered_multimap;

//��һ��Ŀ¼����⵱ǰĿ¼�������ظ��ļ��Ľ������Ҫɨ��
class FileManager {
public:
	void init();
	//ɨ�赱ǰĿ¼(������Ŀ¼)���ļ�
	void scanFolder(const string& filePath);
	//��ʾѡ�� ��������Ŀ¼
	void scanFileNoR(const string& filePath);
	void showRepetitiveFile();

	//ͨ���ļ���ɾ���ļ�
	void deleteFileByName(const string& filepath);

	//ͨ��MD5ֵɾ���ļ�
	void deleteFileByMD5(const string& md5);

	//ɾ�����б���һ���ļ�
	void deleteFileRemainOne(const string& md5, const string& filename);
	
	//ɾ�������ظ��ļ�
	void deleteAllRepetitive();

	//ģ��ɾ��

private:
	unordered_set<string> _filename;
	//filename ---> MD5
	unordered_map<string, string> file_MD5;
	//MD5 ---> filename
	unordered_multimap<string, string> MD5_file;
	MD5 _md5;
};