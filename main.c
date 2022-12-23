#include <stdio.h>

#define row 30
#define col 30

int next_cell(int table[row][col], int i, int j, int path[col + row][2], int *counter_p)
{
    // if the current cell is destination return true
    if (i == row - 1 && j == col - 1)
        return 1;

    if ((i + 1 < row && table[i + 1][j] == 0))
    { // if it's possible to go downwards
        i += 1;
    }
    else if (j + 1 < col && table[i][j + 1] == 0)
    { // else if it's possible to go right
        j += 1;
    }
    else if (i > 0 && table[i - 1][j] == 0)
    { // else if it's possible to go upwards
        i -= 1;
    }
    else if (j > 0 && table[i][j - 1] == 0)
    { // else if it's possible to go left
        j -= 1;
    }
    else
    { // if non of the neighbor cells is equal to 0

        // no possible way -> returned to the first cell
        if (i == 0 && j == 0)
            return 0;

        table[i][j] = 1;
        *counter_p -= 1;
        i = path[*counter_p][0];
        j = path[*counter_p][1];
        return next_cell(table, i, j, path, counter_p);
    }

    *counter_p += 1;
    path[*counter_p][0] = i;
    path[*counter_p][1] = j;
    table[i][j] = 2;
    return next_cell(table, i, j, path, counter_p);
}

int main(void)
{

    int table[row][col];

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            scanf(" %d", &(table[i][j]));
        }
    }

    // printf("_________________________\n");
    // for (int i = 0; i < row; ++i)
    // {
    //     for (int j = 0; j < col; ++j)
    //     {
    //         printf("%d ", table[i][j]);
    //         if(j == col - 1) printf("\n");
    //     }
    // }

    // path array to track the path
    int path[row * col][2];
    // the path cells count (counter)
    int counter = 0;

    // every visited (traversed) cell will be assigned to 2
    // init for the first cell (0,0)
    table[0][0] = 2;
    path[counter][0] = 0;
    path[counter][1] = 0;

    // call next cell function with arguments of table itself, position of the current cell, path array and the counter pointer
    int result = next_cell(table, 0, 0, path, &counter);

    // printing the path result
    if (result)
    {
        for (int i = 0; i < counter; i++)
        {
            printf("[%d][%d] ==> [%d][%d]\n", path[i][0], path[i][1], path[i + 1][0], path[i + 1][1]);
        }
    }
    else
    {
        printf("Impossible !");
    }

    return 1;
}