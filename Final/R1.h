#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

namespace R1{
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

	const int N = int(1e3)+10;
	int S[N],special[N];

	// input graph and source are 0-indexed
	// n - number of nodes
	// m - number of edges
	// s - number of sources
	// D - max distance to compute upto
	// source_inp[] - vector of sources
	// G - adj list of graph
	// ans - final ans will be stored in it
	void solve(int n, int m, int s, int D, VI &source_inp, VI G[], VVI &ans, int s1)
	{
		srand(time(NULL));
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s; i++) S[i] = source_inp[i];

		int sz = (n+s1-1)/s1;

		// Choose S1 special nodes
		VI S1(s1);
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++)
		{
			int l = i*sz, r = i*sz + sz -1;
			if(r>=n) r = n-1;
			int dis = rand()%(r-l+1) + l;
			S1[i] = dis;
			special[dis] = 1;
		}

		VVI result;
		B2::solve(G,n,m,s1,ceil(n/s1),S1,result);

		// Add new arcs into the graph G
		for(int i=0; i<s1; i++) m += SZ(result[i]);
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++)
			for(auto v:result[S1[i]])
				G[S1[i]].PB(v);


		// Transitive closure on graph with added arcs
		int nD = ceil((D*s1)/n) + ceil(n/s1);
		ans.clear();
		B2::solve(G,n,m,s,nD,source_inp,ans);
	}
};
