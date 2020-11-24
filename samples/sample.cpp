#include<iostream>
#include<string>
#include<TFormula.h>
#include<Collection.h>

using namespace std;

int main()
{
	TFormula f;
	//string str = "(145+22*450/(41 + 49))*(45/9)+3947";
	//string str = "(1+2*(4+25))+(45*34/(13+4))";
	string str;
	string strOut;

	while (true)
	{
		getline(cin, str);
		if (str == "exit") break;
		f.init(str);
		f.conversToRevPolNot();
		strOut = f.getOutFormula();
		cout << "Обратная польская запись: " << strOut << endl;
		int ans = f.calcArithmExp();
		cout << "Ответ: " << ans << endl;
	}
	return 0;
}