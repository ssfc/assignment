#include<iostream>
#include<vector>
using namespace std;


int num_v;
vector<bool> adjacency_matrix;
vector<bool> visited;
vector<int> OpenTable;
vector<int> CloseTable;

struct Node
{
	int key;
	int level;
	vector<int> child;
};

vector<Node> tree;
vector<int> result;

void print_OpenTable();
void print_CloseTable();
void print_SearchTree();

bool test_edge(int start, int end)
{
	bool flag = false;

	if(adjacency_matrix[start*num_v + end]==true)    flag = true;

	return flag;
}


// BFS continuous execution;
bool BFS(int source, int goal)
{
	visited[source] = true;	
	tree[source].level = 0;

//	cout<<"Current Node:"<<i<<" "<<endl;
    result.push_back(source);	
	OpenTable.push_back(source);
	
	print_SearchTree();
	print_OpenTable();
	print_CloseTable();

	int current = -1;
	while(!OpenTable.empty())
	{
		current = OpenTable.front();
		OpenTable.erase(OpenTable.begin());
		CloseTable.push_back(current);
		
		print_SearchTree();
		print_OpenTable();
		print_CloseTable();

		for(int j=0;j<num_v;j++)
		{
			if((test_edge(current, j) == true)&&(visited[j]==false))
			{
				visited[j] = true;
//				cout<<"Current Node:"<<j<<" "<<endl;
                result.push_back(j);
				tree[current].child.push_back(j);
				tree[j].level = tree[current].level + 1;
				
				if(j==goal)
				{
					cout<<"We find goal:"<<j<<endl;
					print_SearchTree();
					return true;
				}
								
				OpenTable.push_back(j);
				
                print_SearchTree();
				print_OpenTable();
				print_CloseTable();
			}
		}
	}
	
	cout<<"Not found!"<<endl;
	return false;
}


// BFS one range;
bool BFS_step(int source, int goal)
{
	visited[source] = true;	
	tree[source].level = 0;

//	cout<<"Current Node:"<<i<<" "<<endl;
    result.push_back(source);	
	OpenTable.push_back(source);
	
	print_SearchTree();
	print_OpenTable();
	print_CloseTable();	
	cout<<"Press enter to continue: "<<endl;
	cin.ignore();

	int current = -1;
	while(!OpenTable.empty())
	{
		current = OpenTable.front();
		OpenTable.erase(OpenTable.begin());
		CloseTable.push_back(current);
		
		print_SearchTree();
		print_OpenTable();
		print_CloseTable();		
		cout<<"Press enter to continue: ";
	    cin.ignore();

		for(int j=0;j<num_v;j++)
		{
			if((test_edge(current, j) == true)&&(visited[j]==false))
			{
				visited[j] = true;
//				cout<<"Current Node:"<<j<<" "<<endl;
                result.push_back(j);
				tree[current].child.push_back(j);
				tree[j].level = tree[current].level + 1;
				
				if(j==goal)
				{
					cout<<"We find goal:"<<j<<endl;
					print_SearchTree();
					return true;
				}
								
				OpenTable.push_back(j);
				
                print_SearchTree();
				print_OpenTable();
				print_CloseTable();				
				cout<<"Press enter to continue: ";
	            cin.ignore();
			}
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

void print_SearchTree()
{
	cout<<"Search tree: "<<endl;
	for(int i=0;i<result.size();i++)
	{
		if(i>0)
		{
			if(tree[result[i]].level > tree[result[i-1]].level)
			{
				cout<<endl; 
			}
		}
		
		
		cout<<result[i]<<" ";
	}
	
	cout<<endl;
	
	return;
}


int main()
{
	cout<<"Input number of node and number of edge in the first line, input each edge in the following line."<<endl; 
	
	int N; // number of vertices
	cin>>N;	
	num_v = N;
	tree.resize(N);
	
	for(int i=0;i<N;i++)
	{
		tree[i].level = 0;
	}
	
	
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

		adjacency_matrix[start*N + end] = true;
	}

//	cout<<test_edge(2, 1)<<endl;
//	cout<<test_edge(2, 4)<<endl;

	// generate visited point;
	visited.resize(N);
	for(int i=0;i<N;i++)
	{
		visited[i] = false;
	}



//	BFS(0, 4); // BFS continuous execution;	
	BFS_step(0, 4); //BFS step execution;


	
	// print search tree;
	
	cout<<endl;
	for(int i=0;i<N;i++)
	{
		cout<<"Node:"<<i<<"; Level:"<<tree[i].level<<"; Child:";
		for(int j=0;j<tree[i].child.size();j++)
		{
			cout<<tree[i].child[j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	print_SearchTree();
	cout<<endl;
	



	return 0;
}

/*
6 8
0 1
0 5
1 2
1 3
2 4
3 4
3 5
4 5
*/

