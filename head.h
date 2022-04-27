#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

struct pt{
    int id;
    double x,y;
};

double dist( pt a, pt b );

class Path{
private:
    deque<pt> path;
    int num_of_nodes;

    bool last_improvement_status;
    void try_to_improve_2(int v1, int v2);

public:
    Path();
    void add_node( pt &new_node );
    double length();
    void local_search_2();
    void show_a();
    void show();
};
