#include <cmath>
#include <fstream>
#include <iostream>
#define num_of_comparisons 7
using namespace std;

struct point
{
    double x, y;
    point(double xval = 0, double yval = 0) : x(xval), y(yval) {}
};

struct closest_pair
{
    point p_1, p_2;
    double distance;
    closest_pair(point first = {0, 0}, point second = {0, 0}, double dist = 0) : distance(dist)
    {
        if (first.x < second.x || (first.x == second.x && first.y < second.y))
        {
            p_1 = first;
            p_2 = second;
        }
        else
        {
            p_1 = second;
            p_2 = first;
        }
    }
};

double get_dist(point p_1, point p_2)
{
    return sqrt(pow(p_1.x - p_2.x, 2) + pow(p_1.y - p_2.y, 2));
}

void merge(point *point_list, int left, int mid, int right, bool wrt_x = false)
{
    int i = left;
    int j = mid + 1;
    int index = 0;
    point tempArr[right - left + 1];
    while (i <= mid && j <= right)
    {
        if (wrt_x == true)
        {
            if (point_list[i].x <= point_list[j].x)
            {
                tempArr[index++] = point_list[i++];
            }
            else if (point_list[i].x >= point_list[j].x)
            {
                tempArr[index++] = point_list[j++];
            }
        }
        // wrt y case
        else
        {
            if (point_list[i].y <= point_list[j].y)
            {
                tempArr[index++] = point_list[i++];
            }
            else if (point_list[i].y >= point_list[j].y)
            {
                tempArr[index++] = point_list[j++];
            }
        }
    }

    while (i <= mid)
    {
        tempArr[index++] = point_list[i++];
    }
    while (j <= right)
    {
        tempArr[index++] = point_list[j++];
    }

    for (int i = 0; i < index; i++)
    {
        point_list[left + i] = tempArr[i];
    }
}

void sort_points(point *point_list, int left, int right, bool wrt_x = false, bool wrt_y = false)
{
    // sort either wrt_x or wrt_y
    if (wrt_x == true && wrt_y == true)
    {
        cerr << "Sort error: cannot sort both wrt x and y" << endl;
        exit(1);
    }
    else if (wrt_x == false && wrt_y == false)
    {
        cerr << "Sort error: one of x and y must be selected" << endl;
        exit(1);
    }
    else if (wrt_x == true)
    {
        if (left < right)
        {
            // sort wrt x
            int mid = (left + right) / 2;
            sort_points(point_list, left, mid, true, false);
            sort_points(point_list, mid + 1, right, true, false);
            merge(point_list, left, mid, right, true);
        }
    }
    else if (wrt_y == true)
    {
        if (left < right)
        {
            // sort wrt x
            int mid = (left + right) / 2;
            sort_points(point_list, left, mid, false, true);
            sort_points(point_list, mid + 1, right, false, true);
            merge(point_list, left, mid, right, false);
        }
    }
}

double get_min_dist(double v_1, double v_2)
{
    if (v_1 <= v_2)
        return v_1;
    else
        return v_2;
}

closest_pair get_closest_pair(point *x_sorted_list, point *y_sorted_list, int len)
{
    if (len == 1)
    {
        cerr << "Input Error: Only one point given" << endl;
        exit(1);
    }
    else if (len == 2)
    {
        // cout << "hello" << endl;
        return closest_pair(x_sorted_list[0],
                            x_sorted_list[1],
                            get_dist(x_sorted_list[0], x_sorted_list[1]));
    }
    else if (len == 3)
    {
        // return minimum of the three possible distances
        double dist_1 = get_dist(x_sorted_list[0], x_sorted_list[1]);
        double dist_2 = get_dist(x_sorted_list[0], x_sorted_list[2]);
        double dist_3 = get_dist(x_sorted_list[1], x_sorted_list[2]);

        double temp_min_dist = get_min_dist(dist_1, dist_2);
        temp_min_dist = get_min_dist(temp_min_dist, dist_3);

        if (dist_1 == temp_min_dist)
        {
            return closest_pair(x_sorted_list[0], x_sorted_list[1], temp_min_dist);
        }
        else if (dist_2 == temp_min_dist)
        {
            return closest_pair(x_sorted_list[0], x_sorted_list[2], temp_min_dist);
        }
        else
        {
            return closest_pair(x_sorted_list[1], x_sorted_list[2], temp_min_dist);
        }
    }
    else
    {
        double min_dist;
        closest_pair final_pair;
        point mid_point = x_sorted_list[len / 2];
        closest_pair left_closest_pair = get_closest_pair(x_sorted_list, y_sorted_list, len / 2);
        closest_pair right_closest_pair = get_closest_pair(x_sorted_list + len, y_sorted_list, len - len / 2);
        (left_closest_pair.distance <= right_closest_pair.distance)
            ? (final_pair = left_closest_pair,
               min_dist = left_closest_pair.distance)
            : (final_pair = left_closest_pair,
               min_dist = left_closest_pair.distance);

        const int list_len = sizeof(y_sorted_list) / sizeof(point);
        for (int i = 0; i < sizeof(y_sorted_list) / sizeof(point); i++)
        {
            if (y_sorted_list[i].x <= mid_point.x + min_dist && y_sorted_list[i].x >= mid_point.x - min_dist)
            {
                for (int j = 1; j <= num_of_comparisons && j < list_len; j++)
                {
                    double temp_dist = get_dist(y_sorted_list[i], y_sorted_list[i + j]);
                    if (temp_dist <= min_dist)
                    {
                        min_dist = temp_dist;
                        final_pair = {y_sorted_list[i], y_sorted_list[i + j], temp_dist};
                    }
                }
            }
        }
        return final_pair;
    }
}

point *get_data_from_file(string filename)
{
    int len;
    ifstream infile;
    infile.open(filename);
    if (infile.is_open())
    {
        point point_list[len];
        infile >> len;
        int index = 0;
        while (!infile.eof())
        {
            double x, y;
            infile >> x >> y;
            point_list[index++] = {x, y};
        }
        infile.close();
        return point_list;
    }
}
int main()
{
    const point *point_list = get_data_from_file("randpts.txt");
    int len = sizeof(point_list) / sizeof(point);
    point sorted_wrt_x[len];
    for (int i = 0; i < len; i++)
    {
        sorted_wrt_x[i] = point_list[i];
    }
    point sorted_wrt_y[len];
    for (int i = 0; i < len; i++)
    {
        sorted_wrt_y[i] = point_list[i];
    }

    sort_points(sorted_wrt_x, 0, len - 1, true, false);
    sort_points(sorted_wrt_y, 0, len - 1, false, true);

    closest_pair cp = get_closest_pair(sorted_wrt_x, sorted_wrt_y, len);

    cout << "Closest pair: p_1(" << cp.p_1.x << ", " << cp.p_1.y << "), p_2(" << cp.p_2.x << ", " << cp.p_2.y << ") d = " << cp.distance << endl;
}