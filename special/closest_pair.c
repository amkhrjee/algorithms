#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxchar 1024
#define num_of_pts 10
#define filename "randpts.txt"
struct point
{
    double x, y;
};
typedef struct point point;
typedef point *plist;

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

        int index = 0, is_first_line = 1;
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
                temp.x = strtod(line, &ptr);
                temp.y = strtod(ptr + 1, NULL);
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

void merge(plist pts_list, int left, int mid, int right, int flag)
{
    int i = left;
    int j = mid + 1;
    int index = 0;
    point tempArr[right - left + 1];
    while (i <= mid && j <= right)
    {
        if (flag == 0)
        {
            if (pts_list[i].x <= pts_list[j].x)
            {
                tempArr[index++] = pts_list[i++];
            }
            else if (pts_list[i].x >= pts_list[j].x)
            {
                tempArr[index++] = pts_list[j++];
            }
        }
        else if (flag == 1)
        {
            if (pts_list[i].y <= pts_list[j].y)
            {
                tempArr[index++] = pts_list[i++];
            }
            else if (pts_list[i].y >= pts_list[j].y)
            {
                tempArr[index++] = pts_list[j++];
            }
        }
    }

    while (i <= mid)
    {
        tempArr[index++] = pts_list[i++];
    }
    while (j <= right)
    {
        tempArr[index++] = pts_list[j++];
    }

    for (int i = 0; i < index; i++)
    {
        pts_list[left + i] = tempArr[i];
    }
}

void plist_sort(plist pts_list, int left, int right, int flag)
{
    if (flag == 0 || flag == 1)
    {
        if (left < right)
        {
            int mid = (left + right) / 2;
            plist_sort(pts_list, left, mid, flag);
            plist_sort(pts_list, mid + 1, right, flag);
            merge(pts_list, left, mid, right, flag);
        }
    }
    else
    {
        fprintf(stderr, "Sort error: invalid flag %d\n", flag);
        exit(1);
    }
}

int main()
{
    FILE *randf = fopen(filename, "r");
    point *list_x = malloc(sizeof(point) * num_of_pts);
    point *list_y = malloc(sizeof(point) * num_of_pts);
    read_points(randf, list_x, num_of_pts);
    // copying contents of list_x into list_y
    for (int i = 0; i < num_of_pts; i++)
    {
        list_y[i] = list_x[i];
    }

    enum sort_flag
    {
        wrt_x = 0,
        wrt_y = 1
    };

    plist_sort(list_x, 0, num_of_pts - 1, wrt_x);
    plist_sort(list_y, 0, num_of_pts - 1, wrt_y);

    for (int i = 0; i < num_of_pts; i++)
    {
        printf("(%lf, %lf)\n", list_x[i].x, list_x[i].y);
    }
    printf("=================================\n");
    for (int i = 0; i < num_of_pts; i++)
    {
        printf("(%lf, %lf)\n", list_y[i].x, list_y[i].y);
    }
}