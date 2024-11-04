#pragma once
#include <string>

#include "Mesh.h"
#include <optional>

class MeshImporter
{
public:
	//static std::optional<Mesh> importFile(const std::string& file);
	static Mesh getCube();
};

