#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#define ll long long
using namespace std;
ll res[26]; // 统计字符个数
double ans[26];// 统计字符出现频率


void cotChar(string s){ // 统计字符出现次数
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 'a' && s[i] <= 'z') res[s[i] - 'a']++;
		if(s[i] >= 'A' && s[i] <= 'Z') res[s[i] - 'A']++;
	}
}

void wordF(){ // 计算字符出现的频率
	ll sum = 0;
	for(int i = 0; i < 26; i++) sum += res[i];
	for(int i = 0; i < 26; i++) ans[i] = double(res[i]) / sum;
}

void print_F(){
	bool flag[26]; // 当前字符是否出现过
	memset(flag, false, sizeof flag);
	printf("字符\t出现次数\t频率\n");
	for(int i = 0; i < 26; i++){
		ll tmaxChar[2] = {-1, -1};
		for(int j = 0; j < 26; j++){
			if(!flag[j] && tmaxChar[0] < res[j]){
				tmaxChar[0] = res[j];
				tmaxChar[1] = j;
			}
		}
		flag[tmaxChar[1]] = true;
		printf("%c\t%d\t%.2lf\n", tmaxChar[1] + 'a', res[tmaxChar[1]], ans[tmaxChar[1]]);
	}
}

int main(){
	string s;
	ifstream inf;
	inf.open("The Unadjusted Girl.txt"); // 读入文件——The Unadjusted Girl.txt 对文件进行操作
	freopen("第0步out.txt", "w", stdout); // 结果打印到文件——第0步out.txt 中
	while(getline(inf, s)) cotChar(s); // 单行读入进行操作
	wordF();
	print_F();
	inf.close();
	return 0;
}
