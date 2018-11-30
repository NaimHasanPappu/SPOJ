#include<bits/stdc++.h>

using namespace std;

map <int,int> In,Out;

bool comp(int x,int y){
	
	if(Out[x]==Out[y]){
		
		return x<y;
	}
	
	return Out[x]<Out[y];
}

int main(){
	
	int N,M;
	
	cin>>N>>M;
	
	vector <int> adj[N+1];
	
	for(int i=0; i<M; i+=1){
		
		int u,k;
		
		cin>>u>>k;
		
		Out[u]+=k;
		
		while(k--){
			
			int v;
			
			cin>>v;
			
			adj[v].push_back(u);
			
			In[v]+=1;
		}
	}
	
	vector <int> arr;
	
	for(int i=1; i<=N; i+=1){
		
		arr.push_back(i);
	}
	
	while(!arr.empty()){
		
		sort(arr.begin(),arr.end(),comp);
		
		int x=arr[0];
		
		for(int i=0; i<adj[x].size(); i+=1){
			
			int z=adj[x][i];
			
			Out[z]-=1;
		}
		
		arr.erase(arr.begin());
		
		cout<<x<<" ";
	}
}
