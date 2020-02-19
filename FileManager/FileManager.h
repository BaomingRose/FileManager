#pragma once
#include "MD5.h"
#include "FileScan.h"
#include <unordered_map>
#include <unordered_set>
using std::unordered_set;
using std::unordered_map;
using std::unordered_multimap;

//给一个目录，检测当前目录下所有重复文件的结果，需要扫盘
class FileManager {
public:
	void init();
	//扫描当前目录(包括子目录)的文件
	void scanFolder(const string& filePath);
	//显示选项 不包括子目录
	void scanFileNoR(const string& filePath);
	void showRepetitiveFile();

	//通过文件名删除文件
	void deleteFileByName(const string& filepath);

	//通过MD5值删除文件
	void deleteFileByMD5(const string& md5);

	//删除所有保留一个文件
	void deleteFileRemainOne(const string& md5, const string& filename);
	
	//删除所有重复文件
	void deleteAllRepetitive();

	//模糊删除

private:
	unordered_set<string> _filename;
	//filename ---> MD5
	unordered_map<string, string> file_MD5;
	//MD5 ---> filename
	unordered_multimap<string, string> MD5_file;
	MD5 _md5;
};