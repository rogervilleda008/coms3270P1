typedef struct edge edge_t;
typedef struct node node_t;
struct edge
{
node_t* toNode;
float weight;
void* data; // Pointer to additional edge data
edge_t* next; // Pointer to the next edge in the adjacency list
};
struct node
{
int id;
void* data; // Pointer to additional node data
edge_t* edges; // Pointer to the head of the adjacency list
};
typedef struct
{
node_t** nodes; // Array of pointers to nodes
int nodeCount;
int edgeCount;
int nodeSpace; // Current allocated space for nodes

/**
* Creates a new graph and returns a pointer to it. T
* The graph is initialized with no nodes or edges,
* and returns NULL if memory allocation fails.
* All elements of the graph are stored on the heap.
* The node’s adjacency list is a simple single linked list
* The pointers to all the nodes in the graph are stored in
* an array of pointers. These array is initialized to an
* initial capacity of 100 nodes. If more nodes are added,
* it behaves like an ArrayList in Java, where if the list is
* full, the list of node pointers is expanded to double its size
* and then a new node pointer is added.
**/
graph_t* createGraph();
/**
* Frees the memory used by the graph.
* All nodes and edges in the graph are also freed.
* If the graph pointer is NULL, the function does nothing.
**/
void freeGraph(graph_t* graph);
/**
* Adds a new node to the graph.
* @param graph Pointer to the graph.
* @param id Unique identifier for the new node.
* @param data Pointer to additional node data.
* @return Pointer to the newly created node, or NULL on failure.
**/
node_t* addNode(graph_t* graph, int id, void* data);
/**
* Adds a new edge to the graph.
* @param graph Pointer to the graph.
* @param fromId ID of the source node.
* @param toId ID of the destination node.
* @param weight Weight of the edge.
* @param data Pointer to additional edge data.
* @return Pointer to the newly created edge, or NULL on failure.
* The function fails if either node does not exist or if an edge already
* exists between the two nodes.
* All edges are directed from the source node to the destination node.
* **/
edge_t* addEdge(graph_t* graph, int fromId, int toId, float weight, void*
data);

/**
* Retrieves a node from the graph by its ID.
* @param graph Pointer to the graph.
* @param id ID of the node to retrieve.
* @return Pointer to the node, or NULL if not found.
* **/
node_t* getNode(graph_t* graph, int id);
/**
* Retrieves an edge from the graph by its source and destination node IDs.
* @param graph Pointer to the graph.
* @param fromId ID of the source node.
* @param toId ID of the destination node.
* @return Pointer to the edge, or NULL if not found.
**/
edge_t* getEdge(graph_t* graph, int fromId, int toId);
/**
* Removes a node from the graph.
* @param graph Pointer to the graph.
* @param id ID of the node to remove.
* @return 1 if the node was removed successfully, 0 if not found.
**/
int removeNode(graph_t* graph, int id);
/**
* Removes an edge from the graph.
* @param graph Pointer to the graph.
* @param fromId ID of the source node.
* @param toId ID of the destination node.
* @return 1 if the edge was removed successfully, 0 if not found.
**/
int removeEdge(graph_t* graph, int fromId, int toId);

/**
* Prints the entire graph to the console.
* @param graph Pointer to the graph.
* The function prints each node and its outgoing edges in a readable format.
* If the graph pointer is NULL, the function does nothing.
*
* Example output:
* Node 1: (data)
* -> Node 2 (weight: 1.0, data)
* -> Node 3 (weight: 2.5, data)
* Node 2: (data)
* -> Node 3 (weight: 1.5, data)
* Node 3: (data)
* (no outgoing edges)
*
**/
void printGraph(graph_t* graph);
