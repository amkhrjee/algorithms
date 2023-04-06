#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using std::cerr;
using std::cout;
using std::endl;
using std::vector;

struct point
{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
};

vector<point> set_boundary(vector<point> xlist, vector<point> ylist)
{
    double l = ylist[0].y;
    double r = xlist[0].x;

    vector<point> boundary_pts;
    boundary_pts.push_back({0, l});
    double max_x_covered = 0;
    for (auto each_y : ylist)
    {
        if (each_y.x >= max_x_covered)
        {
            max_x_covered = each_y.x;
            boundary_pts.push_back(each_y);
        }
    }

    boundary_pts.push_back({r, 0});

    return boundary_pts;
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
    vector<point> pts_list = get_data_from_file("randpts.txt");
    vector<point> sorted_wrt_x = pts_list;
    vector<point> sorted_wrt_y = pts_list;

    sort(sorted_wrt_x.begin(), sorted_wrt_x.end(),
         [](point p_1, point p_2)
         { return p_1.x > p_2.x; });

    sort(sorted_wrt_y.begin(), sorted_wrt_y.end(),
         [](point p_1, point p_2)
         { return p_1.y > p_2.y; });

    vector<point> boundary_pts = set_boundary(sorted_wrt_x, sorted_wrt_y);
    for (auto p : boundary_pts)
    {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
}