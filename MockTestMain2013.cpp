#include <iostream>
#include <cmath>
#include <string>
#include <complex>
//using namespace std!!!!!!
using namespace std;

int score(const string& a){
	int len=a.length();
	int score=0;
	for(int i=0;i<len;i++){
		//cout<<pow(-1,i)*(i+1)*(int(a[i]-'a')+1)<<endl;
		score+=pow(-1,i)*(i+1)*(int(a[i]-'a')+1);
		//cout<<score<<endl;
	}
	return score;
}

class quanternions{
public:
	double a,b,c,d;
	quanternions(double aa=0,double bb=0, double cc=0, double dd=0):a(aa),b(bb),c(cc),d(dd){}
	quanternions operator+ (quanternions& b1){
		return quanternions(a+b1.a,b+b1.b,c+b1.c,d+b1.d);
	}
	quanternions operator- (quanternions& b1){
		return quanternions(a-b1.a,b-b1.b,c-b1.c,d-b1.d);	
	}
	quanternions operator* (quanternions& b1){
		double aa=a*b1.a-b*b1.b-c*b1.c-d*b1.d;
		double bb=a*b1.b+b*b1.a+c*b1.d-d*b1.c;
		double cc=a*b1.c-b*b1.d+c*b1.a+d*b1.b;
		double dd=a*b1.d+b*b1.c-c*b1.b+d*b1.a;
		return quanternions(aa,bb,cc,dd);
	}

	quanternions inva(quanternions& astar){
		double lensquared=a*a+b*b+c*c+d*d;
		return quanternions(1/lensquared,0,0,0)*astar;
	}
	void show(){
		cout<<"("<<a<<","<<b<<","<<c<<","<<d<<")"<<endl;
	}

};


class quanint{
public:
	int a,b,c,d;
	quanint(int aa=0,int bb=0, int cc=0, int dd=0):a(aa),b(bb),c(cc),d(dd){}
	quanint operator+ (quanint& b1){
		return quanint(a+b1.a,b+b1.b,c+b1.c,d+b1.d);
	}
	quanint operator- (quanint& b1){
		return quanint(a-b1.a,b-b1.b,c-b1.c,d-b1.d);	
	}
	quanint operator* (quanint& b1){
		int aa=a*b1.a-b*b1.b-c*b1.c-d*b1.d;
		int bb=a*b1.b+b*b1.a+c*b1.d-d*b1.c;
		int cc=a*b1.c-b*b1.d+c*b1.a+d*b1.b;
		int dd=a*b1.d+b*b1.c-c*b1.b+d*b1.a;
		return quanint(aa,bb,cc,dd);
	}
	void show(){
		cout<<"("<<a<<","<<b<<","<<c<<","<<d<<")"<<endl;
	}
};


class quancomplex{
public:
	complex<double> a,b,c,d;
	quancomplex(complex<double> aa=complex<double>(0,0),complex<double> bb=complex<double>(0,0), complex<double> cc=complex<double>(0,0), complex<double> dd=complex<double>(0,0)):a(aa),b(bb),c(cc),d(dd){}
	quancomplex operator+ (quancomplex& b1){
		return quancomplex(a+b1.a,b+b1.b,c+b1.c,d+b1.d);
	}
	quancomplex operator- (quancomplex& b1){
		return quancomplex(a-b1.a,b-b1.b,c-b1.c,d-b1.d);	
	}
	quancomplex operator* (quancomplex& b1){
		complex<double> aa=a*b1.a-b*b1.b-c*b1.c-d*b1.d;
		complex<double> bb=a*b1.b+b*b1.a+c*b1.d-d*b1.c;
		complex<double> cc=a*b1.c-b*b1.d+c*b1.a+d*b1.b;
		complex<double> dd=a*b1.d+b*b1.c-c*b1.b+d*b1.a;
		return quancomplex(aa,bb,cc,dd);
	}
	void show(){
		cout<<"("<<a<<","<<b<<","<<c<<","<<d<<")"<<endl;
	}







};
int main(){
	string stra="zeoulous",strb="transporter",strc="lecturers";
	//cout<<'u'-'a'+1<<endl;
	cout<<score(stra)<<endl;
	cout<<score(strb)<<endl;
	cout<<score(strc)<<endl;

	//problem 2
	quanternions i(0,1,0,0),j(0,0,1,0),k(0,0,0,1),num1(1,0,0,0);
	quanternions a=quanternions(-1/4.,0,0,0)+quanternions(0,3,0,0)+k;
	quanternions b=quanternions(0,0,5,0)+quanternions(0,0,0,-2);
	(i*a*j*b*k).show();
	(a*a-b*b).show();

	quanternions c=a+b,cstar;
	(c+i*c*i+j*c*j+k*c*k).show();
	cstar=quanternions(-0.5,0,0,0)*(c+i*c*i+j*c*j+k*c*k);
	cstar.show();


	quanternions astar(quanternions(-0.5,0,0,0)*(a+i*a*i+j*a*j+k*a*k));
	a.inva(astar).show();

	quanternions bstar(quanternions(-0.5,0,0,0)*(b+i*b*i+j*b*j+k*b*k));
	((b.inva(bstar))*a).show();
	(a*(b.inva(bstar))).show();	



	//problem 3
	quanint a1(123456789,12345,54321,987654321),b1(999,111,222,333);
	(a1*b1).show();
	(b1*a1).show();
	(a1*a1-b1*b1).show();



	//problem 3-2
	quancomplex ca(complex<double>(1,1),complex<double>(-5,0),complex<double>(2,-3),complex<double>(0,1)),cb(complex<double>(0,0),complex<double>(0,5),complex<double>(1,-1),complex<double>(8,9));
	(ca*cb).show();
	(cb*ca).show();
	(ca*ca-cb*cb).show();
	/*complex<double> z1(2,-3), z2(1,-1), z3(-1,1), z4(5,0);
	cout<<z1*z2<<endl;*/
	return 0;





}