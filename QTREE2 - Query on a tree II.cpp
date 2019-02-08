#include <bits/stdc++.h>
 
using namespace std;
 
#define Node 11111
 
int parent[Node],depth[Node],dist[Node];
 
int sparse[Node][16];
 
vector < int > adj[Node],cost[Node];
 
void prepare(){
	
	for(int i=0; i<Node; i+=1){
		
		adj[i].clear();
		
		cost[i].clear();
		
		parent[i] = -1;
		
		dist[i] = 0;
		
		depth[i] = 0;
		
		for(int j=0; j<=15; j+=1){
			
			sparse[i][j] = -1;
		}
	}
}
 
void bfs(int a){
 
	queue <int> q;
 
	q.push(a);
 
	while(!q.empty()){
 
		int u = q.front();
 
		q.pop();
 
		int l = adj[u].size();
 
		for(int i=0; i<l; i+=1){
 
			int v = adj[u][i];
 
			if(v != parent[u]){
 
				q.push(v);
 
				parent[v] = u;
 
				depth[v] = depth[u] + 1;
				
				dist[v] = dist[u] + cost[u][i];
			}
		}
	}
}
 
void sparse_filler(){
	
	for(int i=0; i<Node; i+=1){
		
		sparse[i][0] = parent[i];
	}
	
	for(int j=1; j<=15; j+=1){
		
		for(int i=0; i<Node; i+=1){
			
			if(sparse[i][j-1] != -1){
				
				int x = sparse[i][j-1];
				
				sparse[i][j] = sparse[x][j-1];
			}
		}
	}
}
 
int lca_finder(int u,int v){
 
	if(depth[u] < depth[v]){
		
		swap(u,v);
	}
	
	int d = depth[u] - depth[v];
	
	while(d){
		
		int up = (int)(log2(d));
		
		u = sparse[u][up];
		
		d -= (int)(1<<up);
	}
	
	if(u == v){
		
		return u;
	}
	
	for(int i=15; i>=0; i-=1){
		
		if((sparse[u][i] != sparse[v][i]) && (sparse[u][i] != -1)){
			
			u = sparse[u][i];
			
			v = sparse[v][i];
		}
	}
	
	return parent[u];
}
 
int kth_finder(int a,int b,int lca,int k){
	
	int da = depth[a] - depth[lca];
	
	if(k > da+1){
		
		k -= (da+1);
		
		k = (depth[b]-depth[lca]-k);
		
		while(k){
			
			int up = (int)(log2(k));
			
			b = sparse[b][up];
			
			k -= (int)(1<<up);
		}
		
		return b;
	}
	
	else{
		
		k -= 1;
		
		while(k){
			
			int up = (int)(log2(k));
			
			a = sparse[a][up];
			
			k -= (int)(1<<up);
		}
		
		return a;
	}
}
 
int main(){
	
	ios :: sync_with_stdio(false);
	
	int T;
	
	cin>>T;
	
	while(T--){
 
		int n;
	
		cin>>n;
		
		prepare();
	
		for(int i=1; i<n; i+=1){
	
			int u,v,w;
	
			cin>>u>>v>>w;
	
			adj[u].push_back(v);
	
			adj[v].push_back(u);
	
			cost[u].push_back(w);
	
			cost[v].push_back(w);
		}
		
		bfs(1);
		
		sparse_filler();
		
		while(1){
			
			string s;
			
			cin>>s;
			
			if(s == "DIST"){
				
				int i,j;
				
				cin>>i>>j;
				
				int lca = lca_finder(i,j);
				
				cout<<(dist[i]+dist[j]-2*dist[lca])<<endl;
			}
			
			else if(s == "KTH"){
				
				int i,j,k;
				
				cin>>i>>j>>k;
				
				int lca = lca_finder(i,j);
				
				cout<<kth_finder(i,j,lca,k)<<endl;
			}
			
			else if(s == "DONE"){
				
				break;
			}
		}
	}
}
