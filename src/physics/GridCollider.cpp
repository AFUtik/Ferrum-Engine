#include "Collider.hpp"
#include "GridCollider.hpp"

GridCollider::GridCollider(int collider_size_x, int collider_size_y, int grid_size_x, int grid_size_y) {

}

GridCollider::~GridCollider() {
    delete []grid;
}

bool GridCollider::check_collision(double x, double y, float offset_x, float offset_y) {
    int nx = x / collider_size_x;
    int ny = y / collider_size_y;

    Collider* collider = grid[ny * grid_size_y + nx];
    if(collider==nullptr) return false;
    
    return (collider->x0 <= x && x <= collider->x1) && (collider->y0 <= y && y <= collider->y1);
}