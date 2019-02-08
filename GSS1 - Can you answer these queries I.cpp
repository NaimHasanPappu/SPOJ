#include<bits/stdc++.h>

using namespace std;

class Node{
	
	public:
		
		int prefix;
		
		int suffix;
		
		int sum;
		
		int best_sum;
};

Node Inf;

void INF(){
	
	Inf.prefix=-999999999;

	Inf.suffix=-999999999;

	Inf.sum=0;

	Inf.best_sum=-999999999;
}

Node combine(Node l,Node r){
	
	Node z;
	
	z.prefix	= max(l.prefix,l.sum+r.prefix);
	
	z.suffix	= max(r.suffix,r.sum+l.suffix);
	
	z.sum		= l.sum+r.sum;
	
	z.best_sum	= max((l.suffix+r.prefix),max(l.best_sum,r.best_sum));
	
	return z;
}

vector <Node> Tree;

vector <int> arr;

void build(int n,int b,int e){
	
	if(b>e){
		
		return;
	}
	
	if(b==e){
		
		Tree[n].prefix=Tree[n].suffix=Tree[n].sum=Tree[n].best_sum=arr[b];
		
		return;
	}
	
	int m=(b+e)/2;
	
	build(n*2,b,m);
	
	build(n*2+1,m+1,e);
	
	Tree[n]=combine(Tree[n*2],Tree[n*2+1]);
}

Node query(int n,int b,int e,int i,int j){
	
	if(b>e || e<i || b>j){
		
		return Inf;
	}
	
	if(b>=i && e<=j){
		
		return Tree[n];
	}
	
	int m=(b+e)/2;
	
	Node q1=query(n*2,b,m,i,j);
	
	Node q2=query(n*2+1,m+1,e,i,j);
	
	return combine(q1,q2);
}

int main(){
	
	INF();
	
	int n;
	
	scanf("%d",&n);
	
	for(int i=0; i<=4*(n+5); i+=1){
		
		Node N;
		
		Tree.push_back(N);
	}
	
	for(int i=0; i<n; i+=1){
		
		int x;
		
		scanf("%d",&x);
		
		arr.push_back(x);
	}
	
	build(1,0,n-1);
	
	int q;
	
	scanf("%d",&q);
	
	while(q--){
		
		int i,j;
		
		scanf("%d %d",&i,&j);
		
		i-=1;
		
		j-=1;
		
		Node x=query(1,0,n-1,i,j);
		
		printf("%d\n",x.best_sum);
	}
}
