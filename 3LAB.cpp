#include <stdio.h>
#include <iostream>
using namespace std;

struct Stack {
	int info;
	Stack* next;
};

Stack *Add (Stack* , int );
void View (Stack *);
void Free(Stack** );
void Task(Stack* );

int main()
{
	Stack* begin=NULL;
	int choice,n,in;

	while (true)
	{
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << "\n1 - Create\n2 - Add\n3 - View\n4 - Task\n5 - FreeMemory\n0 - EXIT\n";
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1: case 2:
			if (choice == 1 && begin != NULL) {
				Free(&begin);
				cout << "Memory was cleared!" << endl;
				break;
			}
			cout << "Input amount : "; 
			cin >> n;
			for (int i = 1; i <= n; i++) {
				in = rand()%21-10;
				begin = Add(begin, in);
			}
			if (choice == 1)
				cout << "Created " << n << " elements" << endl;
			else 
				cout << "Added " << n <<" elements" << endl;
			break;
		case 3:
			if (!begin) {
			cout << "Stack is empty!" << endl;
			break;
			}
			cout << "--- Stack ---" << endl;
			View(begin);
			break;
		case 4:
			if (!begin) {
				cout << "Stack is empty!" << endl;
				break;
			}
			Task(begin);
			break;
		case 5:
			Free(&begin);
			cout << "Memory Free!" << endl;
			break;
		case 0:
			if (begin != NULL)
				Free(&begin);
			cout << "Closed\n";
			return 0;
		}
	}
}


Stack *Add(Stack* p, int element) {
	Stack *tmp = new Stack;
	tmp->info = element; 
	tmp->next = p; 
	return tmp;
}

void View(Stack* p) {

	while (p != NULL) {
		cout << p -> info <<endl;
		p = p->next;
	}
}

void Free(Stack** p) {
	Stack* tmp;
	while (*p != NULL){
		tmp = *p;
		*p = (*p)->next;
		delete tmp;
	}
}

void Task(Stack* p) {
	p = Add(p, 100500);
	Stack* tmp,*move,*even=NULL;
	tmp = p;
	while (tmp->next) {
		if (tmp->next->info % 2 == 0) {
			move = tmp->next;
			tmp->next = move->next;
			move->next = even;
			even = move;
		}
		else tmp = tmp->next;
	}
	tmp = p;
	p = p->next;
	delete tmp;
	cout << "Even list\n========\n";
	View(even);
	cout <<"========\n";
	cout << "Odd list\n========\n";
	View(p);
	cout << "========\n";
}