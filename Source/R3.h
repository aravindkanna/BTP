#include<bits/stdc++.h>
#include<omp.h>
#include "R2.h"

using namespace std;


namespace R3{
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
	#define trace(...) __f(	#__VA_ARGS__, __VA_ARGS__)
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

	const int N = int(1e5)+10;
	int S[N],special[N],source[N],sub[N];
	map<int,int> M;

	// input graph and source_inp are 0-indexed
	// n - number of nodes
	// m - number of edges
	// s - number of sources
	// D - max distance to compute upto
	// source_inp[] - vector of sources
	// G - adj list of graph
	// ans - final ans will be stored in it
	void solve(int n, int m, int s, int D, VI &source_inp, VI G[], VVI &ans, int s1, int flag=0, int s2=1)
	{

		cout << "Entered R3" << endl;

		srand(time(NULL));
		ans.clear(); ans.resize(s);
		// sort graph for binary search
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<n; i++) sort(ALL(G[i]));

		VI *RG = new VI[n];
		// construct reverse graph
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(binary_search(ALL(G[j]),i))
					RG[i].PB(j);

		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s; i++)
		{
			S[i] = source_inp[i];
			source[S[i]] = 1;
		}

		// Choose S1 special nodes
		VI S1(s1);
		int sz = (n+s1-1)/s1;
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++)
		{
			int l = i*sz, r = i*sz + sz -1;
			if(r>=n) r = n-1;
			int dis = rand()%(r-l+1) + l;
			S1[i] = dis;
			special[dis] = 1;
		}

		// Find transitive closure of reverse graph from special nodes
		VVI result;
		B2::solve(RG,n,m,s1,ceil(n/s1),S1,result);

		// Construct new graph
		M.clear();
		int sub_n = 0;
		for(int i=0; i<n; i++)
		{
			if(special[i] || source[i])
			{
				sub[sub_n] = i;
				M[i] = sub_n;
				sub_n++;
			}
		}
		VI *subgraph = new VI[sub_n];
		
		// Construct new graph with edges between special and special nodes
		for(int i=0; i<s1; i++) sort(ALL(result[S1[i]]));
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++)
		{
			int v = S1[i];
			for(int j=0; j<s1; j++)
			{
				int u = S1[j];
				if(binary_search(ALL(result[u]),v)) subgraph[M[v]].PB(M[u]);
			}
		}

		// Construct new graph with edges between sources and special nodes
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s; i++)
		{
			int v = S[i];
			for(int j=0; j<s1; j++)
			{
				int u = S1[j];
				if(binary_search(ALL(result[u]),v)) subgraph[M[v]].PB(M[u]);
			}
		}

		// Transitive closure of new subgraph
		int nD = ceil((2*D*s1)/n);
		if(!flag) B2::solve(subgraph,sub_n,m,s,nD,source_inp,result);
		else R2::solve(sub_n,m,s,nD,source_inp,subgraph,result,s2);

		// Add new edges to original graph
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s; i++)
		{
			int idx = M[S[i]];
			for(auto v: result[idx])
				G[S[i]].PB(sub[v]);
		}

		// Transitive closure of final graph
		B2::solve(G,n,m,s,ceil(n/s1),source_inp,ans);
	}
};
