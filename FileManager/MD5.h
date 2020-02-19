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
	//���ļ���ȡ��512bit�����ݿ�
	char _chunk[64];
	//���Ҫ���ص�4������ֵ _A _B _C _D
	uint32_t _A, _B, _C, _D;
	//ѭ������λ��
	static size_t s[64];
	//�м�����ʽ�Ĺ̶�����	_k[i] = (size_t)(abs(sin(i + 1)) * pow(2, 32))
	uint32_t _k[64];
	//���һ�����ݵ��ֽ���
	uint32_t _lastByte;
	//���ֽ���
	uint32_t _totalByte;

	//numѭ������nλ
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

	//һ��chunk��MD5����
	void calMD5(const uint32_t* Chunk);

	//��һ����������ת��Ϊһ��16�����ַ���
	string transHex(uint32_t n);
	void calFinalMD5();
};