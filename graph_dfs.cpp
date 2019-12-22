#include<iostream>
#include<vector>
using namespace std;


int num_v; // number of vertices
vector<bool> adjacency_matrix;
vector<bool> visited;


bool test_edge(int start, int end)
{
	bool flag = false;

	if(adjacency_matrix[(start-1)*num_v+(end-1)]==true)    flag = true;
	if(adjacency_matrix[(start-1)+(end-1)*num_v]==true)    flag = true;

	return flag;
}

// DFS one range;
void DFS(int i)
{
	visited[i-1] = true;
	cout<<i<<" ";
	for(int j=1;j<=num_v;j++)
	{
		if((test_edge(i, j)==true)&&(visited[j-1]==false))
		{
			DFS(j);
		}
	}

}


// DFS all map;
void DFSTraverse()
{
	// initialize visited matrix;
	for(int i=1;i<=num_v;i++)
	{
		visited[i-1] = false;
	}


	for(int i=1;i<=num_v;i++)
	{
		if(visited[i-1]==false)
		{
			DFS(i);
		}
	}
}



int main()
{	
    cout<<"Input number of node and number of edge in the first line, input each edge in the following line."<<endl; 

	int N;
	cin>>N;
	num_v = N;	
	int M; //  number of edges
	cin>>M;

	// create adjacency matrix;
	adjacency_matrix.resize(N*N);
	for(int i=0;i<N*N;i++)
	{
		adjacency_matrix[i] = false;
	}

	// save current amp in adjacency matrix;
	for(int i=0;i<M;i++)
	{
		int start;
		cin>>start;
		int end;
		cin>>end;

		adjacency_matrix[(start-1)*num_v + (end-1)] = true;
		adjacency_matrix[(start-1) + (end-1)*num_v] = true;
	}

	// generate visited point;
	visited.resize(N);
	for(int i=0;i<N;i++)
	{
		visited[i] = false;
	}



//	DFS(5); // test DFS one range;
	DFSTraverse();


	return 0;
}

/*
6 4
1 2
1 6
3 4
2 5
*/

