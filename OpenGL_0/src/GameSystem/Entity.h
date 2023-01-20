#pragma once
#include "Model3D.h"
#include <iostream>
#include <memory>
#include <unordered_map>

class Entity
{

public:
	using id_t = unsigned int;
	//using Map = std::unordered_map<id_t, Entity>;

	static Entity createAppObject(int texture_id)
	{
		static id_t currentId = 0;
		return Entity{ currentId++, texture_id };
	}

	Entity(id_t objId, int texture_id) : id{ objId }, texture_id{ texture_id } {}
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	const id_t getId() { return id; }
	std::unique_ptr<Model3D> model{};

	inline int get_texture() { return texture_id; }
	inline void set_texture(int texture) { texture_id = texture; }

	glm::vec3 color{};

private:

	int texture_id;
	id_t id;

};