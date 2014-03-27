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
  fraction(int num=0,int dd=1):denomintor(dd),numerator(num){
    if(gcd(num,dd)!=0)
      {numerator=num/gcd(num,dd);
	denomintor=dd/gcd(num,dd);
      }
  }
  fraction operator/ (const fraction & rhs)const{
    return fraction(numerator*rhs.denomintor,denomintor*rhs.numerator);
  }
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
  fraction operator* (const int a)const {
    return fraction(numerator*a,denomintor);
  }
  void print(ostream& os)const{
    os<<numerator<<"/"<<denomintor;
  }
  operator double()const{
    return double(numerator)/(denomintor);
  }
};

fraction operator* (const int a, const fraction &f){
  return f*a;
}

ostream& operator<<(ostream& os,const fraction &z){
  z.print(os);
  return os;
}
int main(){
  int a=4, b=3;
  fraction f(1,123), g(1,321),h(1,3), res;
  cout<<f<<endl<<g<<endl;
  cout<< (double)(f-h) <<endl;
  res= a*f -g*b;
  res= -res+ f*h;
  cout<< res << endl;
  f+=g/h;
  cout << f <<endl;


}
