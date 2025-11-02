City Road Mapper Project
Parts A, B, and C

Overview
This project implements a city mapping and data analysis tool in C.
It reads city location and road data from a tab-separated file, stores it in a graph data structure, and provides various operations such as finding coordinates, computing distances, and determining shortest road routes using Dijkstra’s algorithm.

Part A — Graph Structure

Description:

Implements the basic graph data structure using adjacency lists.

Supports nodes (locations) and edges (roads).

Can load data from a .tsv file containing city and road information.

Key Features:

Reads tab-separated input files.

Stores city names, latitude, longitude, and connected roads.

Prints all nodes and their connections for verification.

Example Output:
Node 1: Library
-> Node 2 (Café) distance 120.50 road: Main St
-> Node 3 (Bookstore) distance 340.00 road: College Ave

Part B — Mapper Utility

Description:

Implements the "mapper" program that uses the graph to analyze or visualize connections.

Extends the data structure from Part A to allow efficient lookup of nodes by name.

Key Features:

Parses location data and road data into memory.

Verifies connections between points of interest.

Prepares the foundation for advanced queries in Part C.

Example Output:
Node 1: Atanasoff Hall (42.0403, -93.6317)
-> Node 2 (Kildee Hall) distance 1048.43 road: Union Drive

Part C — City Data Analyzer (citydata)

Description:
Implements a command-line tool, "citydata", which performs computations and lookups on the loaded graph data.

Command-Line Options:
-f <filename> Specifies the city data file to load (required)
-location <name> Prints latitude and longitude of a location
-diameter Finds the two farthest locations (as the crow flies)
-distance <name1> <name2> Prints the straight-line distance in meters
-roaddist <name1> <name2> Prints the shortest road distance using Dijkstra’s algorithm
(no arguments) Displays a usage statement listing all options

Example Usage:
./citydata -f data.tsv -location "Atanasoff Hall"
42.0403 -93.6317

./citydata -f data.tsv -distance "Atanasoff Hall" "Kildee Hall"
1048.432

./citydata -f data.tsv -roaddist "Ames Highschool" "Coffee Place"
20343.342

Build Instructions

Compilation:
make

This will produce:

mapper (builds and verifies the graph)

citydata (performs queries and analysis)

Clean:
make clean

File Structure
Makefile
data.h
data.c
mapper.c
citydata.c
README.md

Algorithms Used

Graph Representation: Adjacency list

Distance Calculation: Haversine formula (latitude/longitude to meters)

Shortest Path: Dijkstra’s Algorithm

Data Input: TSV parsing and dynamic memory management

Git Tag
Once Part C is complete, tag your repository version as:
git tag mapperCcomplete
git push origin mapperCcomplete

Notes

All distances are in meters.

Input files are tab-separated (.tsv).

Quoted names in command-line arguments (e.g., "Atanasoff Hall") are treated as single parameters.

Missing files or invalid options will trigger a usage message.