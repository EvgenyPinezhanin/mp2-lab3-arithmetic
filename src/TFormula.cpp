#include<TFormula.h>

void TFormula::stringParsing(string str)
{

}

TFormula::TFormula()
{
	outFormBool = false;
    outFormula = "";
    qRevPolNot = new Queue<Lexem*>;
}

TFormula::TFormula(const string& str)
{
	inpFormula = str;
	outFormBool = false;
    qRevPolNot = new Queue<Lexem*>;
}

void TFormula::init(const string& str)
{
	inpFormula = str;
	outFormBool = false;
}

bool TFormula::getOutFormula(string* s)
{
    *s = outFormula;
	return false;
}

void TFormula::conversToRevPolNot()
{
    string st;
    State state = q0;
    ICollection<Lexem*>* q = new Queue<Lexem*>;
    inpFormula += " ";
    int n = inpFormula.length();
    for (int i = 0; i < n;i++)
    {
        char c = inpFormula[i];
        if (state == q0)
        {
            if ((c >= '0') && (c <= '9'))
            {
                st = c;
                state = q1;
            }
            if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
            {
                st = c;
                q->push(new Lexem{st,OPERATION});
            }
            if (c == '(')
            {
                st = c;
                q->push(new Lexem{st, LP});
            }
            if (c == ')')
            {
                st = c;
                q->push(new Lexem{st, RP});
            }
            continue;
        }
        if (state == q1)
        {
            if ((c >= '0') && (c <= '9'))
            {
                st += c;
                state = q1;
            }
            if ((c == '+') || (c == '-') || (c == ' ')|| (c == '(') || (c == ')') || (c == '*') || (c == '/'))
            {
                int v = atoi(st.c_str());
                q->push(new Lexem{st,VALUE, v});
                state = q0;
            }
            if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
            {
                st = c;
                q->push(new Lexem{st,OPERATION});
                state = q0;
            }
            if (c == '(')
            {
                st = c;
                q->push(new Lexem{st, LP});
                state = q0;
            }
            if (c == ')')
            {
                st = c;
                q->push(new Lexem{st, RP});
                state = q0;
            }
        }
    }

    state = q0;
    int k = 0;
    ICollection<Lexem*>* qN = new Queue<Lexem*>;
    while(!q->isEmpty())
    {
        Lexem *l = q->pop();
        if (q->isEmpty()) state = q2;
        if (state == q0){
            if (l->te == LP) {
                k++;
                state = q0;
            }
            if ((l->te == VALUE)) {
                state = q1;
            }
            if ((l->te == RP)|| (l->te == OPERATION)) {
                throw logic_error("arithmetic_expression_is_invalid");
            }
            qN->push(l);
            continue;
        }
        if (state == q1){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithmetic_expression_is_invalid");
                state = q1;
            }
            if ((l->te == OPERATION)) {
                state = q0;
            }
            if ((l->te == LP)|| (l->te == VALUE)) {
                throw logic_error("arithmetic_expression_is_invalid");
            }
            qN->push(l);
            continue;
        }
        if (state == q2){
            if (l->te == RP) {
                k--;
                if (k < 0)  throw logic_error("arithmetic_expression_is_invalid");
            }
            if ((l->te == VALUE)) {
            }
            if ((l->te == LP)|| (l->te == OPERATION)) {
                throw logic_error("arithmetic_expression_is_invalid");
            }
            qN->push(l);
        }
    }
    if (k != 0)  throw logic_error("arithmetic_expression_is_invalid");

    ICollection<Lexem*>* s = new Stack<Lexem*>;
    while (!qN->isEmpty())
    {
        Lexem *l = qN->pop();
        if (l->te == LP) {
            s->push(l);
        }
        if ((l->te == VALUE)) {
            qRevPolNot->push(l);
            outFormula += l->s;
            outFormula += " "; 
        }
        if ((l->te == RP)) {
            while (!s->isEmpty()){
                l = s->pop();
                if (l->te != LP){
                    qRevPolNot->push(l);
                    outFormula += l->s;
                }
                else
                {
                    break;
                }
            }
        }
        if ((l->te == OPERATION)) {
            Lexem* l1;
            if ((l->s == "+")||(l->s == "-"))
            {
                while(!s->isEmpty())
                {
                    l1 = s->pop();
                    if (l1->te == OPERATION){
                        qRevPolNot->push(l1);
                        outFormula += l1->s;
                    }
                    else
                    {
                        s->push(l1);
                        break;
                    }
                }
            }
            else
            {
                while(!s->isEmpty())
                {

                    l1 = s->pop();
                    if (l1->te == OPERATION){
                        if ((l1->s == "*")||(l1->s == "/")){
                            qRevPolNot->push(l1);
                            outFormula += l1->s;
                        }
                        else
                        {
                            s->push(l1);
                            break;
                        }
                        
                    }
                    else
                    {
                        s->push(l1);
                        break;
                    }
                }
            }
            s->push(l);
        }
    }
    Lexem *l;
    while(!s->isEmpty())
    {
        l = s->pop();
        qRevPolNot->push(l);
        outFormula += l->s;
    }
    //while(!qRevPolNot->isEmpty())
    //{
    //    Lexem* l = qRevPolNot->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}
    //cout << outFormula;
    //while(!qN->isEmpty())
    //{
    //    Lexem* l = qN->pop();
    //    cout << l->s << " " << l->te << " " << l->val << endl;
    //}
}

int TFormula::calcArithmExp()
{
    ICollection<Lexem*>* s = new Stack<Lexem*>;
    Lexem *l;
    while(!qRevPolNot->isEmpty())
    {
        l = qRevPolNot->pop();
        if (l->te == VALUE)
        {
            s->push(l);
        }
        if (l->te == OPERATION)
        {
            Lexem* l1;
            Lexem* l2;
            int k;
            if (l->s == "+")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l1->val + l2->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "-")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val - l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "*")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val * l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
            if (l->s == "/")
            {
                l1 = s->pop();
                l2 = s->pop();
                k = l2->val / l1->val;
                s->push(new Lexem{to_string(k),VALUE, k});
            }
        }

    }

	return s->pop()->val;
}