#include<bits/stdc++.h>

using namespace std;

#define Min 1111111111

map < int , int > visit,parent,level,tree;

map < int , vector < int > > adj;

vector < int > Euler,Level;

void DFS(int n){
	
	visit[n]=1;
	
	Euler.push_back(n);
	
	Level.push_back(level[n]);
	
	for(int i=0; i<adj[n].size(); i+=1){
		
		int v=adj[n][i];
		
		if(visit[v]==0){
			
			DFS(v);
			
			Euler.push_back(n);
			
			Level.push_back(level[n]);
		}
	}
}

int main(){
	
	int T;
	
	cin>>T;
	
	for(int t=0; t<T; t+=1){
		
		Euler.clear();
		
		Level.clear();
		
		visit.clear();
		
		parent.clear();
		
		level.clear();
		
		adj.clear();
		
		int N;
		
		cin>>N;
		
		for(int i=1; i<=N; i+=1){
			
			int M;
			
			cin>>M;
			
			for(int j=1; j<=M; j+=1){
				
				int v;
				
				cin>>v;
				
				adj[i].push_back(v);
				
				adj[v].push_back(i);
			}
		}
		
		queue <int> q;
		
		q.push(1);
		
		visit[1]=1;
		
		while(!q.empty()){
			
			int u=q.front();
			
			q.pop();
			
			for(int i=0; i<adj[u].size(); i+=1){
				
				int v=adj[u][i];
				
				if(visit[v]==0){
					
					q.push(v);
					
					visit[v]=1;
					
					parent[v]=u;
					
					level[v]=1+level[u];
				}
			}
		}
		
		visit.clear();
		
		DFS(1);
		
		int Q;
		
		cin>>Q;
		
		printf("Case %d:\n",t+1);
		
		for(int i=0; i<Q; i+=1){
			
			int u,v;
			
			cin>>u>>v;
			
			int I,J;
			
			for(int j=0; j<Euler.size(); j+=1){
				
				if(Euler[j]==u){
					
					I=j;
					
					break;
				}
			}
			
			for(int j=0; j<Euler.size(); j+=1){
				
				if(Euler[j]==v){
					
					J=j;
					
					break;
				}
			}
			
			if(I>J){
				
				swap(I,J);
			}
			
			int LCA,MinLevel=Min;
			
			for(int j=I; j<=J; j+=1){
				
				if(MinLevel>Level[j]){
					
					MinLevel=Level[j];
					
					LCA=Euler[j];
				}
			}
			
			cout<<LCA<<endl;
		}
	}
}
