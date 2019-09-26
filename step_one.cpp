#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <io.h>
#include <stdlib.h>
#define ll long long
using namespace std;
map<string, int> cotword;// 统计单词出现的次数
vector<string> word;// 统计单词是否出现
vector<string> filenames; // 记录目录下文件名

struct cmp{// 优先队列重载 < ，首选出现的次数排序，次选字典序
	string words;
	int cot;
	friend operator <(cmp a, cmp b){
		if(a.cot == b.cot) return a.words.compare(b.words) > 0;
		return a.cot < b.cot;
	}
};

priority_queue<cmp> que;

/*
path: 指定目录
files: 保存结果
fileType: 指定的文件格式，如 .jpg
*/
void getAllFiles(string path, vector<string>& files){ // 遍历文件夹中文件名
    long hFile = 0;// 文件句柄
    struct _finddata_t fileinfo;// 文件信息
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));// 保存文件的全路径
           } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

void getAllFiles_childCatalogue(string path, vector<string>& files){ // 递归遍历子文件夹 获取文件名
    long hFile = 0;//文件句柄
    struct _finddata_t fileinfo;//文件信息
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getAllFiles_childCatalogue(p.assign(path).append("\\").append(fileinfo.name), files);//递归搜索
                }
            }
            else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

void solve(string s){ // 处理单词
	for(int i = 0; i < s.size(); i++){// 将单词大写统一变成小写
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 'a'- 'A';
		}
	}
	auto t = cotword.find(s);
	if(t == cotword.end()){// map中没有单词，将单词加入vector中，方便统计
		cotword[s] = 1;
		word.push_back(s);
	}
	else cotword[s]++;// map中有该单词，直接向上计数
}

bool isWord(string s){// 判断是否为单词
	if(!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return false;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))) return false;
	}
	return true;
}

void cotChar(string s){ // 统计单词出现次数
	string a;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))){// 断开string，取单个单词
			if(isWord(a)) solve(a);
			a.clear();// 用完之后，清空a，方便下一次统计
		}
		else a.push_back(s[i]);
	}
	if(a.size()) solve(a); // 末尾单词处理
}

void wordF(){ // 将单词加入优先队列中，自动排序
	for(int i = 0; i < word.size(); i++){
		que.push({word[i], cotword[word[i]]});
	}
}

void print_F(int n){ // 输出单词
	cout << "序号" << "\t" << "出现次数" << '\t' << "单词" << endl;
	int i = 0;
	while(!que.empty() && i < n){
		auto p = que.top(); que.pop();
		cout << ++i << "\t" << p.cot << '\t'<< p.words << endl;
//		cout << p.words << " ";
	}
}

void solve_f(char *args[], int op){ // 对-f命令行参数进行处理
	string s;
	ifstream inf;
	inf.open(args[op]);
	while(getline(inf, s)) cotChar(s); // 单行读入进行操作
	inf.close();
}

void solve_d(char *args[], int op){ // 对-d命令行参数进行处理
	getAllFiles(args[op], filenames);
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s); // 单行读入进行操作
		inf.close();
	}
}

void solve_d_s(char *args[], int op){ // 对-d -s 命令行参数进行处理
	getAllFiles_childCatalogue(args[op], filenames);
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s); // 单行读入进行操作
		inf.close();
	}
}

int outWords(int op, int ops[], int ops_size, char *args[]){ // 处理是否输出限定单词数
	for(int i = 0; i < ops_size; i++){
		if(ops[i]){
			if(op > ops[i] + 2 && !strcmp(args[++ops[i]], "-n"))
				return atoi(args[++ops[i]]);// 存在,则返回查找到的值
		}
	}
	return que.size(); // 不存在，返回默认所有的单词数
}

int main(int op, char *args[]){
	freopen("step_one_out_NoRepetition.txt", "w", stdout); // 结果打印到文件
	int ops[10]; // 操作数目，记录每一个操作进行到的位置
	int res = 0;// 操作数下标
	memset(ops, 0, sizeof ops);
	if(op >= 3 && !strcmp(args[++ops[res]], "-f")) solve_f(args, ++ops[res]);// -f处理
	else if(++res && op >=4 && !strcmp(args[++ops[res]], "-d") && !strcmp(args[++ops[res]], "-s"))//-d-s处理
		solve_d_s(args, ++ops[res]);
	else if(++res && op >=3 && !strcmp(args[++ops[res]], "-d"))//-d处理
		solve_d(args, ++ops[res]);
	else{
		cout << "输入格式有误， 命令行参数格式：xxx.exe -f <file name>" << endl;
		return -1;
	}
	wordF();
	print_F(outWords(op, ops, res + 1, args));
	return 0;
}
