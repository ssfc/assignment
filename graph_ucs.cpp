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
vector<int> sequence;

void print_OpenTable();
void print_CloseTable();
void print_SearchTree();


int get_weight(int start, int end)
{
	return adjacency_matrix[start*num_v + end];
}


bool test_edge(int start, int end)
{
	bool flag = false;

	if(adjacency_matrix[start*num_v + end] != INT_MAX)    flag = true;

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
//		cout<<"Node "<<i<<" Dist "<<dist[i]<<endl;
		
		if(dist[OpenTable[i]] <= min_distance)
		{
			min_distance = dist[OpenTable[i]];
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
	
	dist[source] = 0;
	sptSet[source] = true;	
	tree[source].level = 0;
	
//	cout<<"Current Node:"<<i<<" "<<endl;
    sequence.push_back(source);	
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
			cout<<"We find goal:"<<current<<" Distance: "<<dist[current]<<endl;
			print_SearchTree();
			return true;
		}
		
		
		sptSet[OpenTable[min_index]] = true;	
		OpenTable.erase(OpenTable.begin() + min_index);				
		CloseTable.push_back(current);
		
		print_SearchTree();
		print_OpenTable();
		print_CloseTable();

		for(int j=0;j<num_v;j++)
		{
			if((test_edge(current, j) == true)&&(sptSet[j]==false))
			{
//				cout<<"Current Node:"<<j<<" "<<endl;
				
				if(dist[j] >  dist[current] + get_weight(current, j))
				{
					dist[j] = dist[current] + get_weight(current, j); // compute distance from source to j;
					previous[j] = current;
				}
					
				if(find(OpenTable.begin(), OpenTable.end(), j) == OpenTable.end() )
				{
					OpenTable.push_back(j);		
					print_SearchTree();
				    print_OpenTable();
				    print_CloseTable();			
				}											
				
				
                
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

void tree_bfs(int root)
{  
    for(int i=0;i<num_v;i++)
    {
    	tree[i].child.resize(0);
	}
	
	for(int i=0;i<num_v;i++)
	{
		if(previous[i] != -1)
		{
			tree[previous[i]].child.push_back(i);
		    tree[i].level = tree[previous[i]].level + 1;
		}		
	}

    sequence.resize(0);

    if (root == -1)
	{  
        return;  
    }  

	vector<int> q;  
    q.push_back(root);

    while (!q.empty())
	{
		int current = q[0];
		q.erase(q.begin());
		
		sequence.push_back(current); 

		if(tree[current].child.size()>0)
		{
			for(int i=0;i<tree[current].child.size();i++)
			{
				q.push_back(tree[current].child[i]);
			}
		}

    }

    return;
} 

void print_SearchTree()
{
	cout<<"Search tree: "<<endl;
	
	tree_bfs(0);
	
	for(int i=0;i<sequence.size();i++)
	{
		if(i>0)
		{
			if(tree[sequence[i]].level > tree[sequence[i-1]].level)
			{
				cout<<endl; 
			}
		}
		
		
		cout<<sequence[i]<<" ";
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
		cin>>adjacency_matrix[start*N + end];
	}
	

	UFS(0, 5); // UFS continuous execution;	
//	UFS_step(1, 6); //UFS step execution;
	
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
	
	
//	cout<<get_weight(1, 6)<<" "<<get_weight(6, 1);
    
    cout<<"Distance from source: "<<endl;
    for(int i=0;i<dist.size();i++)
    {
    	cout<<"Node "<<i<<" Dist "<<dist[i]<<endl;
	}
	cout<<endl;
	
	/*
	cout<<"Previous Node: "<<endl;
    for(int i=0;i<dist.size();i++)
    {
    	cout<<"Node "<<i<<" Previous "<<previous[i]<<endl;
	}
	cout<<endl;
	*/
	
	cout<<"Distance: "<<dist[5]<<endl;
	cout<<"Path: ";
	int current = 5;
	while(current != -1)
	{
		cout<<current;
		if(current != 0)    cout<<"<-";
		current = previous[current];
	}
	cout<<endl;

	
	return 0;
}


/*
6 8
0 1 1
0 5 12
1 2 3
1 3 1
2 4 3
3 4 1
3 5 2
4 5 3
*/


