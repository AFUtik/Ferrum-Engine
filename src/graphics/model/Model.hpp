#ifndef VERTEXINFO_HPP
#define VERTEXINFO_HPP

#include <vector>

class ModelManager;

class Model {
protected:
    std::vector<float> vertex_info;
    size_t vertex_size;

    friend class ModelManager;
public:
    Model(std::vector<float> vertex_info) : vertex_info(vertex_info), vertex_size(vertex_info.size()) {};
};

#endif