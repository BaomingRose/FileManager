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
	//��ȡÿһ�ֽ�����
	for (int i = 0; i < 4; ++i) {
		int curByte = (n >> (i * 8)) & 0xff;
		//����ת����16�����ַ�
		string curRet;
		//��16����λ	ģ16����λ
		curRet += strMap[curByte / 16];
		curRet += strMap[curByte % 16];
		ret += curRet;
	}
	return ret;
}


//һ��chunk��MD5����
void MD5::calMD5(const uint32_t* Chunk) {
	uint32_t a = _A, b = _B, c = _C, d = _D;
	uint32_t f, g;
	//���ֽ�Ϊһ������Ԫ
	//��ִ��64�β���
	for (int i = 0; i < 64; ++i) {
		//λ����   F G  H I 
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

		//���£��ӷ� + ѭ������
		uint32_t tmp = d;
		d = c;
		c = b;
		b = b + leftShift(a + f + Chunk[g] + _k[i], s[i]);
		a = tmp;
	}
	//���� _A _B _C _D
	_A += a;
	_B += b;
	_C += c;
	_D += d;
}

//������䣬�ڽ���MD5����
void MD5::calFinalMD5() {
	//���������Ϣ����һλ��1�� ʣ����0
	//������1���ֽ�������Ϣ
	//��ȡ��һ��������λ��
	char* p = _chunk + _lastByte;
	//�������1�ֽڵ�����
	*p++ = 0x80;

	int remainByte = 64 - _lastByte - 1;
	//���ʣ���ֽڲ���8�ֽڣ��洢ԭʼ���ȣ�,�ȴ���һ�����ݣ��ٹ���һ���µ����ݿ�(ǰ448λ��0����64λ��ԭʼ����)
	if (remainByte < 8) {
		memset(p, 0, remainByte);
		calMD5((const uint32_t*)_chunk);
		memset(_chunk, 0, 64);
	} else {
		memset(p, 0, remainByte);
	}
	//�����ݿ����64λ���ԭʼ������Ϣ
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
	//�������һ�����ݣ���Ҫ���
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
		//1.ȫ����������seekg��tellg��ȡ�ļ���С	�ռ任ʱ�䣨�ļ�����ʱ��
		fin.seekg(0, fin.end);
		uint32_t length = fin.tellg();
		fin.seekg(0, fin.beg);
		char* totalData = new char[length];
		fin.read(totalData, length);
#endif
		//2.ÿ��ֻ��ȡһ������	IO�����࣬ʱ�任�ռ�
		fin.read(_chunk, 64);
		//gcount�����ϴζ�ȡ���ֽ���
		//�������64���ֽڣ��������һ������
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

