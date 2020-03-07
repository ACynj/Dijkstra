#include<stdio.h>
#include<stdlib.h>
/*堆栈的定义*/
typedef struct snode* Stack;
struct snode {
	int Data;
	Stack Next;
};
Stack makeempty() {
	Stack s = (Stack)malloc(sizeof(struct snode));
	s->Next = NULL;
	return s;
}
void push(Stack s,int x) {
	Stack newnode = (Stack)malloc(sizeof(struct snode));
	newnode->Data = x;
	newnode->Next = s->Next;
	s->Next = newnode;
}
int pop(Stack s) {
	int temp = s->Next->Data;
	Stack x = s->Next;
		s->Next = x->Next;
		free(x);
		return temp;

}
/*图的定义*/
typedef struct enode* Edge;
typedef struct mgraph* MGraph;
struct enode {
	int v1, v2, weight;
};
struct mgraph {
	int nv, ne, G[1000][1000];
};
MGraph creat(int n) {
	MGraph Graph = (MGraph)malloc(sizeof(struct mgraph));
	Graph->nv = n;
	Graph->ne = 0;
	for (int i = 0; i < Graph->nv; i++) {
		for (int j = 0; j < Graph->nv; j++) {
			Graph->G[i][j] = 10000;
		}
	}
	return Graph;
}
MGraph build() {
	int n, e;
	scanf_s("%d %d", &n, &e);
	MGraph Graph = creat(n);
	Graph->ne = e;
	if (Graph->ne != 0) {
		for (int i = 0; i < Graph->ne; i++) {
			Edge E = (Edge)malloc(sizeof(struct enode));
			scanf_s("%d %d %d", &E->v1, &E->v2, &E->weight);
			Graph->G[E->v1][E->v2] = E->weight;
		}
	}
	return Graph;
}
/*图的定义结束*/
int findMinDist(MGraph Graph,int dist[],int collected[]) {
	int mindist=10000, minv;
	for (int i = 0; i < Graph->nv; i++) {
		if (collected[i]==0&&dist[i] < mindist)
		{
			mindist = dist[i];
			minv = i;
		}
	}
	if (mindist < 10000)return minv;
	else return -1;
}
bool Dijkstra(MGraph Graph,int dist[],int path[],int s) {
	int collected[1000];
	int v;
	/*初始化dist,path*/
	for (int i = 0; i < Graph->nv; i++) {
		dist[i] = Graph->G[s][i];
		if (Graph->G[s][i] < 10000)
			path[i] = s;
		else path[i] = -1;
		collected[i] = 0;
	}
	/*收录s点*/
	dist[s] = 0;
	collected[s] = 1;
	while (1) {
		/*v=未收录点中权重最小的值*/
		v = findMinDist(Graph,dist,collected);
		if (v == -1)break;
		collected[v] = 1;
		for (int i = 0; i < Graph->nv; i++) {
			if (Graph->G[v][i] < 0)return false;
			if (collected[i] != 1 && Graph->G[v][i] < 10000) {
				if (dist[v] + Graph->G[v][i] < dist[i]) {
					dist[i] = dist[v] + Graph->G[v][i];
					path[i] = v;
				}
			}
		}
	}
	return true;
}
int main() {
	int s, x, dist[1000],path[1000],A[1000];
	int index;
	Stack t = makeempty();
	MGraph Graph = build();
	scanf_s("%d %d", &s, &x);
	if (Dijkstra(Graph, dist, path,s)) {
		index = x;
		while (path[index] != -1) {
			push(t,path[index]);
			index = path[index];
		}
		while (t->Next) {
			printf("%d ", pop(t));
		}
		printf("%d\n", x);
	}




}