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

//不遍历子目录
void transferDir(const string& folderPath, unordered_set<string>& fileString);

//遍历文件夹及其子文件夹下所有文件。操作系统中文件夹目录是树状结构，使用深度搜索策略遍历所有文件。用到_A_SUBDIR属性
//在判断有无子目录的if分支中，由于系统在进入一个子目录时，匹配到的头两个文件(夹)是"."(当前目录)，".."(上一层目录)。
//需要忽略掉这两种情况。当需要对遍历到的文件做处理时，在else分支中添加相应的代码就好

void dfsFolder(const string& folderPath, unordered_set<string>& fileString);
