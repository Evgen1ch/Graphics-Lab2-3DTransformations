#pragma once
#include <cstdint>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh
{
public:
	std::vector<Vertex>			vertices;
	std::vector<uint32_t>		indices;
	std::vector<Texture>		textures;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
	void Draw(Shader& shader) const;
private:
	uint32_t VAO{};
	uint32_t VBO{};
	uint32_t EBO{};

	void setupMesh();
};

