#pragma once
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class Model3D
{

public:

	struct Vertex {
		// These 4 items get packed into our vertex buffers
		glm::vec3 position{};		// Position of the vertex
		glm::vec3 color{};			// color at this vertex
		glm::vec3 normal{};			// surface norms
		glm::vec2 texCoord{};		// 2d texture coordinates

		// This is used with our hashing function to generate keys in our ordered map of vertices
		bool operator==(const Vertex& other) const
		{
			return position == other.position && color == other.color && normal == other.normal && texCoord == other.texCoord;
		}

	};

	// Vertex and index information to be sent to the model's vertex and index buffer memory
	// TODO Observe Builder's destructor if it's a class. Make sure it's being deallocated after createModelFromFile returns
	struct Builder {
		std::vector<Vertex> vertices{};
		std::vector<uint32_t> indices{};

		void loadModel(const std::string& filepath);
	};

	//Model3D(EngineDevice& device, const Model3D::Builder& builder);
	Model3D(std::vector<Model3D::Vertex> vertices, std::vector<uint32_t> indices);
	~Model3D();

	//Model3D(const Model3D&) = delete;
	//Model3D& operator=(const Model3D&) = delete;
	static std::unique_ptr<Model3D> createModelFromFile(const std::string& filepath);

};