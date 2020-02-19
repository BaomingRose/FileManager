#if 0
#include "FileScan.h"

int main() {
#if 0
	struct _finddata_t fileinfo;
	cout << "Directory listing of *.*" << endl;
	int k;
	long handle;
	//第一个参数支持正则表达式，*.*表示搜索当前目录下所有文件
	k = handle = _findfirst("D:\\*.*", &fileinfo);
	while (k != -1) {
		cout << fileinfo.name << endl;
		k = _findnext(handle, &fileinfo);
	}
	_findclose(handle);
#endif

	unordered_set<string> v;
	//dfsFolder("D:\\VScpp\\磁盘文件管理工具\\磁盘文件管理工具", v);
	transferDir("D:\\VScpp\\磁盘文件管理工具\\磁盘文件管理工具", v);
	for (const auto& e : v) {
		cout << e << endl;
	}
	
	return 0;
}
#endif