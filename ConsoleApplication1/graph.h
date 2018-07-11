#ifndef GRAPH_H
#define GRAPH_H

struct Edge {
	Edge(int dest, int w) : dest(dest), weight(w), exists(true) {}

	int dest;
	int weight;
	bool exists;

	Edge * otherSide;

	void disable() {
		this->exists = false;
		this->otherSide->exists = false;
	}

	void enable() {
		this->exists = true;
		this->otherSide->exists = true;
	}
};

struct Path {
	int i;
	Edge * e;
};

#endif //GRAPH_H


