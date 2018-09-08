#include <stdlib.h>
#include <stdio.h>
#define PROP_VALUE_MAX 32
int main(int argc, char **argv) {
    char platform[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char cmdlinebuff[1024];
    char board_id[32];
    FILE *fp;
    int rc;

    if ((fp = fopen("/proc/cmdline", "r")) == NULL) {
        printf("Failed to open /proc/cmdline");
        return 1;
    }

    if (fgets(cmdlinebuff, 1024, fp) == NULL) {
        return 2;
    }
    char *boardindex = strstr(cmdlinebuff, "board_id=");
    if (boardindex != NULL) {
        printf("boardindex %s\n", boardindex);
        strncpy(board_id, strtok(boardindex+9, ":"), 32);
    } else {
        printf("%s\n", cmdlinebuff);
    }

    
    fclose(fp);
    if (board_id == NULL) {
        printf("Failed to get board_id");
    } else {
    }
    printf("Found board id: %s\n", board_id);

    return 0;
}
