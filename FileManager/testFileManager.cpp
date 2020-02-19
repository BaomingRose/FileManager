#if 0
#include "FileManager.h"
using namespace std;

int main() {
	FileManager fmer;
	fmer.scanFolder("D:\\VScpp\\磁盘文件管理工具\\磁盘文件管理工具");
	fmer.showRepetitiveFile();

	cout << "请输入要删除的文件路径" << endl;
	string filepath;


	getline(cin, filepath);
	fmer.deleteFileByName(filepath);
	fmer.showRepetitiveFile();

	cout << "请输入要删除的MD5值" << endl;
	string md5;
	getline(cin, md5);
	cout << "请输入要保留的文件" << endl;
	string remainfile;
	getline(cin, remainfile);
	fmer.deleteFileRemainOne(md5, remainfile);

	fmer.showRepetitiveFile();

	return 0;
}
#endif