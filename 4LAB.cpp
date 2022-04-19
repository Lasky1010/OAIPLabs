#include <stdio.h>
#include <iostream>
using namespace std;

struct List {
	int info;
	List* next, * prev;
};
void Create(List**, List**, int);
void Add_List(int, List**, List**, int);
void View_List(int, List*);
void Free(List**);
void Task(List**, List**);
bool isEmpty(List*);


int main()
{
	List* begin = NULL, * end = NULL;
	int CHOICE, element, kod;
	bool Created = false;

	while (true)
	{
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << "\n1 - Create\n2 - Add\n3 - View\n4 - Task\n5 - FreeMemory\n0 - EXIT\n";
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cin >> CHOICE;
		system("cls");
		switch (CHOICE)
		{
		case 1:
			if (CHOICE == 1 && begin != NULL) {
				Free(&begin);
				cout << "Memory was cleared!" << endl;
			}
			cout << "Input 1st element : ";
			cin >> element;
			Create(&begin, &end, element);
			Created = true;
			break;
		case 2:
			if (Created == false) {
				cout << "List isn's created !!!\n";
				break;
			}
			else {
				cout << "Info = ";
				cin >> element;
				cout << "1 - Add Begin,2 - Add End : ";
				cin >> kod;
				Add_List(kod, &begin, &end, element);
				break;
			}

		case 3:
			if (isEmpty(begin)) break;
			cout << "1 - View Begin,2 - View End : ";
			cin >> kod;
			if (kod == 1) View_List(kod, begin);
			else View_List(kod, end);

			break;
		case 4:
			if (isEmpty(begin)) break;
			Task(&begin, &end);
			break;
		case 5:
			if (isEmpty(begin)) break;
			Free(&begin);
			Created = false;
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
bool isEmpty(List *begin) {
	if (!begin) {
		cout << "List is empty!" << endl; return true;
	}
	return false;
}
void Create(List** b, List** e, int element)
{
	List* t = new List;
	t->info = element;
	t->next = t->prev = NULL;
	*b = *e = t;
}

void Add_List(int kod, List** b, List** e, int element) {
	List* t = new List;
	t->info = element;
	if (kod == 1) {
		t->prev = NULL;
		t->next = *b;
		(*b)->prev = t;
		*b = t;
	}
	else if (kod == 2) {
		t->next = NULL;
		t->prev = *e;
		(*e)->next = t;
		*e = t;
	}
}
void View_List(int kod, List* p) {


	if (kod == 1) {
		while (p != NULL) {
			cout << p->info << endl;
			p = p->next;
		}
	}
	else if (kod == 2) {
		while (p != NULL) {
			cout << p->info << endl;
			p = p->prev;
		}
	}


}

void Free(List** p) {
	List* tmp;
	while (*p != NULL) {
		tmp = *p;
		*p = (*p)->next;
		delete tmp;
	}
}

void Task(List** b, List** e) {

	Add_List(1, b, e, 100500);
	List* tmp, * move, * even = NULL;
	tmp = *b;
	while (tmp->next) {
		if (tmp->next->info % 2 == 0) {
			move = tmp->next;
			tmp->next = move->next;
			tmp->next->prev = tmp;
			move->next = even;
			move->prev = even;
			even = move;
		}
		else tmp = tmp->next;
	}
	tmp = *b;
	(*b) = (*b)->next;
	delete tmp;

	cout << "Even list\n========\n";
	View_List(1, even);
	cout << "========\n";
	cout << "Odd list\n========\n";
	View_List(1, *b);
	cout << "========\n";
}
