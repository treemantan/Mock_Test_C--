#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <complex>
#include <ctime>
using namespace std;

template <typename T>
class point{
	complex<T> p;
public:
	point(T x=T(0), T y=T(0)):p(complex<double>(x,y)){}
	point(complex<T>& pp=complex<T>(0)):p(pp){}
	T get_x()const{return p.real();}
	T get_y()const{return p.imag();}
	void print(ostream& os){
		os<<p;
	}
};
template <typename T>
ostream& operator<<(ostream& os, point<T>& a){
	a.print(os);
	return os;
}

//P2. Boxmuller
template <typename T>
point<T> boxmuller(){
	const double pi=4*atan(1.0);
	double u1=rand()/static_cast<T>(RAND_MAX);
	double u2=rand()/static_cast<T>(RAND_MAX);
	
	//Avoid u2 close to zero
	while(u2<1e-15){
		u1=rand()/static_cast<T>(RAND_MAX);
		u2=rand()/static_cast<T>(RAND_MAX);
	}

	double x=sqrt(-2*log(u2))*cos(2*pi*u1);
	double y=sqrt(-2*log(u2))*sin(2*pi*u1);
	return point<T>(complex<T>(x,y));
}

template <typename T>
class RV{
public:
	virtual point<T> generate()=0;
	virtual T pdf(const point<T> &x)=0;
	virtual T cdf(const point<T> &x)=0;
};


template <typename T>
class uni2d: public RV<T>{
	point<T> a,b;
public:
	uni2d(point<T>&aa=point<T>(0),point<T>&bb=point<T>(0)):a(aa),b(bb){}
	point<T> generate(){
		double x=a.get_x()+(a.get_y()-a.get_x())*rand()/static_cast<double>(RAND_MAX);
		double y=b.get_x()+(b.get_y()-b.get_x())*rand()/static_cast<double>(RAND_MAX);;
		return point<T>(x,y);
	}
	T pdf1d(T low,T high,const T &x){
		T res;
		if(x<low) res=0;
		else if(x>high) res=0;
		else res=(T)1/(high-low);

		return res;
	}

	T pdf(const point<T> &x){
		 T x1=x.get_x(),y1=x.get_y();
		 T res1,res2;
		 
		 if(x1<a.get_x()) res1=0;
		 else if(x1>a.get_y()) res1=0;
		 else res1=(T)1/(a.get_y()-a.get_x());

		 if(y1<b.get_x()) res2=0;
		 else if(y1>b.get_y()) res2=0;
		 else res2=(T)1/(b.get_y()-b.get_x());

		 return res1*res2;
	}

	T cdf(const point<T> &x){
		return T(0);
	}
};

template <typename T>
T f1(T &x, T &y){ return exp(x*x+x*y)*y;}
template <typename T,typename F>
T mtuni2d(point<T> &a,point<T> &b,int N,F h){
	uni2d<T> rv(a,b);
	T res(0);
	for(int i=0;i<N;i++){
		point<T> value2d=rv.generate();
		T x=value2d.get_x(),y=value2d.get_y();
		res+=h(x,y)/rv.pdf(value2d)/N;
	}
	return res;
}

int main(){
	point<double> p1(1,2);
	/*srand(time(NULL));
	cout<<p1<<endl<<boxmuller<double>()<<endl;
	double xmean=0;
	double ymean=0;
	long long N=100000;
	for(int i=0;i<N;i++){
		xmean+=boxmuller<double>().get_x()/N;
		ymean+=boxmuller<double>().get_y()/N;
	}
	cout<<xmean<<","<<ymean<<endl;*/
	point<double> a(0.25,1),b(-3,3);
	cout<<mtuni2d<double>(a,b,1000,f1<double>);






}