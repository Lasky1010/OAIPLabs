
#include <iostream>
#include <conio.h>  
using namespace std;

struct Tree {
	int info;
	Tree* left, * right;
};
// Удалить элемент по ключу
// Создать сбалансированное дерево
Tree* list(int);
//Tree* create(Tree*);
void add(Tree*, int);
void view(Tree*, int);
void Search(Tree*, int);
Tree* del(Tree*);
Tree* DelKey(Tree*, int);
void sort(int *arr, int n);
void Infiks(Tree*&);
void Obratnii(Tree*&);
void Make_Balance(Tree**, int, int, int*);
void Task(Tree*);
int find(Tree* t, int mindif, int avg);


int main() {
	Tree* root = NULL;
	int choice, in, n = 1, * arr = new int(0), k = 0,key=0;
	bool created = false;
	while (true) {
		cout << "------------ MENU ------------\n";
		cout << "\t1 - Create\n\t2 - Add\n\t3 - View\n\t"
			 "4 - Balance Tree\n\t5 - Delete element\n\t6 - Individual Task\n\t"
			"7 - Search\n\t8 - Pryamoi\n\t9 - Obratnii\n\t10 - Free Memory\n\t0 - EXIT\n";
		cout << "--------------------------------\n >>> ";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			if (root) {
				cout << "Error!\nClear memory!\n";
				break;
			}
			cout << " >>> Input Root : ";
			cin >> in;
			root = list(in);
			break;
		case 2:

			cin >> n;
			arr = new int[n];
			for (int i = 1; i <= n; i++) {
				cout << " Input info #" << i << ": ";
				cin >> in;
				arr[i - 1] = in;
				created = true;
				if (!root) root = list(in);
				else add(root, in);
			}
			view(root, 0);
			break;
		case 3:
			if (!root) {
				cout << "Tree is not created!\nCreate it by pressing 1\n";
				break;
			}
			view(root, 0);
			break;
		case 4:
			if (!root) {
				cout << "Tree is not created!\nCreate it by pressing 1\n";
				break;
			}
			if (created == true)
			{
				sort(arr, n);
				
				Make_Balance(&root, 0, n,arr);
				view(root, 0);
			}
			break;

		case 5:
			if (!root) {
				cout << "Tree is not created!\nCreate it by pressing 1\n";
				break;
			}
			cout << "Enter desired key for deleting\n";

			cin >> key;
			DelKey(root, key);
			break;
		case 6:
			Task(root);
			break;
		case 7:
			cout << "Enter desired key : ";
			cin >> key;
			Search(root,key);
			break;
		case 8:
			Infiks(root);
			break;
		case 9:
			Obratnii(root);
			break;
		

		case 10:
			root = del(root);
			cout << "Tree removed!\n";
			break;
		case 0:
			if (root)
				root = del(root);
			return 0;
		}
	}
}

Tree* list(int in) {
	Tree* t = new Tree;
	t->info = in;
	t->left = t->right = NULL;
	return t;
}

void add(Tree* root, int in) {
	Tree* prev = NULL, * t = root;
	bool is_find = 0;
	while (t && !is_find) { // заменить на поиск по всему дереву
		prev = t;
		if (in == t->info) {
			is_find = 1;
			cout << "Element " << in << " already exists\n";
		}
		else {
			if (in < t->info) t = t->left;
			else t = t->right;
		}
	}
	if (!is_find) {
		t = list(in);
		if (in < prev->info) prev->left = t;
		else prev->right = t;
	}
}

void view(Tree* t, int level) {
	if (t) {
		view(t->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "    ";
		cout << t->info << endl;
		view(t->left, level + 1);
	}
}


Tree* del(Tree* t) {
	if (t) {
		del(t->left);
		del(t->right);
		delete t;
	}
	return NULL;
}

void Search(Tree* root, int key)
{
	Tree* t = root;
	bool search = false;
	while (t != NULL)
	{
		if (t->info > key)
		{
			t = t->left;
		}
		else if (t->info < key)
		{
			t = t->right;
		}
		else
		{
			search = true;
			cout << t->info << endl;
			break;
		}
	}
	if (!search)
	{
		cout << "This key doenst exist\n";
	}
}


Tree* DelKey(Tree* root, int key)
{
	Tree* Del = root, * Prev_Del = NULL, * R = NULL, * Prev_R = NULL;
	// Del, Prev_Del – удаляемый узел и его предыдущий (предок); 
	// R, Prev_R – элемент, на который заменяется удаленный узел, и его предок;
	//-------- Поиск удаляемого элемента и его предка по ключу key ---------
	while (Del != NULL && Del->info != key) {
		Prev_Del = Del;
		if (Del->info > key) Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) { // Элемент не найден
		cout << "This key doenst exist\n";
		return root;
	}
	//-------------------- Поиск элемента R для замены --------------------------------
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			//---------------- Ищем самый правый узел в левом поддереве -----------------
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			//----------- Нашли элемент для замены R и его предка Prev_R -------------
			if (Prev_R == Del) R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
	if (Del == root) root = R; // Удаляя корень, заменяем его на R
	else
		//------- Поддерево R присоединяем к предку удаляемого узла -----------
		if (Del->info < Prev_Del->info)
			Prev_Del->left = R; // На левую ветвь
		else
			Prev_Del->right = R; // На правую ветвь
	delete Del;
	return root;
}


void Make_Balance(Tree** root, int begin, int end, int* a) {
	if (begin == end) {
		*root = NULL;
		return;
	}
	else {
		int mid = (begin + end) / 2;
		*root = new Tree;
		(*root)->info = a[mid];
		Make_Balance(&(*root)->left, mid, end, a);
		Make_Balance(&(*root)->right, begin, mid + 1, a);
	}
}

int find(Tree* t, int mindif, int avg)
{
	if (t)
	{
		find(t->right, mindif, avg);
		if (abs(t->info - avg) < mindif)
			mindif = abs(t->info - avg);
		find(t->left, mindif, avg);
	}
	return mindif;
}

void Task(Tree*root)
{
	Tree* t = NULL, * min = root, * max = root;
	double avg=0,mindif=0;
	while (min->left != NULL) min= min->left; 
	while (max->right != NULL) max = max->right;
	avg=(double)(min->info + max->info) / 2;
	cout << "Average of Max & Min values = " << avg << endl;
	if (root->info == avg)
	{
		cout << "The Closest value to averageMIN-MAX = " << avg;
		return;
	}
	mindif = abs(root->info-avg);
	t = root;
	mindif = find(t, mindif, avg);
	/*t = root->right;
	while (t!=NULL)
	{
		if (abs(t->info - avg) < mindif)
		{
			mindif = abs(t->info - avg);
		}
		else t = t->right;
	}*/
	cout << t->info << endl;;


}
void sort(int* arr, int n)
{
	for (int i = 0; i < n-1; i++)
		for (int j = i+1; j< n; j++)
			if (arr[j] < arr[i]) {
				int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
			}
}

void Prefiks(Tree*& root)
{
	Tree* t = root;
	while (t != NULL)
	{
		cout << root->info << endl;
		Prefiks(t->left);
		Prefiks(t->right);
	}

}

void Infiks(Tree*& root)
{
	Tree* t = root;
	if (t != NULL)
	{
		Infiks(t->left);
		cout << root->info << endl;
		Infiks(t->right);
	}

}

void Obratnii(Tree*& root)
{
	Tree* t = root;
	if (t != NULL)
	{
		Obratnii(t->right);
		cout << root->info << endl;
		Obratnii(t->left);
	}

}



