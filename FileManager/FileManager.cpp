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
	cout << filePath << "�ļ����������ļ���" << endl;
	for (const auto& e : _filename) {
		_md5.init();
		const char* str = e.c_str();
		MD5_file.insert(make_pair(_md5.getFileMD5(str), e));
		cout << e << endl;
	}
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		//����ÿһ��md5��Ӧ���ļ����
		//ֻ������ظ������ļ����
		if (MD5_file.count(it->first) > 1) {
			//����ֵ��pair<begin, end>
			auto pairIt = MD5_file.equal_range(it->first);
			for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
				file_MD5.insert(make_pair(begin->second, begin->first));
			}
			//��һ����ͬMD5ֵ����ʼλ��
			it = pairIt.second;
		} else {
			//erase����ɾ��Ԫ�ص���һ��λ��
			it = MD5_file.erase(it);
		}
	}
}

void FileManager::scanFileNoR(const string& filePath) {
	init();
	transferDir(filePath, _filename);
	cout << filePath << "�ļ����������ļ���" << endl;
	for (const auto& e : _filename) {
		_md5.init();
		const char* str = e.c_str();
		MD5_file.insert(make_pair(_md5.getFileMD5(str), e));
		cout << e << endl;
	}
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		//����ÿһ��md5��Ӧ���ļ����
		//ֻ������ظ������ļ����
		if (MD5_file.count(it->first) > 1) {
			//����ֵ��pair<begin, end>
			auto pairIt = MD5_file.equal_range(it->first);
			for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
				file_MD5.insert(make_pair(begin->second, begin->first));
			}
			//��һ����ͬMD5ֵ����ʼλ��
			it = pairIt.second;
		} else {
			//erase����ɾ��Ԫ�ص���һ��λ��
			it = MD5_file.erase(it);
		}
	}
}

//չʾ���о����ظ��ļ���ȫ���ļ�
void FileManager::showRepetitiveFile() {
	cout << "��ǰ�ļ����µ��ظ������ļ��У�" << endl;
	auto it = MD5_file.begin();
	while (it != MD5_file.end()) {
		int sum = 0;
		//����ֵ��pair<begin, end>
		auto pairIt = MD5_file.equal_range(it->first);
		cout << "\tmd5ֵΪ" << it->first << "���ļ��У�" << endl;
		for (auto begin = pairIt.first; begin != pairIt.second; ++begin) {
			cout << "\t\t" << begin->second << endl;
			++sum;
		}
		cout << "\t\t\t\t\t\t\t\t��" << sum << "���ļ�" << endl;
		//��һ����ͬMD5ֵ����ʼλ��
		it = pairIt.second;
	}
}

void FileManager::deleteFileByName(const string& filepath) {
	if (file_MD5.count(filepath) == 0) {
		cout << filepath << "������" << endl;
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
		cout << "ɾ��" << filepath << "�ɹ�" << endl;
	} else {
		cout << "ɾ��ʧ�ܣ�" << endl;
	}
}

//����MD5ɾ�ļ���ѡ��һ��Ҫ�������ļ�
void FileManager::deleteFileRemainOne(const string& md5, const string& remainFileName) {
	if (MD5_file.count(md5) == 0) {
		cout << md5 << "������" << endl;
		return;
	}
	auto pairIt = MD5_file.equal_range(md5);
	for (auto it = pairIt.first; it != pairIt.second; ) {
		if (it->second == remainFileName) {
			break;
		}
		if (++it == pairIt.second) {
			cout << "���ļ������ϸ�MD5ֵ" << endl;
			return;
		}
	}
	auto curIt = pairIt.first;
	while (curIt != pairIt.second) {
		_filename.erase(curIt->second);
		file_MD5.erase(curIt->second);
		if (curIt->second != remainFileName) {
			//ɾ���ļ�
			if (remove(curIt->second.c_str()) == 0) {
				cout << "ɾ��" << curIt->second << "�ɹ�" << endl;
			}
		} 
		++curIt;
	}
	curIt = pairIt.first;
	MD5_file.erase(curIt, pairIt.second);
}

void FileManager::deleteFileByMD5(const string& md5) {
	if (MD5_file.count(md5) == 0) {
		cout << md5 << "������" << endl;
		return;
	}
	//����һ��,������һ��
	auto pairIt = MD5_file.equal_range(md5);
	auto curIt = pairIt.first;
	_filename.erase(curIt->second);
	file_MD5.erase(curIt->second);
	++curIt;
	while (curIt != pairIt.second) {
		_filename.erase(curIt->second);
		file_MD5.erase(curIt->second);
		//ɾ���ļ�
		if (remove(curIt->second.c_str()) == 0) {
			cout << "ɾ��" << curIt->second << "�ɹ�" << endl;
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
