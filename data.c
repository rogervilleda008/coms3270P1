#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

static char line[1024];       // buffer for reading lines
static char result[16];       // buffer to store error line as string

int is_digits(const char *s) {
    if (!s || *s == '\0') return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

char *validate(void) {
    int line_num = 0;

    // ====== Read number of POIs ======
    if (!fgets(line, sizeof(line), stdin)) { sprintf(result, "%d", line_num + 1); return result; }
    line_num++;
    int poi_count = atoi(line);
    if (poi_count <= 0) { sprintf(result, "%d", line_num); return result; }

    // ====== Process POIs ======
    for (int i = 0; i < poi_count; i++) {
        if (!fgets(line, sizeof(line), stdin)) { sprintf(result, "%d", line_num + 1); return result; }
        line_num++;

        char *id = strtok(line, "\t");
        char *name = strtok(NULL, "\t");
        char *lat_str = strtok(NULL, "\t");
        char *lon_str = strtok(NULL, "\t\n");

        if (!id || !name || !lat_str || !lon_str) { sprintf(result, "%d", line_num); return result; }
        if (!is_digits(id) || strlen(name) == 0) { sprintf(result, "%d", line_num); return result; }

        char *endptr;
        double lat = strtod(lat_str, &endptr);
        while (isspace((unsigned char)*endptr)) endptr++;
        if (*endptr != '\0') { sprintf(result, "%d", line_num); return result; }

        double lon = strtod(lon_str, &endptr);
        while (isspace((unsigned char)*endptr)) endptr++;
        if (*endptr != '\0') { sprintf(result, "%d", line_num); return result; }

        if (lat < -90.0 || lat > 90.0 || lon <= -180.0 || lon >= 180.0) {
            sprintf(result, "%d", line_num); return result;
        }
    }

    // ====== Read number of Roads ======
    if (!fgets(line, sizeof(line), stdin)) { sprintf(result, "%d", line_num + 1); return result; }
    line_num++;
    int road_count = atoi(line);
    if (road_count <= 0) { sprintf(result, "%d", line_num); return result; }

    // ====== Process Roads ======
    for (int i = 0; i < road_count; i++) {
        if (!fgets(line, sizeof(line), stdin)) { sprintf(result, "%d", line_num + 1); return result; }
        line_num++;

        char *from_id   = strtok(line, "\t");
        char *to_id     = strtok(NULL, "\t");
        char *dist_str  = strtok(NULL, "\t");
        char *lat_str   = strtok(NULL, "\t");
        char *lon_str   = strtok(NULL, "\t");
        char *road_name = strtok(NULL, "\t\n");

        if (!from_id || !to_id || !dist_str || !lat_str || !lon_str || !road_name) {
            sprintf(result, "%d", line_num); return result;
        }

        if (!is_digits(from_id) || !is_digits(to_id)) { sprintf(result, "%d", line_num); return result; }
        if (strlen(road_name) == 0) { sprintf(result, "%d", line_num); return result; }

        char *endptr;
        double lat = strtod(lat_str, &endptr);
        while (isspace((unsigned char)*endptr)) endptr++;
        if (*endptr != '\0') { sprintf(result, "%d", line_num); return result; }

        double lon = strtod(lon_str, &endptr);
        while (isspace((unsigned char)*endptr)) endptr++;
        if (*endptr != '\0') { sprintf(result, "%d", line_num); return result; }

        strtod(dist_str, &endptr);
        if (endptr == dist_str) { sprintf(result, "%d", line_num); return result; }

        if (lat < -90.0 || lat > 90.0 || lon <= -180.0 || lon >= 180.0) {
            sprintf(result, "%d", line_num); return result;
        }
    }

    return "VALID";
}
