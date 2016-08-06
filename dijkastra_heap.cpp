#include <cstdio>
#include <utility>
#include <cstdlib>
#include <queue>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#define MAX 100001
#define INF (1<<20)
#define pii pair< int, int >
#define pb(x) push_back(x)

struct comp {
	bool operator() (const pii &a, const pii &b) {
		return a.second > b.second;
	}
};




priority_queue< pii, vector< pii >, comp > Q;
vector< pii > G[MAX];
int D[MAX];
bool F[MAX];




int main(int argc, char *argv[]) 
{
	struct timeval  tv1, tv2;
	if(argc != 3)
	{
		cout<<"Invalid arguments!!!\n";
		exit(-1);
	}
	int i, u, v, w, sz, nodes, edges, starting;
	char *file_name = argv[1];

	
	int iter = atoi(argv[2]);

	// create graph
	// read content from file

	std::ifstream infile(argv[1]);
	infile >> nodes >> edges;

	w = 1;
	vector<int> neighbors;
	for(i=0; i<edges; i++) 
	{
		infile>>u>>v;
		
		G[u].pb(pii(v, w));
		G[v].pb(pii(u, w)); // for undirected
		
	}
	scanf("%d", &starting);
	int ending;
	scanf("%d", &ending);



	gettimeofday(&tv1, NULL);
	// now finding using heaps */
	// initialize distance vector
	for(i=1; i<=nodes; i++) D[i] = INF;
	D[starting] = 0;
	Q.push(pii(starting, 0));

	// dijkstra algorithm using heaps
	while(!Q.empty()) 
	{
		u = Q.top().first;
		Q.pop();
		if(F[u]) continue;
		sz = G[u].size();
		for(i=0; i<sz; i++) {

			v = G[u][i].first;
			w = G[u][i].second;
			if(!F[v] && D[u]+w < D[v]) {
				D[v] = D[u] + w;
				Q.push(pii(v, D[v]));
			}
		}
		F[u] = 1; // done with u
	}

	gettimeofday(&tv2, NULL);
	double time_taken = (tv2.tv_sec - tv1.tv_sec)*1000000.0 + ((tv2.tv_usec - tv1.tv_usec));
	// print the result
	printf("For Node %d, to node %d minimum distance using heaps= %d\n", starting,ending, D[ending]);
	printf("Time taken in finding path using heaps = %f micro seconds\n",time_taken);
	return 0;
}
