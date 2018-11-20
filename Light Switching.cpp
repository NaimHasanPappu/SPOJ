#include<bits/stdc++.h>

using namespace std;

vector <int> arr,tree,lazy;

void make(int n){
	
	for(int i=0; i<=n; i+=1){
		
		arr.push_back(0);
	}
	
	for(int i=0; i<=4*(n+1); i+=1){
		
		tree.push_back(0);
		
		lazy.push_back(0);
	}
}

void build(int n,int b,int e){
	
	if(b>e){
		
		return;
	}
	
	if(b==e){
		
		tree[n]=arr[b];
		
		return;
	}
	
	int m=(b+e)/2;
	
	build(n*2,b,m);
	
	build(n*2+1,m+1,e);
	
	tree[n]=tree[n*2]+tree[n*2+1];
}

void update(int n,int b,int e,int i,int j){
	
	if(b>e){
		
		return;
	}
	
	if(lazy[n]!=0){
		
		int c=(lazy[n])%2;
		
		if(c==1){
			
			tree[n]=(e-b+1)-tree[n];
		}
		
		if(b!=e){
			
			lazy[n*2]+=lazy[n];
			
			lazy[n*2+1]+=lazy[n];
		}
		
		lazy[n]=0;
	}
	
	if(b>j || e<i){
		
		return;
	}
	
	if(b>=i && e<=j){
		
		tree[n]=(e-b+1)-tree[n];
		
		if(b!=e){
		
			lazy[n*2]^=1;
		
			lazy[n*2+1]^=1;
		}
		
		return;
	}
	
	int m=(b+e)/2;
	
	update(n*2,b,m,i,j);
	
	update(n*2+1,m+1,e,i,j);
	
	tree[n]=tree[n*2]+tree[n*2+1];
}

int query(int n,int b,int e,int i,int j){
	
	if(b>e){
		
		return 0;
	}
	
	if(lazy[n]!=0){
		
		int c=(lazy[n])%2;
		
		if(c==1){
			
			tree[n]=(e-b+1)-tree[n];
		}
		
		if(b!=e){
			
			lazy[n*2]+=lazy[n];
			
			lazy[n*2+1]+=lazy[n];
		}
		
		lazy[n]=0;
	}
	
	if(b>j || e<i){
		
		return 0;
	}
	
	if(b>=i && e<=j){
		
		return tree[n];
	}
	
	int m=(b+e)>>1;
	
	int q1=query(n*2,b,m,i,j);
	
	int q2=query(n*2+1,m+1,e,i,j);
	
	return (q1+q2);
}

int main(){
	
	int n,q;
	
	scanf("%d %d",&n,&q);
	
	make(n);
	
	build(1,1,n);
	
	while(q--){
		
		int k,i,j;
		
		scanf("%d %d %d",&k,&i,&j);
		
		if(k==0){
			
			update(1,1,n,i,j);
		}
		
		else if(k==1){
			
			int Q=query(1,1,n,i,j);
			
			printf("%d\n",Q);
		}
	}
}
