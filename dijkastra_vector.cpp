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
vector< pii > G[MAX];
int D[MAX];
bool F[MAX];


int dijk(int A, int B, vector< int > adj[],int n) 
{
	//int n = adj.size();
	//int n = adj.size();
	vector<int> dist(n);
	vector<bool> vis(n);

	for(int i = 0; i < n; ++i) 
	{
		dist[i] = INF;

	}

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(adj[i][j] != 1)
				adj[i][j] = INF;
		}
	}
	dist[A] = 0;

	for(int i = 0; i < n; ++i) 
	{
		int cur = -1;
		for(int j = 0; j < n; ++j) 
		{
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}

		vis[cur] = true;
		for(int j = 0; j < n; ++j) 
		{
			int path = dist[cur] + adj[cur][j];
			if (path < dist[j]) 
			{
				dist[j] = path;
				//cout<<" j = "<<j <<" path = " <<path<<endl;
			}
		}
	}

	return dist[B];
}


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

	vector <int>  adj[100];
	//vector < vector <int> > adj[100];
	//vector<pair<int,int> adj;
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
		//adj.push_back( std::vector<int>( u, v ) );
		adj[u].push_back(v);
		adj[v].push_back(u);
		
		//adj.push_back(neighbors);
		adj[v][u] = 1;
		adj[u][v] = 1;

	}
	scanf("%d", &starting);
	int ending;
	scanf("%d", &ending);

	gettimeofday(&tv1, NULL);
	int m = dijk(starting,ending,adj,nodes);
	/* record ending time */

	gettimeofday(&tv2, NULL);

	double time_taken = (tv2.tv_sec - tv1.tv_sec)*1000000.0 + ((tv2.tv_usec - tv1.tv_usec));
	// print the result
	printf("For Node %d, to node %d minimum distance using vectors= %d\n", starting,ending, m);
	printf("Time taken in finding path using vectors = %f micro seconds\n",time_taken);

	
	
	return 0;
}

