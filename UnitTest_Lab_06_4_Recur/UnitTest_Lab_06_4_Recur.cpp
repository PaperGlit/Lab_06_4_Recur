#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_06_4_Recur/Lab_06_4_Recur.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void Loop(int* a, int* c, const int size, int i)
{
	if (i < size)
	{
		Assert::AreEqual(a[i], c[i]);
		Loop(a, c, size, i + 1);
	}
}

int TestMin(int* a, const int size, int i, int min, int imin)
{
	if (i < size)
	{
		if (abs(a[i]) < min)
		{
			min = abs(a[i]);
			imin = i;
		}
		TestMin(a, size, i + 1, min, imin);
	}
	else
		return imin;
}

int TestSum1(int* a, const int size, int i, int n)
{
	if (i < size)
	{
		n += abs(a[i]);
		TestSum1(a, size, i + 1, n);
	}
	else
		return n;
}

int TestSum(int* a, const int size, int i, int n)
{
	if (i < size)
	{
		if (a[i] < 0)
		{
			n = TestSum1(a, size, i + 1, 0);
			return n;
		}
		TestSum(a, size, i + 1, n);
	}
	else
		return 0;
}

int* TestSort(int* a, const int size, int j)
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

int* TestCompress(int* a, const int size, int i, int b, int c)
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

void Test(int* a, int* n, const int size, int b, int c)
{
	Assert::AreEqual(TestMin(a, size, 1, abs(a[0]), 0), Min(a, size, 1, abs(a[0]), 0));
	Assert::AreEqual(TestSum(a, size, 0, 0), Sum(a, size, 0, 0));
	a = (TestCompress(a, size, 0, b, c));
	n = (Compress(n, size, 0, b, c));
	Loop(a, n, size, 0);
}

namespace UnitTestLab064Recur
{
	TEST_CLASS(UnitTestLab064Recur)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int n = 10;
			int c[n];
			int Low = -10, High = 10, a = 5, b = 10;
			int* d = c;
			Create(c, n, Low, High, 0);
			Test(c, d, n, a, b);
		}
	};
}