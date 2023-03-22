#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxchar 1024
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
                l[index++] = temp;
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

int get_input_size(FILE *stream)
{
    if (stream != NULL)
    {
        char line[maxchar];
        fgets(line, sizeof(line), stream);
        return atoi(line);
        // don't close the file yet
    }
    else
    {
        fprintf(stderr, "File error: Couldn't open file\n");
        exit(1);
    }
}

void assign_point(point *lvalue, point *rvalue)
{
    lvalue->x = rvalue->x;
    lvalue->y = rvalue->y;
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

void closets_pair_brute_force(const plist xlist, point *p1, point *p2, double *dist, int len)
{
    *dist = INFINITY;
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            double temp_dist = get_dist(xlist[i], xlist[j]);

            if (*dist > temp_dist)
            {
                *dist = temp_dist;

                assign_point(p1, &xlist[i]);

                assign_point(p2, &xlist[j]);
            }
        }
    }
}

void split_list_x(plist xlist, plist x_left, plist x_right, int len)
{
    int index = 0;
    for (int i = 0, j = len / 2; i < len / 2, j < len; i++, j++)
    {
        assign_point(&x_left[i], &xlist[i]);
        assign_point(&x_right[index++], &xlist[j]);
    }
}

void split_list_y(plist ylist, double x_mid, plist y_left, plist y_right, int len)
{
    int left_index, right_index;
    left_index = right_index = 0;
    for (int i = 0; i < len; i++)
    {
        if (ylist[i].x <= x_mid)
        {
            assign_point(&y_left[left_index++], &ylist[i]);
        }
        else
        {
            assign_point(&y_right[right_index++], &ylist[i]);
        }
    }
}

int make_slab_l(const plist y_left, plist slab_l, double x_mid, double delta, int len)
{
    int slab_index = 0;
    for (int i = 0; i < len; i++)
    {
        if (y_left[i].x > x_mid - delta)
        {
            assign_point(&slab_l[slab_index++], &y_left[i]);
        }
    }
    return slab_index;
}

int make_slab_r(plist y_right, plist slab_r, double x_mid, double delta, int len)
{
    int slab_index = 0;
    for (int i = 0; i < len; i++)
    {
        if (y_right[i].x < x_mid + delta)
        {
            assign_point(&slab_r[slab_index++], &y_right[i]);
        }
    }
    return slab_index;
}

void across_pair(plist slab_l, plist slab_r, point *p1, point *p2, double *dist, int lslab_len, int rslab_len, double delta)
{
    double min_dist = delta;
    for (int i = 0; i < lslab_len; i++)
    {
        for (int j = 0; j < (i + 10) && (j < rslab_len); j++)
        {
            double temp_dist = get_dist(slab_l[i], slab_r[j]);

            if (temp_dist < min_dist)
            {
                min_dist = temp_dist;

                assign_point(p1, &slab_l[i]);

                assign_point(p2, &slab_r[j]);
            }
        }
    }
    *dist = min_dist;
}

void closest_pair(const plist xlist, const plist ylist, point *p1, point *p2, double *dist, int len)
{
    if (len <= 3)
    {
        closets_pair_brute_force(xlist, p1, p2, dist, len);
        return;
    }
    point x_left[len / 2], x_right[len - (len / 2)], y_left[len / 2], y_right[len - (len / 2)];
    double x_mid = xlist[(len / 2) - 1].x;

    split_list_x(xlist, x_left, x_right, len);
    split_list_y(ylist, x_mid, y_left, y_right, len);

    // left part
    point p1_left, p2_left;
    double d_left;
    closest_pair(x_left, y_left, &p1_left, &p2_left, &d_left, len / 2);
    // right part
    point p1_right, p2_right;
    double d_right;
    closest_pair(x_right, y_right, &p1_right, &p2_right, &d_right, len - len / 2);

    double delta;
    if (d_left < d_right)
    {
        delta = d_left;
        assign_point(p1, &p1_left);
        assign_point(p2, &p2_left);
    }
    else
    {
        delta = d_right;
        assign_point(p1, &p1_right);
        assign_point(p2, &p2_right);
    }

    point slab_l[len / 2], slab_r[len - len / 2];

    int l_slab_len = make_slab_l(y_left, slab_l, x_mid, delta, len / 2);
    int r_slab_len = make_slab_r(y_right, slab_r, x_mid, delta, len - len / 2);

    across_pair(slab_l, slab_r, p1, p2, dist, l_slab_len, r_slab_len, delta);
}
int main()
{
    FILE *randf = fopen(filename, "r");
    int num_of_pts = get_input_size(randf);
    point list_x[num_of_pts];
    point list_y[num_of_pts];
    read_points(randf, list_x, num_of_pts);

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

    closest_pair(list_x, list_y, &p1, &p2, &dist, num_of_pts);

    // priniting logic
    if (p1.x == p2.x)
    {
        if (p1.y > p2.y)
        {
            point temp;
            assign_point(&temp, &p1);
            assign_point(&p1, &p2);
            assign_point(&p2, &temp);
        }
    }

    printf("Closest pair: p1(%lf, %lf) p2(%lf, %lf) d = %lf\n",
           p1.x,
           p1.y,
           p2.x,
           p2.y,
           dist);
}