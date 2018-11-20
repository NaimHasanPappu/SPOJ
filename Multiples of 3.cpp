#include<bits/stdc++.h>

using namespace std;

class M{
	
	public:
		
		int c0,c1,c2;
		
		M(){
			
			c0=c1=c2=0;
		}
};

vector <M> tree;

vector <int> lazy;

void make(int n){
	
	for(int i=0; i<=4*(n+1); i+=1){
		
		M obj;
		
		tree.push_back(obj);
		
		lazy.push_back(0);
	}
}

void add ( M &n1 , M &n2 , M &n3 ){
	
	n1.c0=n2.c0+n3.c0;
	
	n1.c1=n2.c1+n3.c1;
	
	n1.c2=n2.c2+n3.c2;
	
	return;
}

void toggle( M &n ){
	
	int t=n.c0;
	
	n.c0=n.c2;
	
	n.c2=n.c1;
	
	n.c1=t;
	
	return;
}

void build(int n,int b,int e){
	
	if(b>e){
		
		return;
	}
	
	if(b==e){
		
		tree[n].c0=1;
		
		tree[n].c1=0;
		
		tree[n].c2=0;
		
		return;
	}
	
	int m=(b+e)>>1;
	
	build(n*2,b,m);
	
	build(n*2+1,m+1,e);
	
	add(tree[n],tree[n*2],tree[n*2+1]);
}

void update(int n,int b,int e,int i,int j){
	
	if(b>e){
		
		return;
	}
	
	if(lazy[n]!=0){
		
		int t=(lazy[n])%3;
		
		if(t==1){
			
			toggle(tree[n]);
		}
		
		else if(t==2){
			
			toggle(tree[n]);
			
			toggle(tree[n]);
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
		
		toggle(tree[n]);
		
		if(b!=e){
			
			lazy[n*2]+=1;
			
			lazy[n*2+1]+=1;
		}
		
		return;
	}
	
	int m=(b+e)>>1;
	
	update(n*2,b,m,i,j);
	
	update(n*2+1,m+1,e,i,j);
	
	add(tree[n],tree[n*2],tree[n*2+1]);
}

int query(int n,int b,int e,int i,int j){
	
	if(b>e){
		
		return 0;
	}
	
	if(lazy[n]!=0){
		
		int t=(lazy[n])%3;
		
		if(t==1){
			
			toggle(tree[n]);
		}
		
		if(t==2){
			
			toggle(tree[n]);
			
			toggle(tree[n]);
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
		
		return tree[n].c0;
	}
	
	int m=(b+e)>>1;
	
	int q1=query(n*2,b,m,i,j);
	
	int q2=query(n*2+1,m+1,e,i,j);
	
	return (q1+q2);
}

void solve(){
	
	int n,q;
	
	scanf("%d %d",&n,&q);
	
	make(n);
	
	build(1,1,n);
	
	while(q--){
		
		int i,j,k;
		
		scanf("%d %d %d",&k,&i,&j);
		
		if(k==0){
			
			update(1,1,n,i+1,j+1);
		}
		
		else{
			
			int q=query(1,1,n,i+1,j+1);
			
			printf("%d\n",q);
		}
	}
}

int main(){
	
	solve();
}
