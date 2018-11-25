#include <iostream>
#include <utility>
#include <string>
#include <functional>
#include <vector>
#include <unistd.h>
#include "matrix.hpp"

//#define POLICY_ITERATOR

using sjtu::Matrix;

std::pair<bool, std::string> RE(const std::string &name)
{
	return std::make_pair(false, "Runtime Error! (" + name + ")");
};

std::pair<bool, std::string> WA(const std::string &name)
{
	return std::make_pair(false, "wrong answer! (" + name + ")");
};

std::pair<bool, std::string> testConst()
{
	const Matrix<int> a = {{ 1, 2 },
						   { 3, 4 }};
	const Matrix<int> std_tran = {{ 1, 3 },
								  { 2, 4 }};
	const Matrix<int> std_row0 = {{ 1, 2 }};
	const Matrix<int> std_col0 = {{ 1 },
								  { 3 }};
	if (a.tran() != std_tran)
		WA("tran");
	if (a.row(0) != std_row0)
		WA("row0");
	if (a.column(0) != std_col0)
		WA("col0");
	if (a.size() != std::make_pair((size_t) 2, (size_t) 2))
		WA("size");
	if (a.rowLength() != 2)
		WA("rowLength");
	if (a.columnLength() != 2)
		WA("columnLength");
	if (a + a != a * 2 || a * 2 - a != a)
		WA("operator wrong");
	return { true, "Congratulation!" };
};

void ceTest()
{
	Matrix<int> a;
	Matrix<double> b;

	auto a1 = a * 5;
	a1 = 5 * a;
	a1 = 0.5 * a;

	auto a2 = a * b;
}

std::pair<bool, std::string> testCtorAssignment()
{
	std::initializer_list<std::initializer_list<int>> intIl = {{ 0, 1, 2, 3 },
															   { 1, 2, 3, 4 },
															   { 2, 3, 4, 5 }};
	std::initializer_list<std::initializer_list<double>> doubleIl = {{ 0.1, 1.1, 2.2, 3.3 },
																	 { 1.4, 2.5, 3.4, 4.3 },
																	 { 2.1, 3.2, 4.3, 5.4 }};
	auto checkMat = [&](const Matrix<int> &a)
	{
		for (size_t i = 0; i < 3; ++i)
			for (size_t j = 0; j < 4; ++j)
				if (a(i, j) != i + j)
					return false;
		return true;
	};

	// default constructor
	try
	{
		Matrix<int> a;
	} catch (...)
	{
		return RE("Matrix()");
	}

	// Matrix(std::size_t, ...)
	try
	{
		Matrix<double> a(4, 5, 0.1);
		Matrix<int> b(1, 1);
	} catch (...)
	{
		return RE("Matrix(std::size_t, std::size_t, T)");
	}

	// initializer_list
	try
	{
		Matrix<int> a = intIl;
		if (!checkMat(a))
			return WA("initializer_list ctor");
	} catch (...)
	{
		return RE("initializer_list ctor");
	}

	// copy ctor & assignment
	try
	{
		Matrix<double> a = doubleIl;
		Matrix<int> b(a);
		if (!checkMat(b))
			return WA("copy ctor");
		b = b;
		if (!checkMat(b))
			return WA("copy ctor");
		a = b;
	} catch (...)
	{
		return RE("copy ctor or assignment");
	}
	return { true, "Congratulation!" };
};

std::pair<bool, std::string> testSizeEtc()
{
	// row/column length
	try
	{
		Matrix<int> a(3, 4);
		if (a.rowLength() != 3 || a.columnLength() != 4)
			return WA("row/column lengh");
	} catch (...)
	{
		return RE("row/column length");
	}

	// size / clear
	try
	{
		Matrix<int> a = {{ 0, 1, 2, 3 },
						 { 1, 2, 3, 4 },
						 { 2, 3, 4, 5 }};
		if (a.size().first != 3 || a.size().second != 4)
			return WA("size");
		a.clear();
		if (a.size().first != 0 || a.size().second != 0)
			return WA("clear");
	} catch (...)
	{
		return RE("size/clear");
	}

	// row / column
	try
	{
		Matrix<int> a = {{ 0, 1, 2, 3 },
						 { 1, 2, 3, 4 },
						 { 2, 3, 4, 5 }};
		auto m = a.row(0);
		for (int i = 0; i < 4; ++i)
			if (m(0, (std::size_t) i) != i)
				return WA("row");
		m = a.column(1);
		for (int i = 0; i < 3; ++i)
			if (m((std::size_t) i, 0) != i + 1)
				return WA("column");
	} catch (...)
	{
		return RE("row/column");
	}

	return { true, "Congratulation!" };
};

std::pair<bool, std::string> testOperations()
{
	std::initializer_list<std::initializer_list<int>> intIl = {{ 0, 1, 2, 3 },
															   { 1, 2, 3, 4 },
															   { 2, 3, 4, 5 }};
	Matrix<int> a = intIl;

	auto iterCheck = [&](std::function<bool(std::size_t, std::size_t)> condition)
	{
		for (std::size_t i = 0; i < 3; ++i)
			for (std::size_t j = 0; j < 4; ++j)
				if (!condition(i, j))
					return false;
		return true;
	};

	a = a = a = a = a;
	// tran
	try
	{
		Matrix<int> stdt(4, 3);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 4; ++j)
				stdt((std::size_t) j, (std::size_t) i) = i + j;
		if (a.tran() != stdt)
			return WA("tran");
	} catch (...)
	{
		return RE("tran");
	}

	// ==, !=
	try
	{
		Matrix<long> l(a);
		if (a != l)
			return WA("!=");
		l.resize(1, 1);
		if (a == l)
			return WA("==");
	} catch (...)
	{
		return RE("==/!=");
	}

	// -, *=
	try
	{
		auto b = a;
		b *= 2;
		if (!iterCheck([&](std::size_t i, std::size_t j)
					   {
						   return b(i, j) == 2 * a(i, j);
					   }))
			return WA("*=");
		b = -b;
		if (!iterCheck([&](std::size_t i, std::size_t j)
					   {
						   return b(i, j) == -2 * a(i, j);
					   }))
			return WA("-");
	} catch (...)
	{
		return RE("- / *=");
	}

	bool thrown = false;
	// +=, -=
	try
	{
		auto b = a;
		b += a;
		if (b != 2 * a)
			return WA("+=");
		b -= a;
		if (b != a)
			return WA("-=");
		Matrix<int> c(1, 2);
		b += c;
	} catch (const std::invalid_argument &msg)
	{
		thrown = true;
	} catch (...)
	{
		return RE("+= / -=");
	}
	if (!thrown)
		return WA("+=");

	// +, -, *
	thrown = false;
	try
	{
		Matrix<double> b(a);
		auto c = a + b;
		if (typeid(c(0, 0)) != typeid(b(0, 0)))
			return WA("+");
		Matrix<int> d = a + a;
		if (d != 2 * a)
			return WA("+");
		d = d - a;
		if (d != a)
			return WA("-");
		auto e = 2.0 * a;
		if (typeid(e(0, 0)) != typeid(2.0))
			return WA("scalar multiplication");
		auto f = b * a.tran();
		if (typeid(f(0, 0)) != typeid(b(0, 0)))
			return WA("*");
	} catch (...)
	{
		return RE("+ / - / *");
	}
	try
	{
		Matrix<int> b(1, 1);
		auto c = a * b;
	} catch (const std::invalid_argument &msg)
	{
		thrown = true;
	} catch (...)
	{
		return RE("+ / - / *");
	}
	if (!thrown)
		return WA("*");

	return { true, "Congratulation!" };
};

struct Int
{
	int num;
};

std::pair<bool, std::string> testIterator()
{


	Matrix<int> a = {
			// 0  1  2  3
			{ 0,  1,  2,  3 },    // 0
			{ 4,  5,  6,  7 },    // 1
			{ 8,  9,  10, 11 },  // 2
			{ 12, 13, 14, 15 } // 3
	};

	// begin, end, ++, *
	try
	{
		int k = 0;
		for (auto &&item : a)
		{
			if (item != k++)
				return WA("begin, end, ++, *");
		}
	} catch (...)
	{
		return RE("begin, end, ++, *");
	}

	// subMatrix
	try
	{
		decltype(a.begin()) beg, end;
		std::tie(beg, end) = a.subMatrix({ 1, 1 }, { 2, 3 });
		int ans[] = { 5, 6, 7, 9, 10, 11 };
		int k = 0;
		for (auto iter = beg; iter != end; ++iter)
		{
			if (ans[k++] != *iter)
				return WA("subMatrix");
		}
	} catch (...)
	{
		return RE("subMatrix");
	}

	// -
	try
	{
		auto itera = a.begin() + 2, iterb = a.begin() + 8;
		if (iterb - itera != 6)
			return WA("iter - iter");
	} catch (...)
	{
		return RE("iter - iter");
	}

	// ->
	try
	{
		Matrix<Int> b(1, 1);
		b(0, 0).num = 123;
		if (b.begin()->num != 123)
			return WA("->");
	} catch (...)
	{
		return RE("->");
	}

	return { true, "Congratulation!" };
};

#ifdef POLICY_ITERATOR

std::pair<bool, std::string> testPolicyIterator()
{
	Matrix<int> a = {{ 0, 1,  2 },
					 { 3, 4,  5 },
					 { 6, 7,  8 },
					 { 9, 10, 11 }};

	std::vector<int> stdans;
	std::vector<int> ans;

	try
	{
		stdans = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		for (auto iter = a.begin<Matrix<int>::RowIterator>(); iter != a.end<Matrix<int>::RowIterator>(); ++iter)
		{
			ans.push_back(*iter);
		}
		if (ans != stdans)
			return WA("RowIterator");
		ans.clear();
	} catch (...)
	{
		return RE("RowIterator");
	}

	try
	{
		stdans = { 0, 3, 6, 9, 1, 4, 7, 10, 2, 5, 8, 11 };
		for (auto iter = a.begin<Matrix<int>::ColumnIterator>(); iter != a.end<Matrix<int>::ColumnIterator>(); ++iter)
		{
			ans.push_back(*iter);
		}
		if (ans != stdans)
			return WA("ColumnIterator");
		ans.clear();
	} catch (...)
	{
		return RE("ColumnIterator");
	}

	a = {{ 0, 1, 2 },
		 { 3, 4, 5 },
		 { 6, 7, 8 }};
	try
	{
		stdans = { 0, 4, 8 };
		for (auto iter = a.begin<Matrix<int>::TraceIterator>(); iter != a.end<Matrix<int>::TraceIterator>(); ++iter)
		{
			ans.push_back(*iter);
		}
		if (ans != stdans)
			return WA("TraceIterator");
	} catch (...)
	{
		return RE("TraceIterator");
	}


	return { true, "Congratulation!" };
};

#else

std::pair<bool, std::string> testPolicyIterator() {
	return {true, "Anyway, congratulation!"};
};

#endif

int main()
{
	ceTest();
	std::pair<std::string, std::function<std::pair<bool, std::string>(void)>> testcases[] = {{ "testCtorAssignment", testCtorAssignment },
																							 { "testSizeEtc",        testSizeEtc },
																							 { "testOperations",     testOperations },
																							 { "testIterator",       testIterator },
																							 { "testPolicyIterator", testPolicyIterator },
																							 { "testConst",          testConst }};

	bool result;
	std::string information;
	for (auto &&testcase : testcases)
	{
		std::cout << testcase.first << ": ";
		std::tie(result, information) = testcase.second();
		if (result)
		{
			std::cout << "PASS. " << information << std::endl;
		} else
		{
			std::cout << "FAIL. " << information << std::endl;
		}
	}

	return 0;
}
