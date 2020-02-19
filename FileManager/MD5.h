#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using std::string;
using std::ifstream;
using std::cout;
using std::endl;

class MD5 {
public:
	MD5();
	void init();

	string getStringMD5(const string& str);
	string getFileMD5(const char* filePath);

private:
	//从文件获取的512bit的数据块
	char _chunk[64];
	//最后要返回的4个整型值 _A _B _C _D
	uint32_t _A, _B, _C, _D;
	//循环左移位数
	static size_t s[64];
	//中间运算式的固定变量	_k[i] = (size_t)(abs(sin(i + 1)) * pow(2, 32))
	uint32_t _k[64];
	//最后一块数据的字节数
	uint32_t _lastByte;
	//总字节数
	uint32_t _totalByte;

	//num循环左移n位
	uint32_t leftShift(uint32_t num, int n) {
		return (num << n) | (num >> (32 - n));
	}

	/*
	F(x, y, z) = (x & y) | ((~x) & z)
	G(x, y, z) = (x & z) | (y & (~z))
	H(x, y, z) = x ^ y ^ z
	I(x, y, z) = y ^ (x | (~z))
	*/
	uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
		return (x & y) | ((~x) & z);
	}

	uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
		return (x & z) | (y & (~z));
	}

	uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
		return x ^ y ^ z;
	}

	uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
		return y ^ (x | (~z));
	}

	//一个chunk的MD5运算
	void calMD5(const uint32_t* Chunk);

	//把一个整数数据转换为一个16进制字符串
	string transHex(uint32_t n);
	void calFinalMD5();
};