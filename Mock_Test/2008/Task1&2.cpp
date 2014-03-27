#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;


//P1.bubble sort
void swap(double &a, double &b){
	double temp=b;
	b=a;
	a=temp;
}
int bubble(vector<double>& v){
	int countswap=0;
	for(unsigned int i=0;i<v.size()-1;i++){
		for(int j=0;j<v.size()-1-i;j++){
			if(v[j]>v[j+1]){
				swap(v[j],v[j+1]);
				countswap++;
			}
		}	
	}
	return countswap;
}

//P2. Boxmuller
double boxmuller(){
	const double pi=4*atan(1.0);
	double u1=rand()/static_cast<double>(RAND_MAX);
	double u2=rand()/static_cast<double>(RAND_MAX);

	while(u2<1e-15){
		u2=rand()/static_cast<double>(RAND_MAX);
	}

	double x=sqrt(-2*log(u2))*cos(2*pi*u1);
	double y=sqrt(-2*log(u2))*sin(2*pi*u1);
	return x;
}

//P2. Monte Carlo
class RV{
public:
	virtual double generate()=0;
	virtual double pdf(const double&)=0;
	virtual double cdf(const double&)=0;
	virtual ~RV(){}
};

class uniform: public RV{
	double a,b;
public:
	uniform(double aa=0,double bb=1):a(aa),b(bb){}
	double generate(){
		return a+(b-a)*(rand()/static_cast<double>(RAND_MAX));
	}
	double pdf(const double& x){
		if(x<a)
			return 0;
		else if(x>b)
			return 0;
		else
			return (double)1/(b-a);
	}
	double cdf(const double& x){
		if(x<a) return 0;
		else if(x>=b)
			return 1;
		else{
			return (x-a)/(b-a);
		}
	}

};

class normal: public RV{
	double mu,sigma;
public:
	normal(double mmu=0,double vol=1):mu(mmu),sigma(vol){}
	double generate(){
		return mu+sigma*boxmuller();
	}
	double pdf(const double& x){
		const double pi=4*atan(1.0);
		return 1/(sqrt(2*pi)*sigma)*exp(-(x-mu)*(x-mu)/(2*sigma*sigma));
	}
	double cdf(const double& x){
		return 0;
	}
};

double mtuni(double a,double b,int N,vector<double>& stats){
	double res=0;
	uniform rv(a,b);
	vector<double> monte;
	for(int i=0;i<N;i++){
		double temp=(b-a)*sin(rv.generate());
		res+=temp/N;
		monte.push_back(temp);
	}
	double var=0;
	for(int i=0;i<N;i++){
		var+=(monte[i]-res)*(monte[i]-res)/N;
	}
	stats.push_back(res);
	stats.push_back(var);
	return res;
}

double mtnormal(double mu,double sigma,int N,vector<double>& stats){
	double res=0;
	normal rv(mu,sigma);
	vector<double> monte;
	for(int i=0;i<N;i++){
		double num=rv.generate();
		double temp=sin(num)/rv.pdf(num)*(num<4*atan(1.0)&&num>0);
		res+=temp/N;
		monte.push_back(temp);
	}
	double var=0;
	for(int i=0;i<N;i++){
		var+=(monte[i]-res)*(monte[i]-res)/N;
	}
	stats.push_back(res);
	stats.push_back(var);
	return res;
}

int main(){
	//P1
	vector<double> list;
	ifstream fin("data.txt");
	double num;
	if(!fin.is_open()){ cout<<"No such file"<<endl; return -1;}
	while(fin>>num){
		list.push_back(num);
	}
	fin.close();
	cout<<bubble(list)<<endl;
	//copy(list.begin(),list.end(),ostream_iterator<double>(cout," "));
	//output the result into a file called sorted.txt
	ofstream fout("sorted.txt");
	double outnum;
	if(!fout.is_open()){cout<<"No such file"<<endl; return -1;}
	for(unsigned int i=0;i<list.size();i++){
		fout<<list[i]<<" ";
	}
	fout<<endl;
	fout.close();
	//P2
	const double pi=4*atan(1.0);
	vector<double> statsuni;
	cout<<"U[0,Pi]:"<<endl;
	mtuni(0,pi,1000,statsuni);
	cout<<statsuni[0]<<","<<statsuni[1]<<endl;
	vector<double> statsnorm;
	cout<<"N(0,1):"<<endl;
	mtnormal(0,1,1000,statsnorm);
	cout<<statsnorm[0]<<","<<statsnorm[1]<<endl;
	statsnorm.clear();
	cout<<"N(Pi/2,1):"<<endl;
	mtnormal(pi/2,1,1000,statsnorm);
	cout<<statsnorm[0]<<","<<statsnorm[1]<<endl;
}
