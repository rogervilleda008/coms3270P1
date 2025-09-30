#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

//Checking if a string is all integers
int is_digits(const char *s) {
    if (s == NULL || *s == '\0') return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}


int validate(void) {
    char line[1024];
    int line_num = 0;

    // ====== Read number of POIs ======
    if (!fgets(line, sizeof(line), stdin)) return 1;
    line_num++;
    int poi_count = atoi(line);
    if (poi_count <= 0) return line_num;

    // ====== Process POIs ======
    for (int i = 0; i < poi_count; i++) {
        if (!fgets(line, sizeof(line), stdin)) return line_num + 1;
        line_num++;

        // parse POI line: ID <tab> Name <tab> Lat <tab> Lon
        char *id = strtok(line, "\t");
        char *name = strtok(NULL, "\t");
        char *lat_str = strtok(NULL, "\t");
        char *lon_str = strtok(NULL, "\t\n");

        if (!id || !name || !lat_str || !lon_str) return line_num;

        // check ID
        if (!is_digits(id)) return line_num;

        // name cannot be empty
        if (strlen(name) == 0) return line_num;

        // latitude / longitude parsing
        char *endptr;
        double lat = strtod(lat_str, &endptr);
        if (*endptr != '\0' && *endptr != '\n') return line_num;
        double lon = strtod(lon_str, &endptr);
        if (*endptr != '\0' && *endptr != '\n') return line_num;

        // check ranges
        if (lat < -90.0 || lat > 90.0) return line_num;
        if (lon <= -180.0 || lon >= 180.0) return line_num;
    }

    // ====== Read number of Roads ======
    if (!fgets(line, sizeof(line), stdin)) return line_num + 1;
    line_num++;
    int road_count = atoi(line);
    if (road_count <= 0) return line_num;

    // ====== Process Roads ======
    for (int i = 0; i < road_count; i++) {
        if (!fgets(line, sizeof(line), stdin)) return line_num + 1;
        line_num++;

        // parse Road line: From <tab> To <tab> Distance <tab> Lat <tab> Lon <tab> Name
        char *from_id   = strtok(line, "\t");
        char *to_id     = strtok(NULL, "\t");
        char *dist_str  = strtok(NULL, "\t");
        char *lat_str   = strtok(NULL, "\t");
        char *lon_str   = strtok(NULL, "\t");
        char *road_name = strtok(NULL, "\t\n");

        if (!from_id || !to_id || !dist_str || !lat_str || !lon_str || !road_name) {
            return line_num;
        }

        // IDs must be digits
        if (!is_digits(from_id) || !is_digits(to_id)) return line_num;

        // road name cannot be empty
        if (strlen(road_name) == 0) return line_num;

        // latitude / longitude parsing
        char *endptr;
        double lat = strtod(lat_str, &endptr);
        if (*endptr != '\0' && *endptr != '\n') return line_num;
        double lon = strtod(lon_str, &endptr);
        if (*endptr != '\0' && *endptr != '\n') return line_num;

        // check ranges
        if (lat < -90.0 || lat > 90.0) return line_num;
        if (lon <= -180.0 || lon >= 180.0) return line_num;

        // distance may be NaN → treat as zero, but allow parse
        strtod(dist_str, &endptr);
        if (endptr == dist_str) return line_num;
    }

    // If everything is valid
    return 0;
}
