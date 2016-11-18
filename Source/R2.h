#include <bits/stdc++.h>
#include "omp.h"

using namespace std;

namespace R2 {
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
	int distinguished[N];
	map<int,int> M;

	void get_distinguished(int n, int s1, VI &S1){
		SET(distinguished,0);
		M.clear();
		set<int> A;
		srand(time(NULL));
		while(1){
			int x = rand() % n;
			A.insert(x);
			if(A.size() == s1){
				break;
			}
		}
		set<int>::iterator it;
		for(it = A.begin();it != A.end();it++) {
			S1.PB(*it);
			distinguished[*it] = 1;
		}
		for(int i=0; i<SZ(S1); i++) M[S1[i]] = i;
	}


	// input graph and source are 0-indexed
	// n - number of nodes
	// e - number of edges
	// s - number of sources
	// d - max distance to compute upto
	// S - vector of sources
	// G - adj list of graph
	// s1 - Number of Distinguished Nodes
	// ans - final ans will be stored in it
	void solve(int n, int e, int s, int d, VI &S, VI G[], VVI &ans, int s1) {

		cout << "Entered R2" << endl;

		VI S1;
		get_distinguished(n, s1, S1);

		// The graph with all the vertices but only s1 nodes will be connected
		VVI G1;
		B2::solve(G, n, e, s1, ceil(n / s1), S1, G1);

		// Construct subgraph of distinguished nodes with new arcs found in G1
		VI * subgraph = new VI[s1];
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++)
		{
			int u = S1[i];
			for(auto v:G1[u])
				if(distinguished[v]) subgraph[i].PB(M[v]);
		}

		// Transitive Closure on the subgraph with only distinguished nodes
		VVI G2;
		B1::solve(s1, subgraph, G2);
		for(int i=0; i<s1; i++) e += SZ(G2[i]);

		// Add new arcs found in G2 to original graph G
		#pragma omp parallel for default(shared) schedule(runtime)
		for(int i=0; i<s1; i++) 
			for(auto v:G2[i])
				G[S1[i]].PB(S1[v]);

		// Final step to search
		ans.clear();
		ans.resize(n);
		B2::solve(G, n, e, s, ceil(n / s1), S, ans);
	}
}
