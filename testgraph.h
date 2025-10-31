#ifndef TESTGRAPH_H
#define TESTGRAPH_H

#include "graph.h"

// Node extra data: POI info
typedef struct {
    char* name;     // POI name
    double lat;     // Latitude
    double lon;     // Longitude
} poi_data_t;

// Edge extra data: Road info
typedef struct {
    char* name;     // Road name
} road_data_t;

// Function to read a TSV file from stdin and build a graph
graph_t* buildGraphFromTSV();

#endif // TESTGRAPH_H
