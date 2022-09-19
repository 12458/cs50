#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            BYTE avg = (BYTE)round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE tmp = image[i][j];
            int s_red = (int)round(.393 * tmp.rgbtRed + .769 * tmp.rgbtGreen + .189 * tmp.rgbtBlue);
            int s_green = (int)round(.349 * tmp.rgbtRed + .686 * tmp.rgbtGreen + .168 * tmp.rgbtBlue);
            int s_blue = (int)round(.272 * tmp.rgbtRed + .534 * tmp.rgbtGreen + .131 * tmp.rgbtBlue);

            image[i][j].rgbtRed = (s_red > 255) ? (255) : ((BYTE)s_red);
            image[i][j].rgbtGreen = (s_green > 255) ? (255) : ((BYTE)s_green);
            image[i][j].rgbtBlue = (s_blue > 255) ? (255) : ((BYTE)s_blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    int midpoint = width / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < midpoint; j++) {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }

    return;
}

int bt(int lb, int ub, int val) {
    if (val > lb && val < ub) {
        return val;
    }
    return -1;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }
    /*

    Box average
    Let pixel be at (i,j)
    So we need pixels:
    - (i-1, j-1)
    - (i-1, j)
    - (i-1, j+1)
    - (i, j-1)
    - (i, j)
    - (i, j+1)
    - (i+1, j-1)
    - (i+1, j)
    - (i+1, j+1)

    and average them to the new pixel value

    */

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int box_i[9] = {i - 1, i - 1, i - 1,
                            i, i, i,
                            i + 1, i + 1, i + 1};
            int box_j[9] = {j - 1, j, j + 1,
                            j - 1, j, j + 1,
                            j - 1, j, j + 1};
            for (int k = 0; k < 9; k++) {
                box_j[k] = bt(0, width - 1, box_j[k]);
                box_i[k] = bt(0, height - 1, box_i[k]);
            }
            int cum_red = 0;
            int cum_green = 0;
            int cum_blue = 0;
            int items = 0;
            for (int k = 0; k < 9; k++) {
                if (box_j[k] == -1 || box_i[k] == -1) {
                    continue;
                }
                cum_red += copy[box_i[k]][box_j[k]].rgbtRed;
                cum_green += copy[box_i[k]][box_j[k]].rgbtGreen;
                cum_blue += copy[box_i[k]][box_j[k]].rgbtBlue;
                items++;
            }
            image[i][j].rgbtRed = (BYTE)round(cum_red / items);
            image[i][j].rgbtGreen = (BYTE)round(cum_green / items);
            image[i][j].rgbtBlue = (BYTE)round(cum_blue / items);
        }
    }

    return;
}
