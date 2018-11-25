#include "testint.hpp"
#include "matrix.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using sjtu::Matrix;

std::pair<bool, std::string> RE(const std::string &name)
{
	return std::make_pair(false, "Runtime Error! (" + name + ")");
};

std::pair<bool, std::string> WA(const std::string &name)
{
	return std::make_pair(false, "wrong answer! (" + name + ")");
};

std::pair<bool, std::string> TLE(double time)
{
	std::stringstream ss;
	ss << "Your time is " << time;
	return std::make_pair(false, "Time Limit Exceeded!" + ss.str());
};

std::pair<bool, std::string> PASS(double time)
{
	std::stringstream ss;
	ss << "Your relative time is " << time;
	return std::make_pair(true, ss.str());
};

template <class T>
std::string toString(const T &x)
{
	std::stringstream ss;
	ss << x;
	return ss.str();
}

std::pair<bool, std::string> resizeTest()
{
	const int N = 200, M = 300;
	Matrix<int> a(N, M);
	int cnt = 0;
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			a(i, j) = cnt++;
	const int N1 = 300, M1 = 300;

	a.resize(N1, M1);
	cnt = 0;
	for (size_t i = 0; i < N1; i++)
		for (size_t j = 0; j < M1; j++, cnt++)
			if (a(i, j) != (cnt < N * M ? cnt : 0)) return WA("resize");

	const int N2 = 500, M2 = 100;
	a.resize(std::make_pair(size_t(N2), size_t(M2)));
	cnt = 0;
	for (size_t i = 0; i < N2; i++)
		for (size_t j = 0; j < M2; j++, cnt++)
			if (a(i, j) != cnt) return WA("resize");

	Matrix<testint> b(N, M);
	Matrix<int> judgecode(1, N * M);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			judgecode(0, i * M + j) = b(i, j).judge();
	b.resize(M, N);
	for (size_t i = 0; i < M; i++)
		for (size_t j = 0; j < N; j++)
			if (b(i, j).judge() != judgecode(0, i * N + j))
				return WA("copy the element");

	return { true, "Congratulation" };
}

std::pair<bool, std::string> moveTest()
{
	const int N = 200, M = 300;
	Matrix<int> a(N, M), b(M, N), bak(N, M);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			bak(i, j) = a(i, j) = rand();

	b = std::move(a);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			if (bak(i, j) != b(i, j))
				return WA("move");

	Matrix<testint> c(N, M);
	Matrix<int> judgecode(N, M);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			judgecode(i, j) = c(i, j).judge();
	Matrix<testint> d = std::move(c);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			if (d(i, j).judge() != judgecode(i, j))
				return WA("copy the element");

	return { true, "Congratulation" };
}

std::pair<bool, std::string> exceptionTest()
{
	const int N = 200, M = 300;
	Matrix<int> a(N, M), b(M, N), c(N, M);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			a(i, j) = rand(), b(j, i) = rand(), c(i, j) = rand();
	int cnt = 0;
	try
	{
		a + b;
	} catch (...) { cnt++; }

	try
	{
		a += b;
	} catch (...) { cnt++; }

	try
	{
		a -= b;
	} catch (...) { cnt++; }

	try
	{
		a - b;
	} catch (...) { cnt++; }

	try
	{
		a * c;
	} catch (...) { cnt++; }

	try
	{
		a(-1, -1);
	} catch (...) { cnt++; }

	try
	{
		a(N, M);
	} catch (...) { cnt++; }

	try
	{
		a.row(N);
	} catch (...) { cnt++; }

	try
	{
		a.row(-1);
	} catch (...) { cnt++; }

	try
	{
		a.column(M);
	} catch (...) { cnt++; }

	try
	{
		a.column(-1);
	} catch (...) { cnt++; }

	try
	{
		Matrix<int> t = {{ 0, 1 },
						 { 0 }};
	} catch (...) { cnt++; }

	if (cnt != 12) return WA("Caught " + toString(cnt) + " exceptions");
	return { true, "Congratulation" };
}

int main()
{

	std::pair<std::string, std::function<std::pair<bool, std::string>(void)>> testcases[] = {{ "resizeTest",    resizeTest },
																							 { "moveTest",      moveTest },
																							 { "exceptionTest", exceptionTest }};

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

