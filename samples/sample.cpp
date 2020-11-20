#include<iostream>
#include<string>
#include<TFormula.h>
#include<Collection.h>

using namespace std;

int main()
{
	TFormula f;
	string str = "(145+22*450/(41 + 49))*(45/9)+3947";

	//while (true)
	//{
		//getline(cin, str);
		f.init(str);
		f.conversToRevPolNot();
		string str1;
		f.getOutFormula(&str1);
		cout << "Обратная польская запись: " << str1 << endl;
		int ans = f.calcArithmExp();
		cout << "Ответ: " << ans << endl;
	//}
	return 0;
}