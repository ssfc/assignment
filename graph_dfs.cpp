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


// DFS one range;
bool DFS(int source, int goal)
{
	visited[source-1] = true;	

//	cout<<"Current Node:"<<source<<" "<<endl;	
    OpenTable.insert(OpenTable.begin(), source);
	
	print_OpenTable();
	print_CloseTable();

	int current = -1;
	while(!OpenTable.empty())
	{
		current = OpenTable.front();	
		
		bool flag = false; 
		for(int j=1;j<=num_v;j++)
		{
			if((test_edge(current, j) == true)&&(visited[j-1]==false))
			{
				if(j==goal)
				{
					cout<<"We find goal:"<<j<<endl;
					return true;
				}
				
				
				visited[j-1] = true;
//				cout<<"Current Node:"<<j<<" "<<endl;
				OpenTable.insert(OpenTable.begin(), j);
				
				print_OpenTable();
				print_CloseTable();
				
				flag = true;
				break;
			}
		}
		
		if(flag==false)
		{
			OpenTable.erase(OpenTable.begin());
			CloseTable.push_back(current);
			
			print_OpenTable();
			print_CloseTable();
		}
	}
	
	cout<<"Not found!"<<endl;
	return false;
	
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



	DFS(1, 4); // test DFS one range;



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




