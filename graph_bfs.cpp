#include<iostream>
#include<vector>
using namespace std;


int num_v;
vector<bool> adjacency_matrix;
vector<bool> visited;
vector<int> OpenTable;
vector<int> CloseTable;

void print_OpenTable();
void print_CloseTable();

bool test_edge(int start, int end)
{
	bool flag = false;

	if(adjacency_matrix[(start-1)*num_v+(end-1)]==true)    flag = true;

	return flag;
}


// BFS one range;
void BFS(int i)
{
	visited[i-1] = true;	

	vector<int> q;
	cout<<"Current Node:"<<i<<" "<<endl;	
	q.push_back(i);
	OpenTable.push_back(i);
	
	cout<<"q:";
	for(int k=0;k<q.size();k++)
	{
		cout<<q[k]<<" ";
	}
	cout<<endl;
	print_OpenTable();
	print_CloseTable();

	int current = -1;
	while(!q.empty())
	{
		current = q.front();
		q.erase(q.begin());
		OpenTable.erase(OpenTable.begin());
		CloseTable.push_back(current);
		
		print_OpenTable();
		print_CloseTable();

		for(int j=1;j<=num_v;j++)
		{
			if((test_edge(current, j) == true)&&(visited[j-1]==false))
			{
				visited[j-1] = true;
				cout<<"Current Node:"<<j<<" "<<endl;
				q.push_back(j);
				OpenTable.push_back(j);
				
				cout<<"q:";
				for(int k=0;k<q.size();k++)
				{
					cout<<q[k]<<" ";
				}
				cout<<endl;
				print_OpenTable();
				print_CloseTable();
			}
		}
	}
	
}



// BFS all map;
void BFSTraverse()
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
			BFS(i);
		}
	}
}

void print_OpenTable()
{
	cout<<"Open Table:";
	
	if(OpenTable.size()==0)
	{
		cout<<"Empty!";
	}
	else
	{
		for(int i=0;i<OpenTable.size();i++)
		{
			cout<<OpenTable[i]<<" ";
		}
	}
	
	
	cout<<endl;
}

void print_CloseTable()
{
	cout<<"Close Table:";
	
	if(CloseTable.size()==0)
	{
		cout<<"Empty!";
	}
	else
	{
		for(int i=0;i<CloseTable.size();i++)
		{
			cout<<CloseTable[i]<<" ";
		}
	}
	cout<<endl<<endl;
}


int main()
{
	cout<<"Input number of node and number of edge in the first line, input each edge in the following line."<<endl; 
	
	int N; // number of vertices
	cin>>N;	
	num_v = N;
	int M; //  number of edges	
	cin>>M;

	// create adjacency matrix;
	for(int i=0;i<N*N;i++)
	{
		adjacency_matrix.push_back(false);
	}

	// save current amp in adjacency matrix;
	for(int i=0;i<M;i++)
	{
		int start;
		cin>>start;
		int end;
		cin>>end;

		adjacency_matrix[(start-1)*N + (end-1)] = true;
	}

//	cout<<test_edge(2, 1)<<endl;
//	cout<<test_edge(2, 4)<<endl;

	// generate visited point;
	visited.resize(N);
	for(int i=0;i<N;i++)
	{
		visited[i] = false;
	}



	BFS(1); // test BFS one range;



	return 0;
}

/*
6 8
1 2
1 6
2 3
2 4
3 5
4 5
4 6
5 6
*/

