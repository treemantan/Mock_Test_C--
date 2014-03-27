#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>

using namespace std;



int gcd(int a, int b){
	return (b==0?a:gcd(b,a%b));
}

class fraction{
	int denomintor,numerator;
public:
	fraction(int dd,int num):denomintor(dd/gcd(dd,num)),numerator(num/gcd(dd,num)){}
	fraction operator+ (const fraction & rhs)const{
		return fraction(numerator*rhs.denomintor+rhs.numerator*denomintor,denomintor*rhs.denomintor);
	}
	fraction operator- (const fraction & rhs)const{
		return fraction(numerator*rhs.denomintor-rhs.numerator*denomintor,denomintor*rhs.denomintor);
	}
	fraction operator* (const fraction & rhs)const{
		return fraction(numerator*rhs.numerator,denomintor*rhs.denomintor);
	}
	fraction operator- ()const{
		return fraction(-numerator,denomintor);
	}
	fraction& operator+= (const fraction &rhs){
		*this=*this+rhs;
		return *this;
	}


};