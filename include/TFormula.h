#pragma once
#include<iostream>
#include<cstring>
#include<Collection.h>

using namespace std;

enum TypeElem {VALUE, OPERATION, LP, RP};
enum State {q0, q1, q2};

struct Lexem {
	string s;
	TypeElem te;
    int val = -1;
};

class TFormula {
	string inpFormula;
	string outFormula;
	bool outFormBool;
	 ICollection<Lexem*>* qRevPolNot;
    void stringParsing(string str);
public:
	TFormula();
	TFormula(const string& str);

	void init(const string& str);
	bool getOutFormula(string* s);

	void conversToRevPolNot();
	int calcArithmExp();
};