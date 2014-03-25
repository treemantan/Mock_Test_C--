#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <complex>
using namespace std;

int mymodfact(int n,int m){
	int res=1;
	for(int i=1;i<=n;i++){
		res*=i%m;
		res=res%m;
	}
	return res;
}

int mymodpow(int a,int b,int m){
	int res=1;
	for(int i=0;i<b;i++){
		res*=a%m;
		res=res%m;
	}
	return res;
}

unsigned long collatz(unsigned long n){
	unsigned long count=0;
	while(n!=1){
		if(n%2==0)
			n/=2;
		else
			n=3*n+1;
		count++;
	}
	return count;
}

unsigned long Mc(unsigned long l,unsigned long r){
	unsigned long max=0;
	for(unsigned long i=l;i<=r;i++){
		unsigned long temp=collatz(i);
		if(max<temp)
			max=temp;
	}
	return max;
}

//Sn
unsigned long Sn(unsigned long l,unsigned long r,unsigned long n){
	unsigned long sum=0,count=0,i=l;
	while(i<=r){
		unsigned long temp=collatz(i);
		if(temp==n){
			sum+=i;
		}
		i++;
		//cout<<i<<endl;
	}
	return sum;
}

template <typename T>
class Laurent_polynomial{
	vector<T> lv;
	int N;
public:
	Laurent_polynomial(int nn=0,T an=T(0)):N(nn),lv(vector<T>(nn*2+1,an)){}
	Laurent_polynomial(int nn,vector<T> v):N(nn){
		for(int i=0;i<v.size();i++){
			lv.push_back(v[i]);	
		}
	}
	vector<T>& get_v(){return lv;}
	T& operator[](int j){return lv[N+j];}
	T value(T y){
		T res=0;
		for(int i=-N;i<=N;i++){
			res+=lv[N+i]*pow(y,i);
		}
		return res;
	}
	int getN()const {return N;}
	Laurent_polynomial<T> operator+(Laurent_polynomial<T>& rhs){
		vector<T> res;
		vector<T> p;	
		if(N<rhs.N){ res=rhs.lv; p=lv;}
		else{res=lv;p=rhs.lv;}
		//Must define two limits to avoid some strange errors
		int rangel=(p.size()-1)/2;
		int rangeh=(res.size()-1)/2;
		for(int i=-rangel;i<=rangel;i++){
			res[rangeh+i]+=p[rangel+i];
		}
		return Laurent_polynomial((res.size()-1)/2,res);
	}
};



int main(){
	//P1
	cout<<mymodfact(80,997)<<endl;
	cout<<mymodpow(7,128,pow(10,6))<<endl;
	int sumremain=0;
	for(int i=1;i<=1000;i++){
		sumremain+=mymodpow(i,i,877);
		sumremain=sumremain%877;
	}
	cout<<sumremain<<endl;

	//P2:Collatz conjecture
	cout<<collatz(201203)<<endl;
	unsigned long max=0;
	max=Mc(10000,100000);
	cout<<max<<endl;
	cout<<Sn(1,1000000,256)<<endl;
	//cout<<collatz(113383)<<endl;
	//cout<<Sn(1,1000000,256)<<endl;
	
	//P3:Part I
	Laurent_polynomial<double> p(2,1.0);
	Laurent_polynomial<double> q(5,-1.5),s;
	double x(2.1), y(-1.25);
	cout << "p(y) =" << p.value(y)<<endl;
	s=p+q;
	for(int i=-s.getN();i<=s.getN();i++){
		cout<<"s["<< i << "]=" << s[i] <<endl;
	}
	cout<< "s(x)=" <<s.value(x) <<endl;


	//PartII
	complex<double> f(1,1), g(0,-1);
	Laurent_polynomial<complex<double>> u(2,f);
	Laurent_polynomial<complex<double>>	v(5,g),t;
	complex<double> z(1,2), w(0,-1);
	cout<< "u(w) =" <<u.value(w)<<endl;
	t = u + v;
	for(int i= -t.getN();i<=t.getN();i++){
		cout<<"t["<<i<<"]="<<t[i]<<endl;
	
	}
	cout<<"t(z)="<<t.value(z)<<endl;

}
