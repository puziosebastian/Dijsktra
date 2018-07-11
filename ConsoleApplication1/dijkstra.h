#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "LinkedList.h"
#include "Heap.h"
#include "Graph.h"
#include <stdio.h>

int dijkstra(int n, LinkedList<Edge*>* graph, MinHeap &heap, int from, Path ** p, int * entrance) {
	Path * previous = new Path[n];

	int src;
	int i = 0;
	int * weights = heap.get_weights();
	heap.insert(from, 0);

	while (!heap.empty()) {
		src = heap.get_min();
		graph[src].reset_cursor();
		for (Edge ** e = graph[src].next(); e; e = graph[src].next()) {
			if (weights[(*e)->dest] > weights[src] + (*e)->weight) {
				entrance[(*e)->dest] = src; 
				heap.replace((*e)->dest, weights[src] + (*e)->weight);
				previous[(*e)->dest].i = src;
				previous[(*e)->dest].e = (*e);
			}
		}
	}

	*p = previous;
	return weights[n - 1];
}

int dijkstra(int n, LinkedList<Edge*>* graph, MinHeap &heap, int from, int * entrance) {
	int src;
	int * weights = heap.get_weights();
	heap.insert(from, 0);

	while (!heap.empty()) {
		src = heap.get_min();
		graph[src].reset_cursor();
		for (Edge ** e = graph[src].next(); e; e = graph[src].next()) {
			if ((*e)->exists && weights[(*e)->dest] > weights[src] + (*e)->weight) {
				entrance[(*e)->dest] = src;
				heap.replace((*e)->dest, weights[src] + (*e)->weight);
			}
		}
	}
	
	return weights[n - 1]; 
}

int second(int n, LinkedList<Edge *>* graph, int * weights1, int * weights2, int * entrance1, int * entrance2) {
	int min = MAX_INT, len, next = 0, prev = 0;
	for (int i = 0; i != n - 1; i = next) {
		graph[i].reset_cursor();
		for (Edge ** e = graph[i].next(); e; e = graph[i].next()) {
			if ((*e)->exists) {
				if (entrance1[(*e)->dest] != entrance2[(*e)->dest]) {
					len = weights1[i] + (*e)->weight + weights2[(*e)->dest];
					if (len < min) min = len;
				}
			}

			else if ((*e)->dest != prev) next = (*e)->dest;
		}
		prev = i;
	}

	return min;
}

#endif //DIJKSTRA_H


