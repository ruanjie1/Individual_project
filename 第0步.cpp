#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#define ll long long
using namespace std;
ll res[26]; // ͳ���ַ�����
double ans[26];// ͳ���ַ�����Ƶ��


void cotChar(string s){ // ͳ���ַ����ִ���
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 'a' && s[i] <= 'z') res[s[i] - 'a']++;
		if(s[i] >= 'A' && s[i] <= 'Z') res[s[i] - 'A']++;
	}
}

void wordF(){ // �����ַ����ֵ�Ƶ��
	ll sum = 0;
	for(int i = 0; i < 26; i++) sum += res[i];
	for(int i = 0; i < 26; i++) ans[i] = double(res[i]) / sum;
}

void print_F(){
	bool flag[26]; // ��ǰ�ַ��Ƿ���ֹ�
	memset(flag, false, sizeof flag);
	printf("�ַ�\t���ִ���\tƵ��\n");
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
	inf.open("The Unadjusted Girl.txt"); // �����ļ�����The Unadjusted Girl.txt ���ļ����в���
	freopen("��0��out.txt", "w", stdout); // �����ӡ���ļ�������0��out.txt ��
	while(getline(inf, s)) cotChar(s); // ���ж�����в���
	wordF();
	print_F();
	inf.close();
	return 0;
}
