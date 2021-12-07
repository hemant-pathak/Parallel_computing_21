//N-queen problem

#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

vector<vector<int> > vec;

bool IsSafe(int x, int y,int n){
	#pragma omp for
	for (int row=0;row<x;row++){
		if(vec[row][y]==1){
			return false;
		}
	}
	int row=x,col=y;
	#pragma omp for
	while(row>=0 && col>=0){
		if(vec[row][col]==1){
			return false;
		}
		row--;
		col--;
	}
	
	row=x;col=y;
	#pragma omp for
	while(row>=0 && col<n){
		if(vec[row][col]==1){
			return false;
		}
		row--;
		col++;
	}
	return true;
}

bool nQueen(int x, int n){
	if (x>=n){
		return true;
	}
	for (int col=0; col<n;col++){
		if(IsSafe(x,col,n)){
			vec[x][col]=1;

			if(nQueen(x+1,n)){
				return true;
			}
			vec[x][col]=0; //backtracking
		}
	}
	return false;
}

int main(){
	int num;
	cin>>num;


	//data input;
	for (int i=0;i<num;i++){
		vector<int> temp;
		for (int j=0;j<num;j++){
			
			temp.push_back(0);
		}
		vec.push_back(temp);
		temp.clear();
	}
	//data fill and display
	if(nQueen(0,num)){
		for (int i=0;i<num;i++){
			for (int j=0;j<num;j++){
				cout<<vec[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
