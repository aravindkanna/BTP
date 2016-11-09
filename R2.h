#include <bits.stdc++.h>
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

	void get_distinguished(int s, int s1, VI &S1){
	
		set<int> A;
		srand(time(NULL));
		while(1){
			int x = rand() % s;
			A.insert(x);
			if(A.size() == s1){
				break;
			}
		}
		set<int>::iterator it;
		for(it = A.begin();it != A.end();it++) {
			S1.PB(*it);
		}
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
	void solve_R2(VI G[], int n, int e, int s, int d, VI S, VI &ans[], int s1) {
		VI distinguished S1;
		get_distinguished(s, s1, S1);

		//the graph with all the vertices but only s1 nodes will be connected
		VI G1[n];
		B2::solve(G, n, e, s1, ceil(n / s1), S1, G1);

		//Transitive Closure on the graph with only distinguished nodes
		VI G2[n];
		B1::solve(n, G, G2);

		//creating an adjacancy Matrix for the original graph
		VVI dist(n, VI(n, 0));
		for(int i = 0;i < n;i++)
			for(auto v : G[i])
				dist[i][v] = 1;

		int added_edges = 0;
		//copying the edges from G2 to Original matrix
		for(int i = 0;i < n;i++) {
			for(auto v : G2[i]) {
				dist[i][v] = 1;
				added_edges++;
			}
		}

		G.clear();
		G.resize(n);

		//Creating new Adjacency List for the original graph including the added edges
		for(int i = 0;i < n;i++) {
			for(int j = 0;j < n;j++) {
				if(dist[i][j]) {
					G[i].PB(j);
				}
			}
		}

		//final step to search
		ans.clear();
		ans.resize(n);
		B2::solve(G, n, e + added_edges, s, ceil(n / s1), S, ans);
	}

}