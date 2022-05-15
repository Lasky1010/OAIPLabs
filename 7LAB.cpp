#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>  
using namespace std;

struct Hash {
	int time;
	Hash* next;
};
struct Fly {
	char Dest[20];
	int Time, numb;
};
Hash** create(int m);
void Add(Fly*arr,int i,int m,Hash**H);
Hash* Search(int Time, int m, Hash** H);
void Delete(int m, Hash** H);
void FILLARRAY(Fly[],int i);
void VIEW(Fly*,int i);



int main()
{
	int CHOICE;
	const int n = 3;
	const int m = 10;
	Fly arr[n];
	Hash **H=create(m);
	
	while (true)
	{
		cout <<"\n============MENU===========\n";
		cout << "\t1 - Fill struck\n\t2 - View\n\t3 - Hash\n\t5 - Delete\n\t0 - Exit\n";
		cout << "\n===========================\n";
		cout << " >>>";
		cin >> CHOICE;
		system("cls");
		switch (CHOICE)
		{
		case 1:
			for (int i = 0; i < n; i++)
				FILLARRAY(arr, i);
			break;
		case 2:
			for (int i = 0; i < n; i++)
				VIEW(arr, i);
			break;
		case 3:
			for (int i = 0; i < n; i++)
				Add(arr,i, m, H);
			cout << "Completed\n";
			break;
		case 4:
			Hash * p;
			int ss;
			cout << "Enter desired time (or -1 to end)-> ";
			cin >> ss;
			while (ss!=-1)
			{
				p=Search(ss, m, H);
				if (p==NULL)
					cout << "This element doesnt exist\n";
				else {
					//cout << p->time<<endl;
					for (int i = 0; i < n; i++)
						if (p->time == arr[i].Time)
							VIEW(arr, i);
				}
				cin >> ss;
			}
			Delete(m, H);
			break;
		default:case 0:
			return 0;
			break;
		}
	}

}



Hash** create(int m)
{
	Hash** H = new Hash* [m];
	for (int i = 0; i < m; i++)
		H[i] = NULL;
	return H;
}


void Add(Fly *arr,int k, int m, Hash** H)
{
	Hash* spt = new Hash;
	spt->time = arr[k].Time;
	int i = arr[k].Time % m;
	if (H[i] == NULL) { 
		H[i] = spt; 
		spt->next = NULL;
	}
	else {
		spt->next = H[i];
		H[i] = spt;
	}
		
		
}
Hash* Search(int Time, int m, Hash** H)
{
	int i = abs(Time % m);
	Hash* spt = H[i];
	while (spt != NULL)
	{
		if (spt->time = Time) return spt;
		spt = spt->next;
	}
	return NULL;
}
void Delete(int m, Hash** H)
{
	Hash* spt, * sp;
	for (int i = 0; i < m; i++)
	{
		cout << "H["<<i<<"]= ";
		sp = H[i];
		while (sp!=NULL)
		{
			spt = sp;
			sp = sp->next;
			delete spt;
		}
		cout << endl;
	}
	delete[]H;

}

void FILLARRAY(Fly arr[], int i) {
	cout << "\nDestination -> ";
	scanf("%s", arr[i].Dest);
	cout << "\nNumber -> ";
	cin >> arr[i].numb;
	cout << "\nTime -> ";
	cin >> arr[i].Time;
	cout << endl;
}

void VIEW(Fly *arr,int i)
{
	cout<<arr[i].Dest<<endl;
	cout<< arr[i].numb<<endl;
	cout<<arr[i].Time<<endl;
	cout << endl;
}
