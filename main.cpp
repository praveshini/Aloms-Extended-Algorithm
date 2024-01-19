#include <iostream>
#include<vector>

using namespace std;

vector<int> coverList;
int noOfVertices;
int  noOfEdges;

class Graph
{
    public:
        vector<int>vertices;
        vector<vector<int>> edges;


        int max_end_vertex();
        void vertexCover();
        void findMin();
        bool is_empty();
};



//vector<int> maxFrequency(Graph&,vector<int>);



int main()
{
    Graph G1;
    cout<<"Enter no of vertices: ";
    cin>>noOfVertices;
    G1.vertices.assign(noOfVertices,0);
    cout<<"\nEnter no of edges: ";
    cin>>noOfEdges;
    G1.edges.assign(noOfVertices,vector<int>(noOfVertices,0));
    for(int i=0;i<noOfEdges;i++)
        {
            int head,tail;
            cout<<"\nEdge "<<i+1;
            cout<<"\nEnter head vertex: ";
            cin>>head;
            cout<<"\nEnter tail vertex: ";
            cin>>tail;
            G1.edges[head][tail]=1;
            G1.edges[tail][head]=1;
        }
    G1.vertexCover();
    //for(int i=0;i<G1.vertices.size();i++)
        //for(int j=0;j<G1.vertices.size();j++)
           // cout<<G1.edges[i][j];

    return 0;
}

int Graph::max_end_vertex()
{
    vector<int> f(vertices.size(),0);
    for(int l=0;l<vertices.size();l++)
    {
        for(int k=0;k<vertices.size();k++)
        {
            if(edges[l][k]==1)
                f[l]+=1;
        }
    }
    int maX=0;
    for(int i=0;i<f.size();i++)
    {
        if(maX < f[i])
            maX=f[i];
    }
    vector<int> check_vertex;
    for(int i=0;i<f.size();i++)
    {
        if(maX == f[i])
            check_vertex.push_back(i); //pushing those vertices which have maximum number of incident edges
    }
    int i=0;
    for(i=0;i<check_vertex.size();i++)
    {
        int countV=0;
        if(f[check_vertex[i]] > check_vertex.size()) // the vertex i has edges that covers vertices apart from check_vertex
            break;
        else
        {
            for(int j=0;j<check_vertex.size();j++)
                if(i!=j && edges[check_vertex[i]][check_vertex[j]] == 1)
                    countV+=1;
            if(countV < check_vertex.size()-1)
                break;
        }
    }
    if(i==check_vertex.size())
        i=0;
    return check_vertex[i];
}

void Graph::vertexCover()
{
    for(int j=0;j<noOfVertices;j++)
    {
         Graph graphDup;
         graphDup.vertices = vertices;
         graphDup.edges = edges;
         for(int i=0;i<vertices.size();i++)
        {
            graphDup.edges[j][i]=0;
            graphDup.edges[i][j]=0;
        }
        coverList.clear();
        coverList.push_back(j);
        graphDup.findMin();
    }
    //for(int i=0;i<noOfVertices;i++)
        //cout<<coverList[i]<<" ";
}


bool Graph::is_empty()
{
    for(int i=0;i<vertices.size();i++)
        for(int j=0;j<vertices.size();j++)
    {
        if(edges[i][j] == 1)
            return 0;
    }
    return 1;
}

void Graph::findMin()
{
    int k=0;
    while(!is_empty())
    {
        k=max_end_vertex();
        coverList.push_back(k);
        for(int i=0;i<vertices.size();i++)
        {
                edges[k][i]=0;
                edges[i][k]=0;
        }
    }
    cout<<"\n";
    for(int i=0;i<coverList.size();i++)
        cout<<coverList[i]<<" ";
}
