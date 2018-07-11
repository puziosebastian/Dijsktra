#include <stdio.h>

const int MAX_INT = (1 << 31) - 1;

#include "Heap.h"
#include "Dijkstra.h"

int main() {
	LinkedList<Edge*>* graph; 
	int * enter1, *enter2;
	int n, m;

	scanf("%d %d", &n, &m);

	enter1 = new int[n];
	enter2 = new int[n];
	graph = new LinkedList<Edge*>[n];
	int src, dest, w;

	for (int i = 0; i<m; ++i) {
		scanf("%d %d %d", &src, &dest, &w);
		Edge * e = new Edge(dest, w);
		Edge * e2 = new Edge(src, w);
		e->otherSide = e2;
		e2->otherSide = e;
		graph[src].insert_first(e);
		graph[dest].insert_first(e2);
	}

	Path * path;
	int first_length, second_length;
	MinHeap heap(n);
	MinHeap heap2(n);
	first_length = dijkstra(n, graph, heap, 0, &path, enter1);
	dijkstra(n, graph, heap2, n - 1, enter2);

	for (int i = n - 1; i; i = path[i].i)
		path[i].e->disable();

	second_length = second(n, graph, heap.get_weights(), heap2.get_weights(), enter1, enter2);

	delete[] path;
	delete[] enter1;
	delete[] enter2;
	delete[] graph;

	if (first_length == MAX_INT || second_length == MAX_INT) {
		printf("#\n");
		return 0;
	}

	printf("%d %d\n", first_length, second_length);

	return 0;
}

