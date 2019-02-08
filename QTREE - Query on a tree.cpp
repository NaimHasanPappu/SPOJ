#include <bits/stdc++.h>

using namespace std;

#define Node 11111

int parent[Node],sub[Node],depth[Node],heavy[Node],head[Node];

int node_cost[Node],edge_cost[Node],edge_index[Node],node_index[Node];

int base[Node],tree[4*(Node+11)];

vector < int > adj[Node],cost[Node];

void prepare(){
	
	for(int i=0; i<Node; i+=1){
		
		parent[i] = 0;
		
		sub[i] = 1;
		
		depth[i] = 0;
		
		heavy[i] = -1;
		
		node_cost[i] = -1;
		
		edge_cost[i] = -1;
		
		head[i] = -1;
		
		edge_index[i] = 0;
		
		node_index[i] = 0;
		
		base[i] = 0;
		
		adj[i].clear();
		
		cost[i].clear();
	}
}

void bfs(int a){

	queue <int> q;

	stack <int> p;

	q.push(a);

	while(!q.empty()){

		int u = q.front();

		q.pop();

		p.push(u);

		int l = adj[u].size();

		for(int i=0; i<l; i+=1){

			int v = adj[u][i];

			int w = cost[u][i];

			if(v != parent[u]){

				q.push(v);

				parent[v] = u;

				node_cost[v] = w;

				depth[v] = depth[u] + 1;
			}
		}
	}

	while(!p.empty()){

		int u = p.top();

		p.pop();

		int v = parent[u];

		sub[v] += sub[u];

		if(heavy[v] == -1 || sub[u] > sub[heavy[v]]){

			heavy[v] = u;
		}
	}
}

void hld(int n){
	
	bfs(1);

	int i = 0, c = 0;

	for(int x=1; x<=n; x+=1){

		if(parent[x] == 0 || x != heavy[parent[x]]){

			//c++;

			for(int y=x; y!=-1; y=heavy[y]){

				//chain[y] = c;

				head[y] = x;

				i++;

				node_index[y] = edge_index[node_cost[y]] = i;

				base[i] = edge_cost[node_cost[y]];
			}
		}
	}
}

void build(int n,int l,int r){

	if(l>r){

		return;
	}

	if(l == r){

		tree[n] = base[l];

		return;
	}

	int m = (l+r)/2;

	build(n*2,l,m);

	build(n*2+1,m+1,r);

	tree[n] = max(tree[n*2],tree[n*2+1]);
}

void update(int n,int l,int r,int i,int v){

	if(l>r || l>i || r<i){

		return;
	}

	if(l == r){

		tree[n] = v;

		return;
	}

	int m = (l+r)/2;

	update(n*2,l,m,i,v);

	update(n*2+1,m+1,r,i,v);

	tree[n] = max(tree[n*2],tree[n*2+1]);
}

int query(int n,int l,int r,int i,int j){

	if(l>r || l>j || r<i){

		return -1;
	}

	if(l>=i && r<= j){

		return tree[n];
	}

	int m = (l+r)/2;

	int ql = query(n*2,l,m,i,j);

	int qr = query(n*2+1,m+1,r,i,j);

	return max(ql,qr);
}

int lca_finder(int u,int v){

	while(head[u] != head[v]){

		if(depth[head[u]] < depth[head[v]]){

			swap(u,v);
		}

		u = parent[head[u]];
	}

	return depth[u] < depth[v] ? u:v;
}

int chain_query(int n,int u,int w){

    int ans = -1;

    if(u != w){

        int i,j;

        while(head[u] != head[w]){

            i = node_index[head[u]];

            j = node_index[u];

            ans = max(ans,query(1,1,n,i,j));

            u = parent[head[u]];
        }

        if(u != w){

            i = node_index[w] + 1;

            j = node_index[u];

            ans = max(ans,query(1,1,n,i,j));
        }
    }

    return ans;
}

int path_query(int n,int u,int v){

    int w = lca_finder(u,v);

    int ans1 = chain_query(n,u,w);

    int ans2 = chain_query(n,v,w);

    return max(ans1,ans2);
}

int main(){

	ios::sync_with_stdio(0);
	
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
	
			cost[u].push_back(i);
	
			cost[v].push_back(i);
	
			edge_cost[i] = w;
		}
		
		hld(n);
	
		build(1,1,n);
	
		while(1){
	
			string s;
	
			cin>>s;
	
			if(s == "CHANGE"){
	
				int i,v;
	
				cin>>i>>v;
				
				i = edge_index[i];
	
				update(1,1,n,i,v);
			}
	
			else if(s == "QUERY"){
	
				int i,j;
	
				cin>>i>>j;
	
				if(i == j){
	
					cout<<"0";
				}
	
				else{
	
	                cout<<path_query(n,i,j)<<endl;
				}
			}
			
			else{
				
				break;
			}
		}
	}
}
