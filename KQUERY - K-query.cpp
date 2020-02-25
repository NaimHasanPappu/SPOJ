#include<bits/stdc++.h>
 
using namespace std;
 
#define lli long long int
 
#define ulli unsigned long long int
 
#define Pi 3.14159265358979323846264338327950288419716939937510
 
vector < vector <int> > Tree;
 
vector <int> Array;
 
void Build(int n, int l, int r){
	
	if(l == r){
		
		Tree[n].push_back(Array[l]);
		
		return;
	}
	
	else{
		
		int m = (l+r)/2;
		
		Build(2*n,l,m);
		
		Build(2*n+1,m+1,r);
		
		for(auto &i : Tree[2*n]){
			
			Tree[n].push_back(i);
		}
		
		for(auto &i : Tree[2*n+1]){
			
			Tree[n].push_back(i);
		}
		
		sort(Tree[n].begin(),Tree[n].end());
		
		return;
	}
}
 
int query(int n,int k){
	
	int l = 0;
	
	int r = Tree[n].size()-1;
	
	int result = 0;
	
	while(l <= r){
		
		int m = (l+r)/2;
		
		if(k < Tree[n][m]){
			
			result += (r-m+1);
			
			r = m-1;
		}
		
		else{
			
			l = m+1;
		}
	}
	
	return result;
}
 
int Query(int n, int l, int r, int i, int j, int k){
	
	if(l>r or r<i or l>j){
		
		return 0;
	}
	
	else if(i<=l and r<=j){
		
		return query(n,k);
	}
	
	else{
		
		int m = (l+r)/2;
		
		int Q1 = Query(2*n,l,m,i,j,k);
		
		int Q2 = Query(2*n+1,m+1,r,i,j,k);
		
		return (Q1+Q2);
	}
}
 
int main(){
	
    ios :: sync_with_stdio(false);
   
    //ifstream cin; ofstream cout; cin.open("input.txt"); cout.open("output.txt");
    
    int n;
    
    cin>>n;
    
    Array.resize(n+1);
    
    Tree.resize(4*(n+5));
    
    for(int i=1; i<=n; i++){
    	
    	cin>>Array[i];
	}
	
	Build(1,1,n);
	
	int q;
	
	cin>>q;
	
	while(q--){
		
		int i,j,k;
		
		cin>>i>>j>>k;
		
		cout<<Query(1,1,n,i,j,k)<<endl;
	}
}
