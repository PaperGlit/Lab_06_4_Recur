#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

void Create(int* a, const int size, const int Low, const int High, int i)
{
	if (i < size)
	{
		a[i] = Low + rand() % (High - Low + 1);
		Create(a, size, Low, High, i + 1);
	}
}

void Print(int* a, const int size, int i)
{
	if (i < 1)
		cout << "Значення масиву : ";
	if (i < size)
	{
		cout << a[i] << " ";
		Print(a, size, i + 1);
	}
	else
		cout << endl;
}

int Min(int* a, const int size, int i, int min, int imin)
{
	if (i < size)
	{
		if (abs(a[i]) < min)
		{
			min = abs(a[i]);
			imin = i;
		}
		Min(a, size, i + 1, min, imin);
	}
	else
		return imin;
}

int Sum1(int* a, const int size, int j, int n)
{
	if (j < size)
	{
		n += abs(a[j]);
		Sum1(a, size, j + 1, n);
	}
	else 
		return n;
}

int Sum(int* a, const int size, int i, int s)
{
	if (i < size)
	{
		if (a[i] < 0)
		{
			s = Sum1(a, size, i + 1, 0);
			return s;
		}
		Sum(a, size, i + 1, s);
	}
	else
		return 0;
}

int* Sort(int* a, const int size, int j)
{
	if (j < size - 1)
	{
		a[j] = a[j + 1];
		a[j + 1] = 0;
		Sort(a, size, j + 1);
	}
	else
		return a;
}

const int N(int* a, const int size, int i, int k, int b, int c)
{
	if (i < size)
	{
		if (a[i] >= b && a[i] <= c)
			k++;
		N(a, size, i + 1, k, b, c);
	}
	else
	{
		const int n = size - k;
		return n;
	}
}

int* Compress(int* a, const int size, int i, int b, int c)
{
	if (i < size)
	{
		if (a[i] >= b && a[i] <= c)
		{
			Sort(a, size, i);
			Compress(a, size, i, b, c);
		}
		else
			Compress(a, size, i + 1, b, c);
	}
	else
		return a;
}

int main()
{
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));

	int n, Low, High, a, b;

	cout << "n = "; cin >> n;
	cout << "min = "; cin >> Low;
	cout << "max = "; cin >> High;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;

	int* c = new int[n];

	Create(c, n, Low, High, 0);
	Print(c, n, 0);
	cout << "imin = " << Min(c, n, 1, abs(c[0]), 0) << endl;
	cout << "Sum = " << Sum(c, n, 0, 0) << endl;
	Print(Compress(c, n, 0, a, b), N(c, n, 0, 0, a, b), 0);

	return 0;
}