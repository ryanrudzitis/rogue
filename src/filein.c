#include "filein.h"
#include "dbg.h"

FILE *openFile(char *file, char *mode) {
    FILE *fp = NULL;

    fp = fopen(file, mode);

    check(fp, "Could not open %s", file);

    return fp;

error:
    exit(0);
}
