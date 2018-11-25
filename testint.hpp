#ifndef INC_2017OOP1_TESTINT_HPP
#define INC_2017OOP1_TESTINT_HPP
#include <unistd.h>
#include <cstdlib>

class testint
{
private:
	int data;
	int flag = rand();

public:
	testint(int _data = 0) : data(_data) { }

	testint(const testint &o)
	{
		data = o.data;
	}

	testint &operator=(const testint &o)
	{
		data = o.data;
		return *this;
	}

	testint &operator+=(const testint &o)
	{
		data += o.data;
		return *this;
	}

	friend testint operator+(const testint &a, const testint &b)
	{
		testint ans;
		ans += a;
		return ans += b;
	}

	testint &operator-=(const testint &o)
	{
		data -= o.data;
		return *this;
	}

	friend testint operator-(const testint &a, const testint &b)
	{
		testint ans;
		ans += a;
		return ans -= b;
	}

	testint &operator*=(const testint &o)
	{
		data *= o.data;
		return *this;
	}

	friend testint operator*(const testint &a, const testint &b)
	{
		testint ans;
		ans += a;
		return ans *= b;
	}

	testint operator-()
	{
		testint ans;
		ans.data = -(this->data);
		return ans;
	}

	bool operator==(const testint &a)
	{
		return a.data == data;
	}

	bool operator!=(const testint &a)
	{
		return !((*this) == a);
	}

	int judge()
	{
		return flag;
	}
};

#endif //INC_2017OOP1_TESTINT_HPP
