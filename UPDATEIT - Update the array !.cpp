#include<stdio.h>
 
#include<vector>
 
using namespace std;
 
vector <int> tree;
 
void build(int n){
	
	tree.clear();
	
	for(int i=0; i<=n; i+=1){
		
		tree.push_back(0);
	}
}
 
void update(int i,int n,int v){
	
	while(i<=n){
		
		tree[i]+=v;
		
		i+=(i)&(-i);
	}
}
 
void range_update(int i,int j,int n,int v){
	
	update(i,n,v);
	
	update(j+1,n,-v);
}
 
int query(int i,int n){
	
	int sum=0;
	
	while(i>0){
		
		sum+=tree[i];
		
		i-=(i)&(-i);
	}
	
	return sum;
}
 
int main(){
	
	int T;
	
	scanf("%d",&T);
	
	while(T--){
		
		int n,u;
		
		scanf("%d %d",&n,&u);
		
		build(n);
		
		while(u--){
			
			int i,j,v;
			
			scanf("%d %d %d",&i,&j,&v);
			
			range_update(i+1,j+1,n,v);
		}
		
		int q;
		
		scanf("%d",&q);
		
		while(q--){
			
			int i;
			
			scanf("%d",&i);
			
			printf("%d\n",query(i+1,n));
		}
	}
}
