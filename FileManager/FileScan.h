#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::unordered_set;
using std::vector;

//��������Ŀ¼
void transferDir(const string& folderPath, unordered_set<string>& fileString);

//�����ļ��м������ļ����������ļ�������ϵͳ���ļ���Ŀ¼����״�ṹ��ʹ������������Ա��������ļ����õ�_A_SUBDIR����
//���ж�������Ŀ¼��if��֧�У�����ϵͳ�ڽ���һ����Ŀ¼ʱ��ƥ�䵽��ͷ�����ļ�(��)��"."(��ǰĿ¼)��".."(��һ��Ŀ¼)��
//��Ҫ���Ե����������������Ҫ�Ա��������ļ�������ʱ����else��֧�������Ӧ�Ĵ���ͺ�

void dfsFolder(const string& folderPath, unordered_set<string>& fileString);
