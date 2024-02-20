#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
} Vertex;

typedef struct {
    Vertex *v0;
    Vertex *v1;
    int weight;
} Edge;

typedef struct {
    Vertex **vertices;
    int num_vertices;
    int max_vertices;
    Edge **edges;
    int num_edges;
    int max_edges;
} Graph;

void assert_msg(bool condition, char msg[]) {
    if (!condition) {
        printf("%s\n", msg);
        exit(EXIT_FAILURE);
    }
}

Vertex *vertex_new(int value, int max_vertices) {
    Vertex *v = malloc(sizeof(Vertex));
    v->value = value;

    return v;
}

bool vertex_eq(Vertex *v0, Vertex *v1) {
    // This is safe because it is not intended for more than one vertex to have the same value.
    return v0->value == v1->value;
}

Edge *edge_new(Vertex *v0, Vertex *v1, int weight) {
    Edge *e = malloc(sizeof(Edge));
    e->weight = weight;
    e->v0 = v0;
    e->v1 = v1;

    return e;
}

// Returns true if edge is given by v0 to v1 or vice versa.
bool edge_has_indirect_link(Edge edge, Vertex *v0, Vertex *v1) {
    return (vertex_eq(edge.v0, v0) && vertex_eq(edge.v1, v1))
        || (vertex_eq(edge.v0, v1) && vertex_eq(edge.v1, v0));
}

Graph *graph_new(int max_vertices) {
    int max_edges = max_vertices * (max_vertices - 1) / 2;

    Graph *g = malloc(sizeof(Graph));
    g->vertices = malloc(max_vertices * sizeof(Vertex *));
    g->num_vertices = 0;
    g->max_vertices = max_vertices;
    g->edges = malloc(max_edges * sizeof(Edge *));
    g->num_edges = 0;
    g->max_edges = max_edges;

    return g;
}

// Returns NULL if no vertex is found.
Vertex *graph_get_vertex(Graph graph, int value) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (graph.vertices[i]->value == value)
            return graph.vertices[i];

    return NULL;
}

// Errors if it exceeds the graph's max vertices.
Vertex *graph_add_vertex(Graph *graph, int value) {
    assert_msg(graph->num_vertices < graph->max_vertices, "Cannot exceed graph's size");

    Vertex *match = graph_get_vertex(*graph, value);
    if (match != NULL)
        return match;

    Vertex *v = vertex_new(value, graph->max_vertices);
    graph->vertices[graph->num_vertices] = v;
    graph->num_vertices++;

    return v;
}

Vertex **graph_get_adjascent_vertices(Graph graph, Vertex *v) {
    Vertex **adjascents = malloc(graph.num_vertices * sizeof(Vertex *));
    int count = 0;

    for (int i = 0; i < graph.num_edges; i++) {
        Edge *e = graph.edges[i];

        if (vertex_eq(e->v0, v)) {
            adjascents[count] = e->v1;
            count++;
        } else if (vertex_eq(e->v1, v)) {
            adjascents[count] = e->v0;
            count++;
        }
    }

    return adjascents;
}

// Returns NULL if no edge between v0 and v1 is found.
Edge *graph_get_edge(Graph graph, Vertex *v0, Vertex *v1) {
    for (int i = 0; i < graph.num_edges; i++)
        if (edge_has_indirect_link(*graph.edges[i], v0, v1))
            return graph.edges[i];

    return NULL;
}

Edge *graph_add_edge(Graph *graph, Vertex *v0, Vertex *v1, int weight) {
    Edge *match = graph_get_edge(*graph, v0, v1);
    if (match != NULL)
        return match;

    Edge *e = edge_new(v0, v1, weight);
    graph->edges[graph->num_edges] = e;
    graph->num_edges++;

    return e;
}

Edge *graph_add_edge_of(Graph *graph, int val0, int val1, int weight) {
    Vertex *v0 = graph_add_vertex(graph, val0);
    Vertex *v1 = graph_add_vertex(graph, val1);

    return graph_add_edge(graph, v0, v1, weight);
}

Edge *graph_get_edge_of(Graph graph, int val0, int val1) {
    Vertex *v0 = graph_get_vertex(graph, val0);
    Vertex *v1 = graph_get_vertex(graph, val1);

    return graph_get_edge(graph, v0, v1);
}
