#if 0
#include "FileManager.h"
using namespace std;

int main() {
	FileManager fmer;
	fmer.scanFolder("D:\\VScpp\\�����ļ�������\\�����ļ�������");
	fmer.showRepetitiveFile();

	cout << "������Ҫɾ�����ļ�·��" << endl;
	string filepath;


	getline(cin, filepath);
	fmer.deleteFileByName(filepath);
	fmer.showRepetitiveFile();

	cout << "������Ҫɾ����MD5ֵ" << endl;
	string md5;
	getline(cin, md5);
	cout << "������Ҫ�������ļ�" << endl;
	string remainfile;
	getline(cin, remainfile);
	fmer.deleteFileRemainOne(md5, remainfile);

	fmer.showRepetitiveFile();

	return 0;
}
#endif