#include<algorithm>
#include<climits>
#include<iostream>
#include<vector>
using namespace std;


int num_v;
vector<int> adjacency_matrix;
vector<bool> sptSet; // sptSet[i] will true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
vector<int> dist;    // dist[i] will hold the shortest distance from src to i; 
vector<int> previous;
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


int get_weight(int start, int end)
{
	return adjacency_matrix[(start-1)*num_v + (end-1)];
}


bool test_edge(int start, int end)
{
	bool flag = false;

	if(adjacency_matrix[(start-1)*num_v + (end-1)] != INT_MAX)    flag = true;

	return flag;
}

// get minimum index in the open table; 
int get_MinIndex()
{
	// Initialize min value
	int min_distance = INT_MAX;
	int min_index;
  
//    cout<<"Currently each distance in open table: "
	for(int i=0;i<OpenTable.size();i++)
	{
//		cout<<"Node "<<i+1<<" Dist "<<dist[i]<<endl;
		
		if(dist[OpenTable[i]-1] <= min_distance)
		{
			min_distance = dist[OpenTable[i]-1];
			min_index = i;
		}
	}

	return min_index;
}


// UFS continuous execution;
bool UFS(int source, int goal)
{
	// initialize before start; 
	for (int i=0;i<num_v;i++)
	{
        dist[i] = INT_MAX;
        sptSet[i] = false;
        previous[i] = -1;
	}
	
	dist[source-1] = 0;
	sptSet[source-1] = true;	
	tree[source-1].level = 0;
	
//	cout<<"Current Node:"<<i<<" "<<endl;
    result.push_back(source);	
	OpenTable.push_back(source);
	
	print_SearchTree();
	print_OpenTable();
	print_CloseTable();

	int current = -1;
	while(!OpenTable.empty())
	{
		int min_index = get_MinIndex();
//		cout<<"Minimum index "<<min_index<<endl; // test whether minimum index is correct; 
		current = OpenTable[min_index];	
		
		if(current==goal)
		{
			cout<<"We find goal:"<<current<<" "<<dist[current-1]<<endl;
			print_SearchTree();
			return true;
		}
		
		
		sptSet[OpenTable[min_index]-1] = true;	
		OpenTable.erase(OpenTable.begin() + min_index);				
		CloseTable.push_back(current);
		
		print_SearchTree();
		print_OpenTable();
		print_CloseTable();

		for(int j=1;j<=num_v;j++)
		{
			if((test_edge(current, j) == true)&&(sptSet[j-1]==false))
			{
//				cout<<"Current Node:"<<j<<" "<<endl;
                result.push_back(j);
				tree[current-1].child.push_back(j);
				tree[j-1].level = tree[current-1].level + 1;
				if(dist[j-1] >  dist[current-1] + get_weight(current, j))
				{
					dist[j-1] = dist[current-1] + get_weight(current, j); // compute distance from source to j;
					previous[j-1] = current;
				}
					
				if(find(OpenTable.begin(), OpenTable.end(), j) == OpenTable.end() )
				{
					OpenTable.push_back(j);					
				}											
				
				
                print_SearchTree();
				print_OpenTable();
				print_CloseTable();
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
			if(tree[result[i]-1].level > tree[result[i-1]-1].level)
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
	tree.resize(num_v);
	dist.resize(num_v);
	sptSet.resize(num_v);
	previous.resize(num_v);
	
	for(int i=0;i<N;i++)
	{
		tree[i].level = 0;
	}
	
	
	int M; //  number of edges	
	cin>>M;

	// create adjacency matrix;
	for(int i=0;i<N*N;i++)
	{
		adjacency_matrix.push_back(INT_MAX);
	}

	// save current amp in adjacency matrix;
	for(int i=0;i<M;i++)
	{
		int start;
		cin>>start;
		int end;
		cin>>end;

//		adjacency_matrix[(start-1)*N + (end-1)] = 1;
		cin>>adjacency_matrix[(start-1)*N + (end-1)];
	}

//	cout<<test_edge(2, 1)<<endl;
//	cout<<test_edge(2, 4)<<endl;

	

	UFS(1, 6); // UFS continuous execution;	
//	UFS_step(1, 5); //UFS step execution;


	
	// print search tree;
	
	cout<<endl;
	for(int i=0;i<N;i++)
	{
		cout<<"Node:"<<i+1<<"; Level:"<<tree[i].level<<"; Child:";
		for(int j=0;j<tree[i].child.size();j++)
		{
			cout<<tree[i].child[j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	print_SearchTree();
	cout<<endl;
	
	
//	cout<<get_weight(1, 6)<<" "<<get_weight(6, 1);
    
    cout<<"Distance from source: "<<endl;
    for(int i=0;i<dist.size();i++)
    {
    	cout<<"Node "<<i+1<<" Dist "<<dist[i]<<endl;
	}
	cout<<endl;
	
	cout<<"Previous Node: "<<endl;
    for(int i=0;i<dist.size();i++)
    {
    	cout<<"Node "<<i+1<<" Previous "<<previous[i]<<endl;
	}
	cout<<endl;

	
	return 0;
}


/*
6 8
1 2 1
1 6 12
2 3 3
2 4 1
3 5 3
4 5 1
4 6 2
5 6 3
*/


