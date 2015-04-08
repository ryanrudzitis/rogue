#include "filein.h"
#include "dbg.h"

FILE *openFile(char *file, char *mode) {
    FILE *fp = malloc(sizeof(FILE));

    fp = fopen(file, mode);

    check(fp, "Could not open %s", file);

    return fp;

error:
    exit(0);
}
