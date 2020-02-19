#include "MD5.h" 

size_t MD5::s[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

MD5::MD5() {
	init();
	for (int i = 0; i < 64; i++) {
		_k[i] = static_cast<size_t>(abs(sin(i + 1)) * pow(2, 32));
	}
}

void MD5::init() {
	_A = 0x67452301;
	_B = 0xefcdab89;
	_C = 0x98badcfe;
	_D = 0x10325476;
	_lastByte = 0;
	_totalByte = 0;
}

// 12 34 56 78 --->	78 56 34 12
string MD5::transHex(uint32_t n) {
	static string strMap = "0123456789abcdef";
	string ret;
	//获取每一字节数据
	for (int i = 0; i < 4; ++i) {
		int curByte = (n >> (i * 8)) & 0xff;
		//数据转换成16进制字符
		string curRet;
		//除16：高位	模16：地位
		curRet += strMap[curByte / 16];
		curRet += strMap[curByte % 16];
		ret += curRet;
	}
	return ret;
}


//一个chunk的MD5运算
void MD5::calMD5(const uint32_t* Chunk) {
	uint32_t a = _A, b = _B, c = _C, d = _D;
	uint32_t f, g;
	//四字节为一个处理单元
	//共执行64次操作
	for (int i = 0; i < 64; ++i) {
		//位运算   F G  H I 
		if (i >= 0 && i < 16) {
			f = F(b, c, d);
			g = i;
		} else if (i >= 16 && i < 32) {
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		} else if (i >= 32 && i < 48) {
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		} else {
			f = I(b, c, d);
			g = (7 * i) % 16;
		}

		//更新，加法 + 循环左移
		uint32_t tmp = d;
		d = c;
		c = b;
		b = b + leftShift(a + f + Chunk[g] + _k[i], s[i]);
		a = tmp;
	}
	//更新 _A _B _C _D
	_A += a;
	_B += b;
	_C += c;
	_D += d;
}

//进行填充，在进行MD5计算
void MD5::calFinalMD5() {
	//填充冗余信息：第一位填1， 剩余填0
	//至少填1个字节冗余信息
	//获取第一个待填充的位置
	char* p = _chunk + _lastByte;
	//首先填充1字节的冗余
	*p++ = 0x80;

	int remainByte = 64 - _lastByte - 1;
	//如果剩余字节不够8字节（存储原始长度）,先处理一块数据，再构建一个新的数据块(前448位填0，后64位填原始长度)
	if (remainByte < 8) {
		memset(p, 0, remainByte);
		calMD5((const uint32_t*)_chunk);
		memset(_chunk, 0, 64);
	} else {
		memset(p, 0, remainByte);
	}
	//给数据块最后64位填充原始长度信息
	unsigned long long int totalBits = _totalByte;
	totalBits *= 8;
	((unsigned long long*)_chunk)[7] = totalBits;
	calMD5((uint32_t*)_chunk);
}

string MD5::getStringMD5(const string& str) {
	if (str.empty()) {
		return transHex(_A).append(transHex(_B)).append(transHex(_C)).append(transHex(_D));
	}
	_totalByte = str.size();
	uint32_t chunkNum = _totalByte / 64;
	const char* strPtr = str.c_str();
	for (int i = 0; i < chunkNum; ++i) {
		memcpy(_chunk, strPtr + i * 64, 64);
		calMD5((uint32_t*)_chunk);
	}
	//计算最后一块数据：需要填充
	_lastByte = _totalByte % 64;
	memcpy(_chunk, strPtr + chunkNum * 64, _lastByte);
	calFinalMD5();
	return transHex(_A).append(transHex(_B)).append(transHex(_C)).append(transHex(_D));
}

string MD5::getFileMD5(const char* filePath) {
	ifstream fin(filePath);
	if (!fin.is_open()) {
		cout << filePath << " ";
		perror("file open error");
		return "";
	}
	while (!fin.eof()) {
#if 0
		//1.全部读进来；seekg，tellg获取文件大小	空间换时间（文件不大时）
		fin.seekg(0, fin.end);
		uint32_t length = fin.tellg();
		fin.seekg(0, fin.beg);
		char* totalData = new char[length];
		fin.read(totalData, length);
#endif
		//2.每次只读取一块数据	IO操作多，时间换空间
		fin.read(_chunk, 64);
		//gcount返回上次读取的字节数
		//如果不是64个字节，则是最后一块数据
		if (fin.gcount() != 64) {
			break;
		}
		_totalByte += 64;
		calMD5((uint32_t*)_chunk);
	}
	_lastByte = fin.gcount();
	_totalByte += _lastByte;
	calFinalMD5();
	return transHex(_A).append(transHex(_B)).append(transHex(_C)).append(transHex(_D));
}

