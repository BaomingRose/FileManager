#if 0
#include "FileScan.h"

int main() {
#if 0
	struct _finddata_t fileinfo;
	cout << "Directory listing of *.*" << endl;
	int k;
	long handle;
	//��һ������֧��������ʽ��*.*��ʾ������ǰĿ¼�������ļ�
	k = handle = _findfirst("D:\\*.*", &fileinfo);
	while (k != -1) {
		cout << fileinfo.name << endl;
		k = _findnext(handle, &fileinfo);
	}
	_findclose(handle);
#endif

	unordered_set<string> v;
	//dfsFolder("D:\\VScpp\\�����ļ�������\\�����ļ�������", v);
	transferDir("D:\\VScpp\\�����ļ�������\\�����ļ�������", v);
	for (const auto& e : v) {
		cout << e << endl;
	}
	
	return 0;
}
#endif