#include <math.h>
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

double get_dist(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void closets_pair_brute_force(const plist xlist, point *p1, point *p2, double *dist)
{
    *dist = INFINITY;
    for (int i = 0; i < num_of_pts; i++)
    {
        for (int j = 0; i < num_of_pts; j++)
        {
            if ((xlist[i].x != xlist[j].x) && (xlist[i].y != xlist[j].y))
            {
                double temp_dist = get_dist(xlist[i], xlist[j]);
                if (*dist < temp_dist)
                {
                    *dist = temp_dist;
                    *p1 = xlist[i];
                    *p2 = xlist[j];
                }
            }
        }
    }
}

void split_list_x(plist xlist, plist x_left, plist x_right)
{
    // xlist is already sorted
    int len = (sizeof(xlist) / sizeof(point));
    int half_len = len / 2;
    // memory allocation
    x_left = malloc(sizeof(point) * half_len);
    x_right = malloc(sizeof(point) * half_len);
    // put stuff into x_left and x_right
    for (int i = 0, j = half_len; i < half_len, j < len; i++, j++)
    {
        x_left[i] = xlist[i];
        x_right[j] = xlist[j];
    }
}

void split_list_y(plist ylist, double x_mid, plist y_left, plist y_right)
{
    // ylist is already sorted
    // put things in y_left and y_right that are in x_left and x_right
    // but in the order of ylist
    int len = sizeof(ylist) / sizeof(point);
    // memory allocation
    y_left = malloc(sizeof(point) * (len / 2));
    y_right = malloc(sizeof(point) * (len / 2));
    // putting things in y_left
    int left_index, right_index;
    left_index = right_index = 0;
    for (int i = 0; i < len; i++)
    {
        if (ylist[i].x < x_mid)
        {
            y_left[left_index++] = ylist[i];
        }
        else
        {
            y_right[right_index++] = ylist[i];
        }
    }
}

void make_slab_l(const plist y_left, plist slab_l, double x_mid, double delta)
{
    slab_l = malloc(sizeof(y_left) / sizeof(point));
    int slab_index = 0;
    for (int i = 0; i < (sizeof(y_left) / sizeof(point)); i++)
    {
        if (y_left[i].x >= x_mid - delta)
        {
            slab_l[slab_index++] = y_left[i];
        }
    }
}

void make_slab_r(plist y_right, plist slab_r, double x_mid, double delta)
{
    slab_r = malloc(sizeof(y_right) / sizeof(point));
    int slab_index = 0;
    for (int i = 0; i < (sizeof(y_right) / sizeof(point)); i++)
    {
        if (y_right[i].x <= x_mid + delta)
        {
            slab_r[slab_index++] = y_right[i];
        }
    }
}

void across_pair(plist slab_l, plist slab_r, point *p1, point *p2, double *dist)
{
    // for every point in the slab_l, check next 4 points in slab_r?
    double min_dist = INFINITY;
    int len = sizeof(slab_l) / sizeof(point);
    for (int i = 0; i < len; i++)
    {
        for (int j = i; i < (i + 4); j++)
        {
            double temp_dist = get_dist(slab_l[i], slab_r[j]);
            if (temp_dist < min_dist)
            {
                min_dist = temp_dist;
                *p1 = slab_l[i];
                *p2 = slab_r[j];
            }
        }
    }
    *dist = min_dist;
}

void closest_pair(const plist xlist, const plist ylist, point *p1, point *p2, double *dist)
{
    if (num_of_pts <= 3)
    {
        closets_pair_brute_force(xlist, p1, p2, dist);
    }
    plist x_left, x_right, y_left, y_right;
    double x_mid = xlist[sizeof(xlist) / 2 - 1].x;

    split_list_x(xlist, x_left, x_right);
    split_list_y(ylist, x_mid, y_left, y_right);

    // left part
    point p1_left, p2_left;
    double d_left;
    closest_pair(x_left, y_left, &p1_left, &p2_left, &d_left);
    // right part
    point p1_right, p2_right;
    double d_right;
    closest_pair(x_right, y_right, &p1_right, &p2_right, &d_right);

    double delta;
    if (d_left < d_right)
    {
        delta = d_left;
    }
    else
    {
        delta = d_right;
    }

    plist slab_l, slab_r;

    make_slab_l(y_left, slab_l, x_mid, delta);
    make_slab_r(y_right, slab_r, x_mid, delta);

    across_pair(slab_l, slab_r, p1, p2, dist);
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

    point p1, p2;
    double dist;

    closest_pair(list_x, list_y, &p1, &p2, &dist);

    // printing logic
    if (p1.x == p2.x)
    {
        if (p1.y > p2.y)
        {
            point temp = p1;
            p1 = p2;
            p2 = temp;
        }
    }
    else if (p1.x > p2.x)
    {
        point temp = p1;
        p1 = p2;
        p2 = temp;
    }

    printf("Closetst pair: p1(%lf, %lf) p2(%lf, %lf) d = %lf", p1.x, p1.y, p2.x, p2.y, dist);
}