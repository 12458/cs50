#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[]) {
    int image_count = 0;
    if (argc != 2) {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file) {
        return 1;
    }

    // printf("RAW FILE OPENED\n");

    FILE *cur = NULL;

    BYTE buf[512];

    // printf("WHILE LOOP\n");
    int found = 0;
    while (fread(buf, 1, BLOCK_SIZE, file) == BLOCK_SIZE) {
        // printf("IMAGE_COUNT: %i\n", image_count);
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff) {
            // printf("JPG FOUND\n");
            if (found) {
                fclose(cur);
            }
            found = 1;
            char filename[8];
            sprintf(filename, "%03d.jpg", image_count);
            ++image_count;
            // printf("FILENAME: %s\n", filename);
            cur = fopen(filename, "w");
            fwrite(buf, BLOCK_SIZE, 1, cur);
        } else {
            if (found) {
                fwrite(buf, BLOCK_SIZE, 1, cur);
            }
        }
    }

    fclose(cur);
    fclose(file);
    return 0;
}