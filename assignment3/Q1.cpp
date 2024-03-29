//Stencil computations

#include<bits/stdc++.h>
#include "omp.h"
using namespace std;

void display(vector<vector<int> > v){
	int n=v.size();
	for (int i=1;i<n-1;i++){
		for (int j=1;j<n-1;j++){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
}

void iteration(vector<vector<int> > &v){
	int n=v.size();
	#pragma omp for
	for (int i=1;i<n-1;i++){
		for (int j=1;j<n-1;j++){
			int l=v[i][j-1],r=v[i][j+1],u=v[i-1][j],d=v[i+1][j];
			int sum1=l+r+u+d+v[i][j];
			int t1=max(v[i][j],sum1/5);
			v[i][j]=t1;
		}
	}
}

int main(){
	int num;
	cin>>num;
	vector<vector<int> > vec;
	for (int i=0;i<num+2;i++){
		vector<int> temp;
		for (int j=0;j<num+2;j++){
			int random = rand() % 10;
			//int t0; cin>>t0;
			if(i==0 || j==0 || i==num+1 || j==num+1){   //used to avoid segmentation fault
				temp.push_back(0);
			}else
				temp.push_back(random);
		}
		vec.push_back(temp);
		temp.clear();
	}
	display(vec);
	for (int i=0;i<300000;i++){
		iteration(vec);
	}
	cout<<endl;
	display(vec);
	
	return 0;
}
