/**
References:
http://www.cplusplus.com/forum/general/124853/
http://www.cplusplus.com/reference/list/list/unique/
http://www.cplusplus.com/doc/tutorial/files/
http://www.cplusplus.com/reference/list/list/insert/
**/


#include <fstream>
#include <functional>
#include <climits>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;


/** this structure is used to represent each node **/
struct node {
	int vertex;
	int weight;
	node(int v, int w) : vertex(v), weight(w) { };
	node() { }
};


/** this is structure to store weight and previous node's link **/
struct path{
	int weights;
	int pathSource;
	int currentVertex;
	path() : weights(INT_MAX), pathSource(-1), currentVertex(-1){ }; 
};


/** this is the vector to store graph **/
vector< list<node> > adj;
vector<path> paths;

void readData();
void Dijkstra(node);
void writeDataDijkstra();
void countVertexAndEdges(int& , int&);


/** call by reference **/
void countVertexAndEdges(int& vertexCount, int& edgesCount){
	string line;
	/** it store all the vertex of graph **/	
	list<int> vertex;
	edgesCount=0;
	vertexCount=0;

	/** open input file **/
	fstream in("graph.dat", ios::in);

	/** read line by line **/	
	while (getline(in, line))
	{
		/** create stream from line **/
    		istringstream iss(line);
    		int node, weight, vertices;

		/** first element in vertex **/
		iss>>vertices;
		vertex.push_back(vertices);

		/** read next two element **/	
    		while((iss >> node >> weight)) {
			vertex.push_back(node);
			/** for each edge increment number of edges **/
			edgesCount++;		
		}
	}

	/** remove duplicate from the file **/
	vertex.sort();
	vertex.unique();

	vertexCount = vertex.size();
	in.close();
}


int main(int argc, char *argv[]) {
	/** Read data from the file and store in data structure**/
	readData();

	/** Apply dijkstra algorithm **/
	Dijkstra(node(1, 0));

	/** Write dijkstra output in file **/
	writeDataDijkstra();

	return 0;
}

void readData() {
	string line;
	fstream in("graph.dat", ios::in);
	
	int nrVertices,  nrEdges, weight, nodeX, nodeY;

	/** count number of verties and edges **/
	countVertexAndEdges(nrVertices, nrEdges);

	/** resize adjacency list **/
	adj.resize(nrVertices+1);

	/** resize path vector **/
	paths.resize(nrVertices+1);

	/** read file line by line **/
	while (getline(in, line))
	{
    		istringstream iss(line);
    		
		iss>>nodeX;
			
    		while((iss >> nodeY >> weight)) {
			/** push each edge in vector **/
			adj[nodeX].push_back(node(nodeY, weight));
								
		}
	}

	in.close();
}

void Dijkstra(node startNode) {
	/** this is a comparator class **/
	class CompareGreater {
		public:
			bool const operator()(node &nodeX, node &nodeY) {
				return (nodeX.weight > nodeY.weight) ;
			}
	};

	/** this is queue whioch is used to implement graph **/
	priority_queue<node, vector<node>, CompareGreater> Q;

	node currentNode;

	/** initialise the source vertex **/
	paths.at(startNode.vertex).weights = 0;
	paths.at(startNode.vertex).currentVertex = 1;
	paths.at(startNode.vertex).pathSource = 1;
	
	Q.push(startNode);

	/** implementting core dijkstra algo
		read each node from queue and push child vertex in queue **/

	while (!Q.empty()) {
		currentNode = Q.top();
		Q.pop();

		
		if (currentNode.weight <= paths.at(currentNode.vertex).weights) {
			/** for each adjacent node check if current weight can be reduces **/
			for (list<node>::iterator it = adj[currentNode.vertex].begin(); it != adj[currentNode.vertex].end(); ++it) {

				/** if current weight can be reduces reset data **/
				if (paths.at(it->vertex).weights > paths.at(currentNode.vertex).weights + it->weight) {
					paths.at(it->vertex).weights =  paths.at(currentNode.vertex).weights + it->weight;
					paths.at(it->vertex).pathSource = currentNode.vertex;
					paths.at(it->vertex).currentVertex = it->vertex;
					/** push child vertex **/
					Q.push(node((it->vertex), paths.at(it->vertex).weights));
				}
			}
		}
	}
}

void writeDataDijkstra() {
	fstream out("dijkstra.out", ios::out);
	int temp;
	
	string pathFinal;
	for (auto indx = 0; indx < paths.size(); ++indx) {
		temp = paths.at(indx).currentVertex;
		pathFinal.clear();
		if(temp>1){
			/** traverse to get the final path **/
			while(temp!=1){
				pathFinal.append(" from ");
				pathFinal.append(to_string(temp));	
				temp=paths.at(temp).pathSource;		
			}
			pathFinal.append(" from ");
			pathFinal.append(to_string(temp));
		

			out <<"Vertex " << paths.at(indx).currentVertex;
			out <<" can be traverse following path "<< pathFinal;
			out <<" which will have total weight of "<< paths.at(indx).weights<<endl;
			
			cout <<"Vertex " << paths.at(indx).currentVertex;
			cout <<" can be traverse following path "<< pathFinal;
			cout <<" which will have total weight of "<< paths.at(indx).weights<<endl;
		}
	}

	out.close();
}

