#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>

using namespace std;




//Copy from Task2.cpp
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
    if(denomintor!=1)
      os<<numerator<<"/"<<denomintor;
    else
      os<<numerator;
  }
  operator double()const{
    return double(numerator)/(denomintor);
  }
};

fraction mypow(const fraction &f,int n){
  fraction res(1,1);
  for(int i=0;i<n;i++)
    res=res*f;
  return res;
}
fraction operator* (const int a, const fraction &f){
  return f*a;
}

ostream& operator<<(ostream& os,const fraction &z){
  z.print(os);
  return os;
}



template <typename T>
T gibonacci(int n, const T &F0, const T &F1)
{
  if(n==0)
    return F0;
  T a=F0,b=F1;
  while(n-- > 1){
   T t=b;
    b+=a;
    a=t;
  }
  return b;
}

template <typename T>
int glimit_phi(double epsilon, const T &F0, const T &F1)
{
  int i=1;
  double phi=(1+sqrt(5))/2;
  while(abs((double)gibonacci(i,F0,F1)/(double)gibonacci(i-1,F0,F1)-phi)>epsilon){
    i++;
  }
  return i;
}

template <typename T1, typename T2>
T2 r_N(const T2 &x, int N, const T1 &F0, const T1 &F1)
{
  T2 res(0);
  for(int i=0;i<=N;i++){
    res+=gibonacci(i,F0,F1)*mypow(x,i);
    //cout<<i<<":"<<gibonacci(i,F0,F1)<<" "<<mypow(x,i)<<" "<<gibonacci(i,F0,F1)*mypow(x,i)<<endl;
  }
  return res;
}

template <typename T1, typename T2>
int limit_r(const T2 &x, double epsilon, const T1 &F0, const T1 &F1){
  int ind=1;
  while(abs(r_N(x,ind,F0,F1)-r_N(x,ind-1,F0,F1))>epsilon){
    ind++;
  }
  return ind;
}



int main(){
  // int a=4, b=3;
  // fraction f(1,123), g(1,321),h(1,3), res;
  // cout<<f<<endl<<g<<endl;
  // cout<< (double)(f-h) <<endl;
  // res= a*f -g*b;
  // res= -res+ f*h;
  // cout<< res << endl;
  // f+=g/h;
  // cout << f <<endl;
  
  //Problem 3: Test setting G0=1/2, G1=1/3;
 
  fraction G0(1,2),G1(1,3);
  cout<<"********************Setting****************"<<endl;
  cout<<"G0:"<<G0<<"\t"<<"G1:"<<G1<<endl;
  cout<<"********************Setting****************"<<endl;
  cout<<"G20:"<<gibonacci(20,G0,G1)<<endl;
  
  double epsilon=1e-6;
  int resind=glimit_phi(epsilon,G0,G1);
  cout<<"n_e, for epsilon=10-6 and G_{n_e}:"<< resind <<","<<gibonacci(resind,G0,G1)<<endl;
  
  fraction x(3,8);
  cout<< "r_5(3/8):"<<r_N(x,2,G0,G1)<<endl;
 
  fraction x2(1,4);
  //cout<<glimit_phi(0.003,G0,G1)<<endl;
  cout<<"epsilon=0.003,r_N_{e}(1/4):"<<limit_r(x2,0.003,G0,G1)<<endl;
  //Be careful, when N is greater than 7, int is not sufficient for r_N;
  //cout<<r_N(x2,6,G0,G1)<<endl;
  cout<<"gibnonacci<short>(90,0,1):"<<gibonacci<short>(90,0,1)<<endl;
  cout<<"gibnonacci<unsigned int>(90,0,1):"<<gibonacci<unsigned int>(90,0,1)<<endl;
  cout<<"gibnonacci<unsigned long>(90,0,1):"<<gibonacci<unsigned long>(90,0,1)<<endl;
  cout<<"gibnonacci<float>(90,0,1):"<<gibonacci<float>(90,0,1)<<endl;


  return 0;
} 
