#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do{
        height = get_int("Height: ");
    } while(height < 1 || height > 8);

    for(int row = 0; row < height; row++){
        for(int i = 0; i < height - row - 1; i++){printf(" ");}
        for(int i = 0; i < row + 1; i++){printf("#");}
        printf("  ");
        for(int i = 0; i < row + 1; i++){printf("#");}
        printf("\n");
    }
}
/*
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
*/