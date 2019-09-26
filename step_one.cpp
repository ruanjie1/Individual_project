#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#define ll long long
using namespace std;
map<string, int> cotword;// ͳ�Ƶ��ʳ��ֵĴ���
vector<string> word;// ͳ�Ƶ����Ƿ����

struct cmp{
	string words;
	int cot;
	friend operator <(cmp a, cmp b){// ���ȶ������� < ����ѡ���ֵĴ������򣬴�ѡ�ֵ���
		if(a.cot == b.cot) return a.words.compare(b.words) > 0;
		return a.cot < b.cot;
	}
};

priority_queue<cmp> que;



void solve(string s){ // ������
	for(int i = 0; i < s.size(); i++){// �����ʴ�дͳһ���Сд
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 'a'- 'A';
		}
	}
	auto t = cotword.find(s);
	if(t == cotword.end()){// map��û�е��ʣ������ʼ���vector�У�����ͳ��
		cotword[s] = 1;
		word.push_back(s);
	}
	else cotword[s]++;// map���иõ��ʣ�ֱ�����ϼ���
}

bool isWord(string s){// �ж��Ƿ�Ϊ����
	if(!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return false;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))) return false;
	}
	return true;
}

void cotChar(string s){ // ͳ�Ƶ��ʳ��ִ���
	string a;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))){// �Ͽ�string��ȡ��������
			if(isWord(a)) solve(a);
			a.clear();// ����֮�����a��������һ��ͳ��
		}
		else a.push_back(s[i]);
	}
}

void wordF(){ // �����ʼ������ȶ����У��Զ�����
	for(int i = 0; i < word.size(); i++){
		que.push({word[i], cotword[word[i]]});
	}
}

void print_F(){ // �������
	cout << "���ظ�����ͳ�ƣ�" << endl;
	cout << "���ִ���" << '\t' << "����"<< endl;
	while(!que.empty()){
		auto p = que.top(); que.pop();
		cout << p.cot << '\t'<< p.words << endl;
//		cout << p.words << " ";
	}cout << endl;
}

int main(int op, char *args[]){
	string s;
	ifstream inf;
	if(op == 3 && !strcmp(args[1], "-f")){
		inf.open(args[2]);
		freopen("step_one_out_NoRepetition.txt", "w", stdout); // �����ӡ���ļ�������1��out.txt ��
		while(getline(inf, s)) cotChar(s); // ���ж�����в���
		wordF();
		print_F();
	}
	else cout << "�����ʽ���� �����в�����ʽ��xxx.exe -f <file name>" << endl;
	inf.close();
	return 0;
}
