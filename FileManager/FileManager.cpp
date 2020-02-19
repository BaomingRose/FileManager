#include "FileManager.h"
#include <string>
using std::pair;
using std::make_pair;

void FileManager::init() {
	_filename.clear();
	file_MD5.clear();
	MD5_file.clear();
	_md5.init();
}

void FileManager::scanFolder(const string& filePath) {
	init();
	dfsFolder(filePath, _filename);
	cout << filePath << "文件夹下所有文件：" << endl;
	for (const auto& e : _filename) {
		_md5.init();
		const char* str = e.c_str();
		MD5_file.insert(make_pair(_md5.getFileMD5(str), e));
		cout << e << endl;
	}
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		//查找每一个md5对应的文件结果
		//只存放有重复内容文件结果
		if (MD5_file.count(it->first) > 1) {
			//返回值：pair<begin, end>
			auto pairIt = MD5_file.equal_range(it->first);
			for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
				file_MD5.insert(make_pair(begin->second, begin->first));
			}
			//下一个不同MD5值的起始位置
			it = pairIt.second;
		} else {
			//erase：被删除元素的下一个位置
			it = MD5_file.erase(it);
		}
	}
}

void FileManager::scanFileNoR(const string& filePath) {
	init();
	transferDir(filePath, _filename);
	cout << filePath << "文件夹下所有文件：" << endl;
	for (const auto& e : _filename) {
		_md5.init();
		const char* str = e.c_str();
		MD5_file.insert(make_pair(_md5.getFileMD5(str), e));
		cout << e << endl;
	}
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		//查找每一个md5对应的文件结果
		//只存放有重复内容文件结果
		if (MD5_file.count(it->first) > 1) {
			//返回值：pair<begin, end>
			auto pairIt = MD5_file.equal_range(it->first);
			for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
				file_MD5.insert(make_pair(begin->second, begin->first));
			}
			//下一个不同MD5值的起始位置
			it = pairIt.second;
		} else {
			//erase：被删除元素的下一个位置
			it = MD5_file.erase(it);
		}
	}
}

//展示所有具有重复文件的全部文件
void FileManager::showRepetitiveFile() {
	cout << "当前文件夹下的重复内容文件有：" << endl;
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		int sum = 0;
		//返回值：pair<begin, end>
		auto pairIt = MD5_file.equal_range(it->first);
		cout << "\tmd5值为" << it->first << "的文件有：" << endl;
		for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
			cout << "\t\t" << begin->second << endl;
			++sum;
		}
		cout << "\t\t\t\t\t\t\t\t共" << sum << "个文件" << endl;
		//下一个不同MD5值的起始位置
		it = pairIt.second;
	}
}

void FileManager::deleteFileByName(const string& filepath) {
	if (file_MD5.count(filepath) == 0) {
		cout << filepath << "不存在" << endl;
		return;
	}
	_filename.erase(filepath);
	file_MD5.erase(filepath);
	for (auto it = MD5_file.begin(); it != MD5_file.end(); ++it) {
		if (it->second == filepath) {
			it = MD5_file.erase(it);
			break;
		}
	}
	if (remove(filepath.c_str()) == 0) {
		cout << "删除" << filepath << "成功" << endl;
	} else {
		cout << "删除失败！" << endl;
	}
}

//按照MD5删文件，选择一个要保留的文件
void FileManager::deleteFileRemainOne(const string& md5, const string& remainFileName) {
	if (MD5_file.count(md5) == 0) {
		cout << md5 << "不存在" << endl;
		return;
	}
	auto pairIt = MD5_file.equal_range(md5);
	for (auto it = pairIt.first; it != pairIt.second; ) {
		if (it->second == remainFileName) {
			break;
		}
		if (++it == pairIt.second) {
			cout << "该文件不符合该MD5值" << endl;
			return;
		}
	}
	auto curIt = pairIt.first;
	while (curIt != pairIt.second) {
		_filename.erase(curIt->second);
		file_MD5.erase(curIt->second);
		if (curIt->second != remainFileName) {
			//删除文件
			if (remove(curIt->second.c_str()) == 0) {
				cout << "删除" << curIt->second << "成功" << endl;
			}
		} 
		++curIt;
	}
	curIt = pairIt.first;
	MD5_file.erase(curIt, pairIt.second);
}

void FileManager::deleteFileByMD5(const string& md5) {
	if (MD5_file.count(md5) == 0) {
		cout << md5 << "不存在" << endl;
		return;
	}
	//保留一份,保留第一个
	auto pairIt = MD5_file.equal_range(md5);
	auto curIt = pairIt.first;
	_filename.erase(curIt->second);
	file_MD5.erase(curIt->second);
	++curIt;
	while (curIt != pairIt.second) {
		_filename.erase(curIt->second);
		file_MD5.erase(curIt->second);
		//删除文件
		if (remove(curIt->second.c_str()) == 0) {
			cout << "删除" << curIt->second << "成功" << endl;
		}
		++curIt;
	}
	curIt = pairIt.first;
	MD5_file.erase(curIt, pairIt.second);
}

void FileManager::deleteAllRepetitive() {
	unordered_set<string> md5s;
	for (const auto& e : MD5_file) {
		md5s.insert(e.first);
	}
	for (const auto& e : md5s) {
		deleteFileByMD5(e);
	}
}
