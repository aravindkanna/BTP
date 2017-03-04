#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

namespace B2 {
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


	void dfs(int u, int len, VI &visited, VI &reached, VI* adj)
	{
		if(u >= SZ(visited) || u < 0) return;
		if(len == -1 || visited[u]) return;
		visited[u] = 1;
		reached.PB(u);
		for(int i=0; i<SZ(adj[u]); i++) {
			dfs(adj[u][i], len-1, visited, reached, adj);
		}
	}

	// input graph and source are 0-indexed
	// n - number of nodes
	// e - number of edges
	// s - number of sources
	// d - max distance to compute upto
	// S - vector of sources
	// G - adj list of graph
	// H - final ans will be stored in it
	void solve(VI G[], int n, int e, int s, int d, VI &S, VVI &H) {
		/*
		cout<<endl;
		trace("B2",n,e,s,d);
		for(int i=0; i<n; i++)
		{
			cout<<i<<": ";
			for(auto v:G[i]) cout<<v<<" ";
			cout<<endl;
		}
		trace("sources");
		for(int i=0; i<s; i++) cout<<S[i]<<" ";
		cout<<endl;
		*/

		cout << "Entered B2" << endl;

		int n_groups = ceil(s / d);
		int i = 0;
		H.clear(); H.resize(n);
		while(i < s) {
			int j = d;
			vector<int> subgroup;
			
			//selecting d sources every time
			while(j && i < s) {
				subgroup.push_back(S[i++]);
				j--;
			}

			int K = subgroup.size();
			//search forward from d sources with e processors
			#pragma omp parallel for default(shared) schedule(runtime) num_threads(e)
			for(int k = 0;k < K;k++) {
				vector<int> reached;
				vector<int> visited(n, 0);
				dfs(subgroup[k], d, visited, reached, G);
				H[subgroup[k]] = reached;
			}
		}
		/*
		for(int i=0; i<n; i++)
		{
			cout<<i<<": ";
			for(auto v:H[i]) cout<<v<<" ";
			cout<<endl;
		}
		cout<<endl;
		*/
	}
}
