#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
#include <stack>
#include <queue>

string impt;

/* important -- for converting strings into integer here I did
str[i]-'0';
This will be converting string into integer. Also confirmed by using
sizeof function.
*/
int priority(char c){
    if (c=='*'|| c=='/')
    {
        return 2;
    }
    else if (c=='+'|| c=='-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int length(char exp[]){
    int i = 0;
    while (exp[i])
    {
        i++;
    }
    return i;
    
}

string infix2postfix(char exp[]){
    stack<char> s;
    int len=length(exp);
    string postfix;
    for (int i = 0; i < len; i++)
    {
        if (exp[i]=='(')
        {
            s.push(exp[i]);
        }
        else if (/*exp[i]!='('|| exp[i]!=')' || exp[i]!='*' || 
        exp[i]!='/' || exp[i]!='+' || exp[i]!='-'*/ (exp[i]>='0' &&
        exp[i]<='9'))
        {
            postfix+=exp[i];
        }
        else if (exp[i]==')')
        {
            while (/*!s.empty() && */ s.top()!='(')
            {
                postfix+=s.top();
                s.pop();
                // postfix+=c;
            }
            if (s.top()=='(')
            {
                s.pop();
            }
            // cout<<s.top()<<endl;
        }
        else
        {
            while (!s.empty() && priority(exp[i])<=priority(s.top()))
            {
                char c= s.top();
                s.pop();
                postfix+=c;
            }
            s.push(exp[i]);   
        }
        // cout<<s.top()<<endl;
        // cout<<postfix<<endl;
    }
    while (!s.empty())
    {
        if (s.top()!='(')
        {
            postfix+=s.top();
            s.pop();
        }
        else
        {
            s.pop();
        }
        
        
    }
    cout<<postfix<<endl;
    impt=postfix;
    // cout<<postfix<<endl;
    return postfix; 
}

int evaluateHelper(int op1, int op2, char c){
    switch (c)
    {
    case '*':
        return op2*op1;
    case '/':
        return op2/op1;
    case '+':
        return op2+op1;
    case '-':
        return op2-op1;
    
    default:
        return 0;
    }
}
void evaluateTotal(char exp[]){
    // cout<<impt<<endl;
    int val;
    stack<int> x;
    int i = 0;
    while (i<impt.size())
    {
        if (isdigit(impt[i]))
        {
            int l=impt[i]-'0';
            x.push(l);
        }
        else
        {
            int op1=x.top();
            x.pop();
            int op2=x.top();
            x.pop();
            val=evaluateHelper(op1, op2, impt[i]);
            x.push(val);
        }
        // cout<<val<<endl;
        i++;
    }
    cout<<val<<endl;
    
}
void evaluatePostfix(char exp[]){
    infix2postfix(exp);
    evaluateTotal(exp);
}

int main(){
    char exp[1000];
    cin>>exp;
    evaluatePostfix(exp);
    return 0;
}
