#include <cmath>
#include <vector>
#include <fstream>
#include <limits>
#include <iostream>
#include <algorithm>
#define num_of_comparisons 7

using std::cerr;
using std::cout;
using std::endl;
using std::vector;

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

closest_pair get_closest_pair(vector<point> x_sorted_list, vector<point> &y_sorted_list)
{
    if (x_sorted_list.size() == 1)
    {
        cerr << "Input Error: Only one point given" << endl;
        exit(1);
    }
    else if (x_sorted_list.size() == 2)
    {
        return closest_pair(x_sorted_list[0],
                            x_sorted_list[1],
                            get_dist(x_sorted_list[0], x_sorted_list[1]));
    }
    else if (x_sorted_list.size() == 3)
    {
        // return minimum of the three possible distances
        double dist_1 = get_dist(x_sorted_list[0], x_sorted_list[1]);
        double dist_2 = get_dist(x_sorted_list[0], x_sorted_list[2]);
        double dist_3 = get_dist(x_sorted_list[1], x_sorted_list[2]);

        double temp_min_dist = std::min(dist_1, dist_2);
        temp_min_dist = std::min(temp_min_dist, dist_3);

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
        point mid_point = x_sorted_list[x_sorted_list.size() / 2];
        closest_pair left_closest_pair = get_closest_pair(vector<point>(x_sorted_list.begin(), x_sorted_list.begin() + x_sorted_list.size() / 2),
                                                          y_sorted_list);
        closest_pair right_closest_pair = get_closest_pair(vector<point>(x_sorted_list.begin() + x_sorted_list.size() / 2, x_sorted_list.end()),
                                                           y_sorted_list);

        if (left_closest_pair.distance < right_closest_pair.distance)
        {
            final_pair = left_closest_pair;
            min_dist = left_closest_pair.distance;
        }
        else
        {
            final_pair = right_closest_pair;
            min_dist = right_closest_pair.distance;
        }

        int index = 0;
        for (auto each_point : y_sorted_list)
        {
            if (each_point.x <= mid_point.x + min_dist && each_point.x >= mid_point.x - min_dist)
            {
                for (int j = 1; j <= num_of_comparisons && (index + j) < y_sorted_list.size(); j++)
                {
                    double temp_dist = get_dist(each_point, y_sorted_list[index + j]);
                    if (temp_dist <= min_dist)
                    {
                        min_dist = temp_dist;
                        final_pair = {each_point, y_sorted_list[index + j], temp_dist};
                    }
                }
            }
            index++;
        }
        return final_pair;
    }
}

vector<point> get_data_from_file(std::string filename)
{
    std::ifstream infile;
    infile.open(filename);
    vector<point> point_list;
    if (infile.is_open())
    {
        int len; // not useful with vector
        infile >> len;
        int index = 0;
        double x, y;
        while (infile >> x >> y)
        {
            point_list.push_back({x, y});
        }
        infile.close();
    }
    return point_list;
}

int main()
{
    const vector<point> point_list = get_data_from_file("randpts.txt");
    vector<point> sorted_wrt_x = point_list;
    sort(sorted_wrt_x.begin(), sorted_wrt_x.end(), [](point p_1, point p_2)
         { return p_1.x < p_2.x; });

    vector<point> sorted_wrt_y = point_list;
    sort(sorted_wrt_y.begin(), sorted_wrt_y.end(), [](point p_1, point p_2)
         { return p_1.y < p_2.y; });

    closest_pair cp = get_closest_pair(sorted_wrt_x, sorted_wrt_y);
    // prints double upto max precision
    typedef std::numeric_limits<double> dbl;
    cout.precision(dbl::max_digits10);
    cout << "Closest pair: p_1("
         << cp.p_1.x
         << ", "
         << cp.p_1.y
         << "), p_2("
         << cp.p_2.x
         << ", "
         << cp.p_2.y
         << ") d = "
         << cp.distance << endl;
}