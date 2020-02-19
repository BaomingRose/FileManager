#if 0
#include "MD5.h"
#include <iostream>
using std::cout;
using std::endl;

#if 0
void testTransHex() {
	MD5 md5;
	uint32_t n = 0x23456789;
	cout << md5.transHex(n) << endl;
}
#endif

void testStringMD5() {
	MD5 md;
	string str = "123456789abcdefgh";
	cout << md.getStringMD5(str) << endl;
}

void testFileMD5() {
	MD5 md;
	const char* filePath1 = "a.txt";
	const char* filePath2 = "a1.txt";
	cout << md.getFileMD5(filePath1) << endl;
	md.init();
	cout << md.getFileMD5(filePath2) << endl;
}

int main() {
	//testTransHex();
	//testStringMD5();
	testFileMD5();

	return 0;
}
#endif