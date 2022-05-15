#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include<io.h>
using namespace std;

struct Stack {
	char info;
	Stack* next;
};

struct Nums {
	char letter;
	bool already = false;
};
Stack* InS(Stack*, char);
Stack* OutS(Stack*, char&);
int Prior(char);
void Result(char*);
void Expression(char*);

int main()
{
	Stack* begin = NULL, * Operation = NULL;
	char a, In[15], Out[15];
	int l = 0,kolvo=0;
	Expression(In);
	
	for (int k = 0; In[k] != '\0'; ++k) {
		
		if (In[k] >= 'a' && In[k] <= 'z')
			Out[l++] = In[k]; 
		if (In[k] == '(')
			Operation = InS(Operation, In[k]);
		if (In[k] == ')') {
			while ((Operation->info) != '(') {
				Operation = OutS(Operation, a);
				if (!Operation) a = '\0';
				Out[l++] = a;
			}
			Operation = OutS(Operation, a);
		}
		if (In[k] == '+' || In[k] == '-' || In[k] == '*' || In[k] == '/') {
			while (Operation != NULL && Prior(Operation->info) >= Prior(In[k])) {
				Operation = OutS(Operation, a);
				Out[l++] = a;
			}
			Operation = InS(Operation, In[k]);
		}
	}
	while (Operation != NULL) {
		Operation = OutS(Operation, a);
		Out[l++] = a;
	}
	Out[l] = '\0';
	cout << "\nReverse Polish Notation = " << Out << endl;
	 Result(Out);
	 system("pause");
	return 0;
}



Stack* InS(Stack* p, char a)
{
	Stack* t = new Stack;
	t->info = a;
	t->next = p;
	return t;
}

Stack* OutS(Stack* p, char& s)
{
	Stack* t = p;
	s = p->info;
	p = p->next;
	delete t;
	return p;
}
int Prior(char a) {
	switch (a) {
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	}
	return 0;
}

void Result(char* str) {
	int len = strlen(str);
	int  i,k=0;
	Nums* arrzap = new Nums[27];
	
	Stack* begin = NULL;
	char ss1, ss2, ssR = 'z' + 1;
	double op1 = 0, op2 = 0, res = 0,arr[28];

	for (int i = 0; i<len; i++)
	{
		arrzap[i].letter = str[i];
	}

	for (int i = 0; str[i] != '\0'; i++)
		if (arrzap[k].already==false)
			for (k = i + 1; str[k] != '\0'; k++)
				if (arrzap[i].letter == arrzap[k].letter) { arrzap[k].already = true; }
		
	cout << "Input data" << endl;

	for (i = 0; str[i] != '\0'; ++i)
		if (str[i] >= 'a' && str[i] <= 'z' && arrzap[i].letter == str[i] && arrzap[i].already == false) {
			cout << str[i] << " = ";
			cin >> arr[int(str[i] - 'a')];
		}

	for (i = 0; str[i] != '\0'; ++i) {
		if (!(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')) 
			begin = InS(begin, str[i]);
		else {        
			begin = OutS(begin, ss2);
			op2 = arr[int(ss2 - 'a')];
			begin = OutS(begin, ss1);
			op1 = arr[int(ss1 - 'a')];
			switch (str[i]){
			case '+':   res = op1 + op2;   break;
			case '-':   res = op1 - op2;   break;
			case '*':   res = op1 * op2;   break;
			case '/':   
				if (op2 == 0) {
					cout << "Error,devide by zero\n";
					delete[]arrzap;
					exit(0);
				}
				res = op1 / op2; 
				break;
			}
			arr[int(ssR - 'a')] = res;
			begin = InS(begin, ssR);
			ssR++;
		}
	}
	delete[]arrzap;
	cout << "Expression Resulst = " << res << endl;
}

void Expression(char *In)
{
	bool again;
	do {
		again = false;
		int bracket = 0;
		cout << " Input formula : ";
		cin >> In;
		if (In[0] == '+' || In[0] == '-' || In[0] == '*' || In[0] == '/' || (In[0] == ')'))
		{
			cout << "You can't put signs or close bracket at the beginning\n";
			again = true;
		}
		for (int i = 0; In[i] != '\0'; i++)
		{
			if (In[i] == '(')
			{
				if (In[i + 1] == '+' || In[i + 1] == '-' || In[i + 1] == '*' || In[i + 1] == '/' || In[i + 1] == ')') {
					cout << "You can't put signs after bracket\n"; again = true;
				}
				bracket++;
			}
			if (In[i] == ')')
			{
				if (In[i + 1] != '+' && In[i + 1] != '-' && In[i + 1] != '*' && In[i + 1] != '/' && In[i + 2] >= 'a' && In[i + 2] <= 'z')
				{
					cout << "You can't put vars after closed bracket\n"; again = true;
				}
				bracket--;
			}
			if (In[i] >= 'a' && In[i] <= 'z')
			{
				if (In[i + 1] >= 'a' && In[i + 1] <= 'z')
				{
					cout << "Enter vars in a row is unavailable\n";
					again = true;
				}
				if (In[i + 1] == '(')
				{
					cout << "You can't put open bracket after vars\n";
					again = true;
				}
			}
			if (In[i] == '+' || In[i] == '-' || In[i] == '*' || In[i] == '/')
			{
				if (In[i + 1] == '+' || In[i + 1] == '-' || In[i + 1] == '*' || In[i + 1] == '/') {
					cout << "Enter signs in a row is unavailable\n"; again = true;
				}
				if (In[i + 1] == ')') {
					cout << "You can't put brackets after signs\n";
					again = true;
				}
				if (In[i + 1] == '\0')
				{
					cout << "Expression should be ended\n";
					again = true;
				}
			}
		}
		if (bracket != 0) {
			cout << "Check bracket\n";
			again = true;
		}

	} while (again == true);
}