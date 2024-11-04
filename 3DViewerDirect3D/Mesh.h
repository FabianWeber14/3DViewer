#pragma once
#include <vector>
#include "Vertex.h"

struct Mesh
{
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};