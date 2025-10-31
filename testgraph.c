#include "testgraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINEBUF 1024

// Utility to trim newline
static void trim_newline(char* s) {
    char* p = strchr(s, '\n');
    if (p) *p = '\0';
}

// Build the graph from TSV read from stdin
graph_t* buildGraphFromTSV() {
    char line[LINEBUF];
    int line_num = 0;

    graph_t* graph = createGraph();
    if (!graph) return NULL;

    // --- Read number of POIs ---
    if (!fgets(line, LINEBUF, stdin)) return NULL;
    line_num++;
    int poi_count = atoi(line);

    // --- Read POIs ---
    for (int i = 0; i < poi_count; i++) {
        if (!fgets(line, LINEBUF, stdin)) return NULL;
        line_num++;
        trim_newline(line);

        char* id_str = strtok(line, "\t");
        char* name = strtok(NULL, "\t");
        char* lat_str = strtok(NULL, "\t");
        char* lon_str = strtok(NULL, "\t");

        if (!id_str || !name || !lat_str || !lon_str) continue;

        int id = atoi(id_str);
        poi_data_t* pdata = malloc(sizeof(poi_data_t));
        pdata->name = strdup(name);
        pdata->lat = atof(lat_str);
        pdata->lon = atof(lon_str);

        addNode(graph, id, pdata);
    }

    // --- Read number of Roads ---
    if (!fgets(line, LINEBUF, stdin)) return graph;
    line_num++;
    int road_count = atoi(line);

    // --- Read Roads ---
    for (int i = 0; i < road_count; i++) {
        if (!fgets(line, LINEBUF, stdin)) return graph;
        line_num++;
        trim_newline(line);

        char* from_str = strtok(line, "\t");
        char* to_str = strtok(NULL, "\t");
        char* dist_str = strtok(NULL, "\t");
        char* lat_str = strtok(NULL, "\t");
        char* lon_str = strtok(NULL, "\t");
        char* road_name = strtok(NULL, "\t");

        if (!from_str || !to_str || !dist_str || !lat_str || !lon_str || !road_name) continue;

        int from_id = atoi(from_str);
        int to_id = atoi(to_str);
        float dist = atof(dist_str);

        road_data_t* rdata = malloc(sizeof(road_data_t));
        rdata->name = strdup(road_name);

        addEdge(graph, from_id, to_id, dist, rdata);
    }

    return graph;
}

// --- Print Graph to stdout, including extra data ---
void printGraphWithData(graph_t* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->nodeCount; i++) {
        node_t* n = graph->nodes[i];
        poi_data_t* pdata = (poi_data_t*) n->data;
        printf("Node %d: %s (lat: %.5f, lon: %.5f)\n",
               n->id, pdata->name, pdata->lat, pdata->lon);

        edge_t* e = n->edges;
        if (!e) {
            printf("  (no outgoing edges)\n");
        } else {
            while (e) {
                road_data_t* rdata = (road_data_t*) e->data;
                poi_data_t* toData = (poi_data_t*) e->toNode->data;
                printf("  -> Node %d (%s) distance %.2f road: %s\n",
                       e->toNode->id, toData->name, e->weight, rdata->name);
                e = e->next;
            }
        }
    }
}
