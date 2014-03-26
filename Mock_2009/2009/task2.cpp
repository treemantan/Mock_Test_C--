#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <numeric>
//#include <iterator>

using namespace std;







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
      res+=(*this)[i]*pow(y,i);
    }
    return res;
  }
};


int main(){
  Laurent_polynomial<double> p(2, 1.0); // N = 2, a_n = 1.0, n = -N,...,N.
  Laurent_polynomial<double> q(5, -1.5), s;
  double x(2.1), y(-1.25);
  cout << "p(y) = " << p.value(y) << endl; // value of polynomial p at y
  s = p + q;
  for (int i = -s.getN(); i <= s.getN(); i++)
    cout << "s[" << i << "] = " << s[i] << endl; // print coefficients a_n of s
  cout << "s(x) = " << s.value(x) << endl;







}
