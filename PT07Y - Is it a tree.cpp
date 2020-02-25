#include<bits/stdc++.h>
 
using namespace std;
 
#define lli long long int
 
#define ulli unsigned long long int
 
#define Pi 3.14159265358979323846264338327950288419716939937510
 
vector <int> Parent;
 
int finder(int n){
	
	while(n != Parent[n]){
		
		Parent[n] = Parent[Parent[n]];
		
		n = Parent[n];
	}
	
	return n;
}
 
bool unite(int u,int v){
	
	int U = finder(u);
	
	int V = finder(v);
	
	if(U != V){
		
		Parent[U] = Parent[V];
		
		return true;
	}
	
	else{
		
		return false;
	}
}
 
int main(){
	
	ios :: sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
   
    int n,m;
    
    cin>>n>>m;
    
    Parent.resize(n+1);
    
    for(int i=0; i<=n; i++){
    	
    	Parent[i] = i;
	}
	
	bool tree = true;
	
	for(int i=0; i<m; i++){
		
		int u,v;
		
		cin>>u>>v;
		
		if(unite(u,v) == false){
			
			tree = false;
		}
	}
	
	if(tree){
		
		cout<<"YES";
	}
	
	else{
		
		cout<<"NO";
	}
}
