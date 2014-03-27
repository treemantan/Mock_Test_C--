#include <iostream>
#include <cmath>
#include <map>
#include <iterator>
#include <string>
#include <vector>
using namespace std;


double f(double x){ return exp(x*x)+1./(1+x);}
double f2(double x){return f(x)*f(x);}


template <typename T>
class gen_charfn{
  T alpha,a,b;
public:
  gen_charfn(T al=T(0),T aa=T(0), T bb=T(0)):alpha(al),a(aa),b(bb){}
  T evaluation(const T x)const{
    if(x>=a||x<b) return alpha;
    else return 0;
  }
  T integration(){
    return (b-a)*alpha;
  }
  gen_charfn operator* (const gen_charfn &rhs)const{
    if(a<=rhs.a && b>=rhs.b) return gen_charfn(alpha*rhs.alpha,rhs.a,rhs.b);
    else if(a<=rhs.a && b<=rhs.b) return gen_charfn(alpha*rhs.alpha,rhs.a,b);
    else if(a>=rhs.a && b<=rhs.b) return gen_charfn(alpha*rhs.alpha,a,b);
    else if(a>=rhs.a && b>=rhs.b) return gen_charfn(alpha*rhs.alpha,a,rhs.b);
    else return gen_charfn(0,0,0);
  }
  gen_charfn operator* (const T beta)const{
    return gen_charfn(alpha*beta,a,b);
  }
};

template <typename T>
class step_function{
  vector<gen_charfn<T> > s;
public:
  //Default constructor to avoid no input parameter
  step_function(){}
  //Const is needed!!!
  step_function(const vector<gen_charfn<T> > &ss):s(ss){}
  T operator() (const T x){
    T res(0);
    for(unsigned int i=0;i<s.size();i++){
      res+=s[i].evaluation(x);
    }
    return res;
  }
  T intR(){
    T res(0);
    for(unsigned int i=0;i<s.size();i++){
      res+=s[i].integration();
    }
    return res;
  }
  step_function operator+ (const step_function &rhs) const{
    //For loop to add
    step_function res(s);
    for(unsigned int i=0;i<rhs.s.size();i++){
      res.push_back(rhs.s[i]);
    }
    //Use insert function
    /*step_function res;
    res.s.reserve(s.size()+rhs.s.size());
    res.s.insert(res.s.end(),s.begin(),s.end());
    res.s.insert(res.s.end(),rhs.s.begin(),rhs.s.end());*/
    return res;
  }
  void push_back(const gen_charfn<T> &fn){
    s.push_back(fn);
  }
  
  //Overload the multiplication
  step_function operator* (const step_function &rhs)const{
    step_function res;
    for(unsigned int i=0;i<s.size();i++){
      for(unsigned int j=0;j<rhs.s.size();j++){
	res.push_back(s[i]*rhs.s[j]);
      }
    }
    return res;
  }

  step_function operator* (const T beta)const{
    step_function res;
    for(unsigned int i=0;i<s.size();i++)
      res.push_back(s[i]*beta);
    return res;
  }

  step_function operator* (const gen_charfn<T> &rhs)const{
    step_function res;
    for(int i=0;i<s.size();i++){
      res.push_back(s[i]*rhs);
    }
    return res;
  }

};

void uniform_partition(double a,double b, int n, vector<double> &partuni){
  for(int i=0;i<=n;i++){
    partuni.push_back(a+i*(b-a)/n);
  }
}

void logarithmic_partition(double a,double b, int n, vector<double> &partlog){
  for(int i=0;i<=n;i++){
    partlog.push_back(log(exp(a)+i*(exp(b)-exp(a))/n));
  }
}


template <typename T>
void interpolate(T (*f)(T),vector<T> partition,step_function<T> &s){
  for(unsigned int i=0;i<partition.size()-1;i++){
    double a,b;
    a=partition[i];
    b=partition[i+1];
    s.push_back(gen_charfn<T>(f(a),a,b));
  }
}




int main() {
  int n = 100;
  double a = -0.5; double b = 0.5;
  vector<double> partuni, partlog;
  step_function<double> s, t, u, v, w;
  uniform_partition(a, b, n, partuni);
  interpolate(f, partuni, s);
  cout << "Integral with uniform = " << s.intR() << endl;
  logarithmic_partition(a, b, n, partlog);
  interpolate(f, partlog, t);
  cout << "Integral with logarithmic = " << t.intR() << endl;
  u = s + t;
  cout << "u(0.1) = " << u(0.1) << endl;
  cout << "Integral sum = " << u.intR() << endl;
  v = s * t;
  cout << "Integral of s * t = " << v.intR() << endl;
  interpolate(f2, partlog, w);
  cout << "Integral of f^2 with logarithmic = " << w.intR() << endl;
  return 0;
}


