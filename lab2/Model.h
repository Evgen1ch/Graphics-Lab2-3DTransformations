#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"


class Model
{
public:
	Model(const std::string& path);
	void Draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	string directory;
	std::vector<Texture> textures_loaded;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	uint32_t TextureFromFile(const char* path, const string& directory);
};

