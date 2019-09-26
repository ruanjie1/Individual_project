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
map<string, int> cotword;// ͳ�Ƶ��ʳ��ֵĴ���
vector<string> filenames; // ��¼Ŀ¼���ļ���
map<string, int> stopword; // ͣ�ʱ�

struct cmp{// ���ȶ������� < ����ѡ���ֵĴ������򣬴�ѡ�ֵ���
	string words;
	int cot;
	friend operator <(cmp a, cmp b){
		if(a.cot == b.cot) return a.words.compare(b.words) > 0;
		return a.cot < b.cot;
	}
};
ll ans = 0;
priority_queue<cmp> que;

/*
path: ָ��Ŀ¼
files: ������
fileType: ָ�����ļ���ʽ���� .jpg
*/
void getAllFiles(string path, vector<string>& files){ // �����ļ������ļ���
    long hFile = 0;// �ļ����
    struct _finddata_t fileinfo;// �ļ���Ϣ
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));// �����ļ���ȫ·��
           } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }
}

void getAllFiles_childCatalogue(string path, vector<string>& files){ // �ݹ�������ļ��� ��ȡ�ļ���
    long hFile = 0;//�ļ����
    struct _finddata_t fileinfo;//�ļ���Ϣ
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getAllFiles_childCatalogue(p.assign(path).append("\\").append(fileinfo.name), files);//�ݹ�����
                }
            }
            else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }
}

void add_words(string s, int f){ // ������
	for(int i = 0; i < s.size(); i++){// �����ʴ�дͳһ���Сд
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 'a'- 'A';
		}
	}
	if(f) cotword[s]++;
	else stopword[s]++;
	ans++;
}

bool isWord(string s){// �ж��Ƿ�Ϊ����
	if(!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return false;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))) return false;
	}
	return true;
}

void cotChar(string s, int f){ // ͳ�Ƶ��ʳ��ִ���
	string a;
	for(int i = 0; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))){// �Ͽ�string��ȡ��������
			if(isWord(a)) add_words(a, f);
			a.clear();// ����֮�����a��������һ��ͳ��
		}
		else a.push_back(s[i]);
	}
	if(a.size()) add_words(a, f); // ĩβ���ʴ���
}

void wordF(){ // �����ʼ������ȶ����У��Զ�����
	for(auto i = cotword.begin(); i != cotword.end(); i++){
		if(stopword.find(i->first) == stopword.end())
			que.push({i->first, i->second});
	}
}

void print_F(int n){ // �������
	cout << "���" << "\t" << "���ִ���" << '\t' << "����" << endl;
	int i = 0;
	while(!que.empty() && i < n){
		auto p = que.top(); que.pop();
		cout << ++i << "\t" << p.cot << '\t'<< p.words << endl;
	}
}

void solve_x(int op, char *args[]){// ��-x�����в������д���
	string s;
	ifstream inf;
	inf.open(args[op]);
	while(getline(inf, s)) cotChar(s, 0); // ���ж�����в���
	inf.close();
}

void solve_f(int op, char *args[]){ // ��-f�����в������д���
	string s;
	ifstream inf;
	inf.open(args[op]);
	while(getline(inf, s)) cotChar(s, 1); // ���ж�����в���
	inf.close();
}

void solve_d(int op, char *args[]){ // ��-d�����в������д���
	getAllFiles(args[op], filenames);
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s, 1); // ���ж�����в���
		inf.close();
	}
}

void solve_d_s(int op, char *args[]){ // ��-d -s �����в������д���
	getAllFiles_childCatalogue(args[op], filenames);
	for(int i = 0; i < filenames.size(); i++){
		string s;
		ifstream inf;
		inf.open(filenames[i]);
		while(getline(inf, s)) cotChar(s, 1); // ���ж�����в���
		inf.close();
	}
}

int outWords(int op, char *args[]){ // �����Ƿ�����޶�������
	if(!strcmp(args[op], "-n")) return atoi(args[op + 1]);
	return que.size(); // �����ڣ�����Ĭ�����еĵ�����
}

bool judge_x_command(int ps, char *args[]){ // �ж��Ƿ��� -x ָ��
	return !strcmp(args[ps], "-x");
}

bool judge_f_command(int ps, char *args[]){ // �ж��Ƿ��� -f ָ��
	return !strcmp(args[ps], "-f");
}

bool judge_d_command(int ps, char *args[]){ // �ж��Ƿ��� -d ָ��
	return !strcmp(args[ps], "-d");
}

bool judge_d_s_command(int ps, char *args[]){ // �ж��Ƿ��� -d -s ָ��
	return !strcmp(args[ps], "-d") * !strcmp(args[ps + 1], "-s");
}

int main(int op, char *args[]){
	freopen("step_one_out_NoRepetition.txt", "w", stdout); // �����ӡ���ļ�
	int ps = 1; // argsλ��
	if(ps + 1 < op && judge_x_command(ps, args)) solve_x(ps + 1, args), ps += 2; // ����-x����
	
	if(ps + 1 < op && judge_f_command(ps, args)) solve_f(ps + 1, args), ps += 2;// -f����
	else if(ps + 2 < op && judge_d_s_command(ps, args)) solve_d_s(ps + 2, args), ps += 3;// -d-s����
	else if(ps + 1 < op && judge_d_command(ps, args)) solve_d(ps + 1, args), ps += 2; //-d����
	else{
		cout << "�����ʽ���� �����в�����ʽ��xxx.exe -f <file name>" << endl;
		return -1;
	}
	wordF();
//	cout << ans << endl;
	int outW = que.size();
	if(ps + 1 < op) outW = outWords(ps, args);
	print_F(outW), ps += 2;
	return 0;
}
