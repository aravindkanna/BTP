#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

namespace B1{
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

	void transitive_closure(VVI &dist, int n)
	{
		int i, j, k;
		for (k = 0; k < n; ++k) 
			#pragma omp parallel for private(i,j)
			for (i = 0; i < n; ++i)
				for (j = 0; j < n; ++j)
					if ((i != j))
						dist[i][j] |= (dist[i][k] & dist[k][j]);
	}

	// input graph and source are 0-indexed
	// n - number of nodes
	// m - number of edges
	// s - number of sources
	// D - max distance to compute upto
	// source_inp[] - vector of sources
	// G - adj list of graph
	// ans - final ans will be stored in it
	void solve(int n, VI G[], VVI &ans)
	{
		/*
		trace("B1",n);
		for(int i=0; i<n; i++)
		{
			cout<<i<<": ";
			for(auto v:G[i]) cout<<v<<" ";
			cout<<endl;
		}
		*/
		VVI dist(n,VI(n,0));
		for(int i=0; i<n; i++)
			for(auto v:G[i])
				dist[i][v] = 1;
		transitive_closure(dist,n);
		ans.clear(); ans.resize(n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(dist[i][j])
					ans[i].PB(j);
		/*
		for(int i=0; i<n; i++)
		{
			cout<<i<<": ";
			for(auto v:ans[i]) cout<<v<<" ";
			cout<<endl;
		}
		*/
	}
};
