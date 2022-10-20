#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_VERTEX_NUM 20

struct edge{
    int headvertex,tailvertex;//边的起点 边的终点编号
    int value;//边的权值
    edge *headlink,*taillink;//起点相同的边 终点相同的边

    edge(int x,int y,int val,edge* tail,edge* head):
        headvertex(x),tailvertex(y),value(val),
        headlink(head),taillink(tail){};
};

struct vertex{
    char id;//顶点名
    edge *firstout,*firstin;//分别指向出边(起点相同的边)和入边(终点相同的边)
};

struct OLGraph{
    vertex v[MAX_VERTEX_NUM];//表头向量
    int vertexnum,edgenum;//顶点数目,边的数目
};

void init(OLGraph& G,int vertex,int edge){
    G.vertexnum = vertex;
    G.edgenum = edge;
    for(int i = 0; i < vertex; ++i){
        G.v[i].id = 'A' + '0';
        G.v[i].firstin = nullptr;
        G.v[i].firstout = nullptr;
    }
}

void insert(OLGraph &G,int x,int y){
    edge *p = new edge(x,y,1,G.v[y].firstin,G.v[x].firstout);
    G.v[y].firstin = G.v[x].firstout = p; //头插法
}

int main(){
    
    OLGraph G;
    init(G,5,7);
    int x[] = {0,0,2,2,3,3,3};
    int y[] = {1,2,0,3,0,1,2};
    for(int i=0;i<7;++i) insert(G,x[i],y[i]);

    for(int i=0;i<5;++i){
        cout<<"Vertex = "<< i <<"\n";
        cout<<"Outedge\n";
        edge *p = G.v[i].firstout;
        while(p!=nullptr){
            cout<<(char)('A' + p->headvertex)<<" "<<(char)('A' + p->tailvertex)<<"\n";
            p = p->headlink;
        }

        cout<<"inedge\n";
        p = G.v[i].firstin;
        while(p!=nullptr){
            cout<<(char)('A' + p->headvertex)<<" "<<(char)('A' + p->tailvertex)<<"\n";
            p = p->taillink;
        }

        cout<<"\n";
    }
    
    return 0;
}