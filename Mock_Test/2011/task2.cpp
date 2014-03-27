#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <map>
#include <iterator>
using namespace std;


//This is not the best or clear way to do it. Alternative way is to redefine a mathvector class and its member function and it is more easily to be extended.
double dot(vector<double> &a, vector<double> &b){
  double res=0;
  for(unsigned int i=0;i<a.size();i++){
    res+=a[i]*b[i];
  }
  return res;
}

vector<double> product(vector<double> &v,double r){
  vector<double> res;
  for(int i=0;i<v.size();i++){
    res.push_back(v[i]/r);
  }
  return res;
}
//Const needed here if I do not create templocal to store the product of q[j] and 1./dot(ma[i],q[j])
void myminus(vector<double> &v, const vector<double> & q){
  for(int i=0;i<v.size();i++){
    v[i]=v[i]-q[i];
  }
}

void schimit(vector<vector<double> > &q,vector<vector<double> > &ma){
  vector<vector<double> > v;
  v.push_back(ma[0]);
  q.push_back(product(v[0],sqrt(dot(v[0],v[0]))));
  for(int i=1;i<ma.size();i++){
    vector<double> temp;
    temp=ma[i];
    for(int j=0;j<i;j++){
      //Remark:错误： 用类型为‘std::vector<double>’的右值初始化类型为‘std::vector<double>&’的非常量引用无效
      // vector<double> templocal;
      //templocal=product(q[j],1./dot(ma[i],q[j]));
      myminus(temp,product(q[j],1./dot(ma[i],q[j])));
      //myminus(temp,templocal);
      // templocal.clear();
    }
    v.push_back(temp);
    q.push_back(product(temp,sqrt(dot(temp,temp))));
    temp.clear();
  }


}

int main(){
  vector<vector<double> > ma;
  vector<vector<double> > q;
  double a1[]={1,2,0};
  double a2[]={2,2,0};
  vector<double> ma1(a1,a1+3),ma2(a2,a2+3);
  ma.push_back(ma1);
  ma.push_back(ma2);
  schimit(q,ma);
  copy(q[0].begin(),q[0].end(),ostream_iterator<double>(cout," "));
  cout<<endl;
  copy(q[1].begin(),q[1].end(),ostream_iterator<double>(cout," "));
  cout<<endl;



}
