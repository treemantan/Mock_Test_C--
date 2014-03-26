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

complex my_power(const complex &z, int n){
  complex res(complex(1,0));
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



int main(){
  double x = 4.1, y = -3.5;
  complex z(1,-1), v(0,1), w(-2,3), res;
  cout << z - w << endl;
  res = x * z - v * y;
  res = - res + z * w;
  cout << res << endl;
  z += v / w;
  cout << z << endl;
  cout << my_power(w, 3) << endl;
  cout << my_power(v, -2) << endl;







}
