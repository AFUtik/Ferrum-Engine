#ifndef GRIDCOLLIDER_HPP
#define GRIDCOLLIDER_HPP

class Collider;

class GridCollider {
public:
    int collider_size_x;
    int collider_size_y;
    int grid_size_x;
    int grid_size_y;
    Collider **grid;

    GridCollider(int collider_size_x, int collider_size_y, int grid_size_x, int grid_size_y);
    ~GridCollider();

    bool check_collision(double x, double y, float offset_x, float offset_y);
};

#endif