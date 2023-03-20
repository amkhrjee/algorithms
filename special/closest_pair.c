#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define maxchar 1024
#define num_of_pts 10
#define filename "randpts.txt"
struct point
{
    double x, y;
};
typedef struct point point;
typedef point* plist;

// // functions prescribed as must include:
// void read_points(FILE *stream, plist *l, int n);
// void closest_pair(const plist *list_x, const plist *list_y, point *p1, point *p2, double *d);
// void split_list_x(const plist *l, plist *left, plist *right);
// void split_list_y(const plist *l, const plist *x_left, const plist *x_right, plist *y_left, plist *y_right);
// void make_slab_l(const plist *list_y, plist *slab_l, double x_mid, double delta);
// void make_slab_r(const plist *list_y, plist *slab_r, double x_mid, double delta);
// void across_pair(const plist *slab_l, const plist *slab_l, point *p1, point *p2, double *d);


void read_points(FILE *stream, plist l, int n)
{
    if (stream != NULL)
    {

        int  index = 0, is_first_line = 1;
        char line[maxchar];
        while (fgets(line, sizeof(line), stream) != NULL)
        {
            if (is_first_line)
            {
                is_first_line = 0;
            }
            else
            {
                point temp;
                char *ptr;
                temp.x =  strtod(line, &ptr);
                temp.y =  strtod(ptr + 1, NULL);
                *(l + index++) = temp;
            }
        }
        fclose(stream);
    }
    else
    {
        fprintf(stderr, "File error: Couldn't open file\n");
        exit(1);
    }
}

int main()
{
    FILE *randf = fopen(filename, "r");
    point *list_x = malloc(sizeof(point)* num_of_pts);
    point *list_y = malloc(sizeof(point)* num_of_pts);
    read_points(randf, list_x, num_of_pts);
    // copying contents of list_x into list_y
    for(int i = 0; i < num_of_pts; i++)
    {
        list_y[i] = list_x[i];
    }
    
}