#include <iostream>
using namespace std;
int afunction(
		int val,		// int a = 100		Call by Value 
		const int &cr,	// int b = 200		Call by Reference 
		int *ptr,		// int b = 200		Call by Pointer 
		int &ret		// int c = 300		Call by Referencef
		)
{
	val += cr;	// val = val + cr = 100 + 200 = 300, but caller's a is not changed. a = 100
//  cr += val;	// not allowed because it is constant
	*ptr += 10;	// b += 10 = 200 + 10 = 210, caller's b is changed
	ret += 10;	// ret = ret + 10 = 300 + 10 = 310, caller's c is changed
	return val; // return 300
}

int main()
{
	int a = 100, b = 200, c = 300;
	int ret;
	ret = afunction(a, b, &b, c);

	cout << "The value of a = " << a << endl;
	cout << "The value of b = " << b << endl;
	cout << "The value of c = " << c << endl;
	cout << "The return value is = " << ret << endl;
	
	return 0;
}
