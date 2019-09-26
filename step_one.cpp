#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <io.h>
#define ll long long
using namespace std;
map<string, int> cotword;// ͳ�Ƶ��ʳ��ֵĴ���
vector<string> word;// ͳ�Ƶ����Ƿ����
vector<string> filenames; // ��¼Ŀ¼���ļ���

struct cmp{
	string words;
	int cot;
	friend operator <(cmp a, cmp b){// ���ȶ������� < ����ѡ���ֵĴ������򣬴�ѡ�ֵ���
		if(a.cot == b.cot) return a.words.compare(b.words) > 0;
		return a.cot < b.cot;
	}
};

priority_queue<cmp> que;

/*
path: ָ��Ŀ¼
files: ������
fileType: ָ�����ļ���ʽ���� .jpg
*/
//void getAllFiles(string path, vector<string>& files){
//    long hFile = 0;// �ļ����
//    struct _finddata_t fileinfo;// �ļ���Ϣ
//    string p;
//    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
//        do {
//            files.push_back(p.assign(path).append("\\").append(fileinfo.name));// �����ļ���ȫ·��
//           } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
//        _findclose(hFile);
//    }
//}

void getAllFiles(string path, vector<string>& files){ // �ݹ�������ļ��� ��ȡ�ļ���
    long hFile = 0;//�ļ����
    struct _finddata_t fileinfo;//�ļ���Ϣ
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);//�ݹ�����
                }
            }
            else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }
}

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
	if(a.size()) solve(a); // ĩβ���ʴ���
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

void solve_f(char *args[]){
	string s;
	ifstream inf;
	inf.open(args[2]);
	freopen("step_one_out_NoRepetition.txt", "w", stdout); // �����ӡ���ļ�������1��out.txt ��
	while(getline(inf, s)) cotChar(s); // ���ж�����в���
	wordF();
	print_F();
	inf.close();
}

void solve_d(char *args[]){
	getAllFiles(args[2], filenames);
	freopen("step_one_out_NoRepetition.txt", "w", stdout); // �����ӡ���ļ�������1��out.txt ��
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s); // ���ж�����в���
		inf.close();
	}
	wordF();
	print_F();
}

void solve_d_s(char *args[]){
	getAllFiles(args[3], filenames);
	freopen("step_one_out_NoRepetition.txt", "w", stdout); // �����ӡ���ļ�������1��out.txt ��
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s); // ���ж�����в���
		inf.close();
	}
	wordF();
	print_F();
}

int main(int op, char *args[]){
	if(op == 3 && !strcmp(args[1], "-f")) solve_f(args);
	else if(op == 3 && !strcmp(args[1], "-d")) solve_d(args);
	else if(op == 4 && !strcmp(args[1], "-d") && !strcmp(args[2], "-s")) solve_d_s(args);
	else cout << "�����ʽ���� �����в�����ʽ��xxx.exe -f <file name>" << endl;
	return 0;
}
