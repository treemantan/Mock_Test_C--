#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>

using namespace std;

int fibonacci(int n,int F0, int F1){
	if(n==0)
		return F0;
	else if(n==1)
		return F1;
	else
		return fibonacci(n-1,F0,F1)+fibonacci(n-2,F0,F1);
}


int flimit_phi(double epsilon, int F0, int F1){
	int ind=1;
	while(abs((double)fibonacci(ind,F0,F1)/fibonacci(ind-1,F0,F1)-(1+sqrt(5))/2)>=epsilon){
		ind++;	
	}
	return ind;
}


double s_N(double x, int N, int F0, int F1){
	double res=0;
	for(int i=0;i<N;i++){
		res+=fibonacci(i,F0,F1)*pow(x,i);
	}
	return res;
}

int limit_s(double x, double epsilon,int F0, int F1){
	int ind=1;
	while(abs(s_N(x,ind,F0,F1)-s_N(x,ind-1,F0,F1))>=epsilon){
		ind++;
	}
	return ind;
}




int main(){








}