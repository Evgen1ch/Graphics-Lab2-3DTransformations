#include "Mesh.h"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures)
	:vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures))
{
	setupMesh();
}

void Mesh::Draw(Shader& shader) const
{
	uint32_t diffuseNr = 1;
	uint32_t specularNr = 1;
	//we assume that all diffuse textures are named as 'texture_diffuseN', where N is texture number. Same to specular textures('texture_specularN')
	for (uint32_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); //activate proper texture unit. we assume that we have less than 16 textures
		string number;
		string name = textures[i].Type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setInt("material." + name.append(number), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].Id);
	}
	glActiveTexture(GL_TEXTURE0);
	
	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof Vertex, vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	//vertex position vector
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	//vertex normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
	//vertex color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

	glBindVertexArray(0);
}
