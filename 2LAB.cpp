#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include<io.h>
using namespace std;
struct Database {
	char Destination[14], Type[9];
	int flightnumber, Time;
};

struct QuickStack {
	int Left, Right;
};
void create(FILE*, FILE*);
void add(FILE*, int);
void view(FILE*, FILE*, int);
void Sort(FILE*, FILE*, int, bool&);
void Search(FILE*, FILE*, int, bool);
void outsort(int, Database*, FILE*);
void QuickSort(int, Database*, bool&);
void ChooseSort(int, Database*, bool&);
void LineSearch(int, Database*);
void BinarySearch(int, Database*, bool);

int main()
{
	FILE* inputfile = fopen("input.txt", "a+b"), * sortedfile = fopen("input.txt", "a+");
	int choice = 0, size = sizeof(Database);
	bool sorted = false;
	while (true)
	{
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << "\n1 - Create\n2 - Add\n3 - View\n4 - Sort\n5 - Search\n0 - Exit\n";
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";

		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			create(inputfile, sortedfile);
			break;
		case 2:
			add(inputfile, size);
			break;
		case 3:
			view(inputfile, sortedfile, size);
			break;
		case 4:
			Sort(inputfile, sortedfile, size, sorted);

			break;
		case 5:
			Search(inputfile, sortedfile, size, sorted);
			break;
		case 0:
			cout << "Closed\n";
			return 0;
		}
	}
}

void create(FILE* inputfile, FILE* sortedfile)
{
	freopen("out.txt", "w", sortedfile);
	freopen("input.txt", "wb", inputfile);
	if (inputfile == NULL) { puts("\n Create ERROR!"); return; }
	fclose(inputfile);
	fclose(sortedfile);
	cout << "\nCreated new file - input.txt\n";
}

void add(FILE* inputfile, int size)
{
	Database flight;
	inputfile = fopen("input.txt", "a+b");
	printf("\nF.Number - ");
	fflush(stdin);
	cin >> flight.flightnumber;
	printf("\nDestination - ");
	cin >> flight.Destination;
	printf("\nDeparture time - ");
	cin >> flight.Time;
	printf("\nType - ");
	cin >> flight.Type;
	fwrite(&flight, size, 1, inputfile);
	fclose(inputfile);
}

void view(FILE* inputfile, FILE* sortedfile, int size)
{
	sortedfile = fopen("out.txt", "w");
	Database flight;
	if ((inputfile = fopen("input.txt", "rb")) == NULL) { puts("\n Open ERROR!"); return; }
	while (fread(&flight, size, 1, inputfile)) {
		fprintf(sortedfile, "\n%d\t%s\t%d\t%s\n", flight.flightnumber, flight.Destination, flight.Time, flight.Type);
		cout << flight.flightnumber << "\t" << flight.Destination << "\t" << flight.Time << "\t" << flight.Type << endl;
	}
	fclose(inputfile);
	fclose(sortedfile);
}

void Sort(FILE* inputfile, FILE* sortedfile, int size, bool& sorted)
{
	Database* arrzap;
	int kol = 0;
	long len = 0;
	int parametr = 0;
	sortedfile = fopen("out.txt", "w");
	inputfile = fopen("input.txt", "r");
	len = _filelength(_fileno(inputfile));
	kol = len / size;
	arrzap = new Database[kol];
	fread(arrzap, size, kol, inputfile);
	fclose(inputfile);
	cout << "\nSort how ?";
	cout << "\n\t1 - Quick sort\n\t2 - ChooseSort\n";
	cin >> parametr;
	switch (parametr)
	{
	default:case 1:
		QuickSort(kol, arrzap, sorted);
		break;
	case 2:
		ChooseSort(kol, arrzap, sorted);
		break;
	}
	outsort(kol, arrzap, sortedfile);
	delete[]arrzap;
	fclose(inputfile);
	fclose(sortedfile);
}

void ChooseSort(int kol, Database* arrzap, bool& sorted)
{
	for (int i = 0; i < kol - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < kol; j++)
			if (arrzap[min].Time > arrzap[j].Time) min = j;
		Database r = arrzap[min];
		arrzap[min] = arrzap[i];
		arrzap[i] = r;
	}
	sorted = true;
}

void QuickSort(int kol, Database* arrzap, bool& sorted)
{
	QuickStack arrstack[20];
	int i, j, L, R, s = 0, x;
	arrstack[0].Left = 0, arrstack[0].Right = kol - 1;
	while (s != -1)
	{
		L = arrstack[s].Left;
		R = arrstack[s].Right;
		s--;
		while (L < R)
		{
			i = L, j = R; x = arrzap[(L + R) / 2].Time;
			while (i <= j)
			{
				while (arrzap[i].Time < x)i++;
				while (arrzap[j].Time > x)j--;
				if (i <= j)
				{
					Database temp = arrzap[i];
					arrzap[i] = arrzap[j];
					arrzap[j] = temp;
					i++; j--;
				}
			}
			if ((j - L) < (R - i))
			{
				if (i < R)
				{
					s++;
					arrstack[s].Left = i;
					arrstack[s].Right = j;
				}
				R = j;
			}

			else
			{
				if (L < j)
				{
					s++; arrstack[s].Left = L;
					arrstack[s].Right = j;
				}
				L = i;
			}
		}
	}
	sorted = true;
}

void Search(FILE* inputfile, FILE* sortedfile, int size, bool sorted)
{
	Database* arrzap;
	int kol = 0;
	long len = 0;
	int parametr = 0;
	sortedfile = fopen("out.txt", "w");
	inputfile = fopen("input.txt", "r");
	len = _filelength(_fileno(inputfile));
	kol = len / size;
	arrzap = new Database[kol];
	fread(arrzap, size, kol, inputfile);
	fclose(inputfile);
	cout << "\nSearch how ?";
	cout << "\n\t1 - Straight search\n\t2 - Binary search\n";
	cin >> parametr;
	switch (parametr)
	{
	default:case 1:
		LineSearch(kol, arrzap);
		break;
	case 2:
		BinarySearch(kol, arrzap, sorted);
		break;
	}
	delete[]arrzap;
	fclose(inputfile);
	fclose(sortedfile);
}

void LineSearch(int kol, Database* arrzap)
{
	char fkey[14];
	int kod = 0;
	cout << "Enter desired destination : ";
	cin >> fkey;
	for (int i = 0; i < kol; i++) {
		if (strcmp(arrzap[i].Destination, fkey) == 0) {
			kod = 1;
			cout << arrzap[i].flightnumber << "\t" << arrzap[i].Destination << "\t" << arrzap[i].Time << "\t" << arrzap[i].Type << endl;
		}
	}
	if (kod == 0) cout << "Not found\n"; return;
}

void BinarySearch(int kol, Database* arrzap, bool sorted)
{
	if (sorted == false) QuickSort(kol, arrzap, sorted);

	char fkey[14];
	cout << "Enter desired destination : ";
	cin >> fkey;
	int i = 0, j = kol - 1, m;
	while (i < j) {
		m = (i + j) / 2;
		if (strcmp(arrzap[i].Destination, fkey) == 0) i = m + 1;
		else j = m;
	}
	if (strcmp(arrzap[i].Destination, fkey) == 1)
		cout << "Destination isn't find\n";  return;
	cout << arrzap[i].flightnumber << "\t" << arrzap[i].Destination << "\t" << arrzap[i].Time << "\t" << arrzap[i].Type << endl;
}

void outsort(int kol, Database* arrzap, FILE* outfile)
{
	for (int i = 0; i < kol; i++) {
		cout << arrzap[i].flightnumber << "\t" << arrzap[i].Destination << "\t" << arrzap[i].Time << "\t" << arrzap[i].Type << endl;
		fprintf(outfile, "\n%d\t%s\t%d\t%s\n", arrzap[i].flightnumber, arrzap[i].Destination, arrzap[i].Time, arrzap[i].Type);
	}

}
