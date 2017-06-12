#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct Edge
{
    int src, dest;
};

struct Graph
{
     Edge* edge;
};

// A structure to represent a group for union-find
struct group
{
    int parent;
    int rank;
};

int sToInt(string x){
	int l=x.size();
	int y=0, i=0;
	while(i<l){
		int cx=x[i]-'0';
		y=y*10+cx;
		i++;
	}
	return y;
}

int find(struct group groups[], int i)
{
    if (groups[i].parent != i)
      groups[i].parent = find(groups, groups[i].parent); //path compression step 
    return groups[i].parent;
}
 
void Union(struct group groups[], int x, int y)//using union by rank method to find the union of 2 disoint sets
{
    int xparent = find(groups, x);
    int yparent = find(groups, y);
 
    if (groups[xparent].rank < groups[yparent].rank){
        groups[xparent].parent = yparent;
	}
    else if (groups[xparent].rank > groups[yparent].rank){
        groups[yparent].parent = xparent;
	}
    else
    {
        groups[yparent].parent = xparent;
        groups[xparent].rank++;
    }
}

int minCut(struct Graph* graph, int V, int E)
{
    Edge *edge = graph->edge;
 
    struct group *groups = new group[V];
 
    for (int v = 0; v < V; ++v)
    {
        groups[v].parent = v;
        groups[v].rank = 0;
    }
 
    while (V > 2)
    {
  	    int i = rand() % E;
    	int src_group = find(groups, edge[i].src);
        int dest_group = find(groups, edge[i].dest);
 
        if (src_group == dest_group)
        	continue;
        else
        {
	        V--;
    	    Union(groups, src_group, dest_group);
        }
    }
 
    int mincut = 0;
    for (int i=0; i<E; i++)
    {
        int src_group = find(groups, edge[i].src);
        int dest_group = find(groups, edge[i].dest);
        if (src_group != dest_group)
          mincut++;
    }
 
    return mincut;
}

int main(void){
	
	struct Graph *graph = new Graph;
	int V=200, E=2517;
	graph->edge = new Edge[E];

   	ifstream infile("KargerMinCut.txt");
    
    string buff;
    int k=0;
	
	//Storing edges in graph->edge[]
    while(getline(infile, buff)){
    
		int i=0;
		string side="";
		while(buff[i]!='\t' && buff[i]!='\0'){
			side= side + buff[i];
			i++;
		}
	
		int srce=sToInt(side);
		
		while(buff[i]!='\0'){
			side="";
			while(buff[i]=='\t' && buff[i]!= '\0')
				i++;
			
			while(buff[i]!='\t' && buff[i]!='\0'){
				side= side + buff[i];
				i++;
			}
			
			if(side!=""){
				int dst=sToInt(side);
				if(srce<dst){
					int edge_num=k++;
					graph->edge[edge_num].src = srce;
					graph->edge[edge_num].dest = dst;
				}
			}
			
		}
		
	}
	
	int i=0, mincut=1000;
	//runnning the mincut algorithm for multiple times as it doesn't guarantee in returning the mincut always.
	while(i<20){
		// Use a different seed value for every run.
    	srand(time(NULL));
    	int min=minCut(graph, V, E);
    	if(min<mincut)
    		mincut=min;
		i++; 
	}
	
	cout<<"Mincut value: "<<mincut<<endl;

 
	return 0;
}
