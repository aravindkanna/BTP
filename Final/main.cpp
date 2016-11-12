#include<bits/stdc++.h>
#include "B1.h"
#include "B2.h"
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);

const int N = int(1e3)+10;
VI G[N],S;
VVI tmp;
int n,m,s,D,t,rootN;

void print(VVI &ans)
{
	for(int i=0; i<SZ(S); i++)
	{
		printf("%d : ",S[i]+1);
		sort(ALL(ans[i]));
		for(int j=0; j<SZ(ans[i]); j++)
			printf("%d ",ans[i][j]+1);
		printf("\n");
	}
}

void test_recursive()
{
	VVI R1,R2,R3,R4;
	R1::solve(n,m,s,D,S,G,R1,rootN);
	for(int i=0; i<n; i++) G[i] = tmp[i];
	R2::solve(n,m,s,D,S,G,R2,rootN);
	for(int i=0; i<n; i++) G[i] = tmp[i];
	R3::solve(n,m,s,D,S,G,R3,rootN);
	for(int i=0; i<n; i++) G[i] = tmp[i];
	R4::solve(n,m,s,D,S,G,R4);

	printf("R1\n"); print(R1);
	printf("\n\n\nR2\n"); print(R2);
	printf("\n\n\nR3\n"); print(R3);
	printf("\n\n\nR4\n"); print(R4);
}

int main()
{
	scanf("%d %d %d %d %d",&n,&m,&s,&D,&t);
	rootN = 0; while(rootN*rootN<n) rootN++;
	tmp.clear(); tmp.resize(n);
	for(int i=0; i<m; i++)
	{
		int u,v; scanf("%d %d",&u,&v); u--; v--;
		G[u].PB(v);
		tmp[u].PB(v);
	}
	for(int i=0; i<s; i++)
	{
		int x; scanf("%d",&x); x--;
		S.PB(x);
	}
	
	//test_recursive();

	VVI ans;
	if(D <= t && D <= rootN) B2::solve(G,n,m,s,D,S,ans);
	else if(t >= rootN) R1::solve(n,m,s,D,S,G,ans,rootN);
	else if(s >= ceil(n/t)) R2::solve(n,m,s,D,S,G,ans,ceil(n/t));
	else if(D <= t*t) R3::solve(n,m,s,D,S,G,ans,ceil(n/t));
	else R3::solve(n,m,s,D,S,G,ans,ceil(n/t));

	printf("Graph:\n");
	print(tmp);
	printf("Transitive Closure:\n");
	print(ans);
	return 0;
}
