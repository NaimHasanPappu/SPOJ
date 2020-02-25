#include<bits/stdc++.h>
 
using namespace std;
 
#define lli long long int
 
vector <lli> arr,tree,lazy;
 
void make(lli n){
	
	arr.clear();
	
	tree.clear();
	
	lazy.clear();
	
	for(lli i=0; i<=n; i+=1){
		
		arr.push_back(0);
	}
	
	for(lli i=0; i<=4*n; i+=1){
		
		tree.push_back(0);
		
		lazy.push_back(0);
	}
}
 
void build(lli n,lli b,lli e){
	
	if(b == e){
		
		tree[n] = arr[b];
		
		return;
	}
	
	int m = (b+e)>>1;
	
	build(n*2,b,m);
	
	build(n*2+1,m+1,e);
	
	tree[n] = tree[n*2] + tree[n*2+1];
}
 
void update(lli n,lli b,lli e,lli i,lli j,lli v){
	
	if(b>e){
		
		return;
	}
	
	if(lazy[n] != 0){
		
		tree[n] += ((e-b+1)*lazy[n]);
		
		if(b != e){
			
			lazy[n*2] += lazy[n];
			
			lazy[n*2+1] += lazy[n];
		}
		
		lazy[n] = 0;
	}
	
	if(b>j || e<i){
		
		return;
	}
	
	if(b>=i && e<=j){
		
		tree[n] += ((e-b+1)*v);
		
		if(b != e){
			
			lazy[n*2] += v;
			
			lazy[n*2+1] += v;
		}
		
		return;
	}
	
	lli m = (b+e)>>1;
	
	update(n*2,b,m,i,j,v);
	
	update(n*2+1,m+1,e,i,j,v);
	
	tree[n] = tree[n*2] + tree[n*2+1];
}
 
lli query(lli n,lli b,lli e,lli i,lli j){
	
	if(b>e){
		
		return 0;
	}
	
	if(lazy[n] != 0){
		
		tree[n] += ((e-b+1)*lazy[n]);
		
		if(b != e){
			
			lazy[n*2] += lazy[n];
			
			lazy[n*2+1] += lazy[n];
		}
		
		lazy[n] = 0;
	}
	
	if(b>j || e<i){
		
		return 0;
	}
	
	if(b>=i && e<=j){
		
		return tree[n];
	}
	
	lli m = (b+e)>>1;
	
	lli q1 = query(n*2,b,m,i,j);
	
	lli q2 = query(n*2+1,m+1,e,i,j);
	
	return (q1+q2);
}
 
int main(){
	
	int t;
	
	scanf("%d",&t);
	
	while(t--){
		
		lli n,q;
		
		scanf("%lld %lld",&n,&q);
		
		make(n);
		
		build(1,1,n);
		
		while(q--){
			
			lli i,j,k;
			
			scanf("%lld %lld %lld",&k,&i,&j);
			
			if(k==0){
				
				lli v;
				
				scanf("%lld",&v);
				
				update(1,1,n,i,j,v);
			}
			
			else if(k==1){
				
				lli Q=query(1,1,n,i,j);
				
				printf("%lld\n",Q);
			}
		}
	}
}
