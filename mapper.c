#include <stdio.h>
#include <string.h>
#include "data.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file.tsv\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *f = freopen(argv[i], "r", stdin);
        if (!f) {
            perror(argv[i]);
            continue;
        }

        char *res = validate();
        printf("%s: %s\n", argv[i], res);
    }

    return 0;
}
