#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <numeric>
//#include <iterator>

using namespace std;


class complex{
 double re,im;
public:
  complex(double ree=0,double imm=0):re(ree),im(imm){}
  double real()const{return re;}
  double image()const{return im;}
  complex operator+ (const complex& rhs)const{
    return complex(re+rhs.real(),im+rhs.image());
  }
  complex operator* (const complex& rhs)const{
    return complex(re*rhs.real()-im*rhs.image(),re*rhs.image()+im*rhs.real());
  }
  complex operator* (const double &rhs)const{
    return complex(re*rhs,im*rhs);
  }
  complex conj()const{
    return complex(re,-im);
  }
  double norm()const{
    return sqrt(re*re+im*im);
  }
  complex operator- (const complex &rhs)const{
    return complex(re-rhs.real(),im-rhs.image());
  }
  complex operator/ (const complex  &rhs)const{
    return *this*rhs.conj()*(1./rhs.norm()*rhs.norm());
  }
  complex& operator+= (const complex &rhs){
    *this=*this+rhs;
    return *this;
  }
  complex operator- (){
    return complex(-re,-im);
  }
  void print(ostream& os)const{
    os<<"("<<re<<","<<im<<")"<<endl;
  }
};

complex operator*(const double lhs,const complex & rhs){
  return rhs*lhs;
}

template <typename T>
T my_power(const T &z, int n){
  T res(1);
  if(n>0){
    for(int i=0;i<n;i++){
      res=res*z;
    }
  }else if(n<0){
    for(int i=0;i<abs(n);i++)
      res=res/z;
  }
  return res;
}

ostream& operator<<(ostream& os,const complex &c){
  c.print(os);
  return os;
}


template <typename T>
class Laurent_polynomial{
  int N;
  vector<T> lv;
public:
  Laurent_polynomial(int nn=0,T an=0):N(nn),lv(vector<T>(2*nn+1,an)){}
  T& operator[](int i){return lv[i+N];}
  int getN()const{return N;}
  Laurent_polynomial operator+ (Laurent_polynomial &rhs){
    Laurent_polynomial res;
    Laurent_polynomial low;
    if(N<rhs.getN()){res=rhs;low=*this;}
    else{res=*this;low=rhs;}
    for(int i=-low.getN();i<=low.getN();i++){res[i]+=low[i];}
    return res;
  }
  T value(T y){
    T res(0);
    for(int i=-N;i<=N;i++){
      res+=(*this)[i]*my_power<T>(y,i);
    }
    return res;
  }
};


int main(){
  complex f(1,1), g(0,-1);
  Laurent_polynomial<complex> p(2, f);
  Laurent_polynomial<complex> q(5, g), s;
  complex x(1,2), y(0,-1);
  cout << "p(y) = " << p.value(y) << endl;
  s = p + q;
  for (int i = -s.getN(); i <= s.getN(); i++)
    cout << "s[" << i << "] = " << s[i] << endl;
  cout << "s(x) = " << s.value(x) << endl;










}
