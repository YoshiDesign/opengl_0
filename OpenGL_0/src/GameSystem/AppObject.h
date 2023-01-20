#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "AppComponent.h"
#include "Model3D.h"

class AppObject
{

public:
	using id_t = unsigned int;
	using Map = std::unordered_map<id_t, AppObject>;

	static AppObject createAppObject(/*int texture_id*/)
	{
		static id_t currentId = 0;
		return AppObject{ currentId++ /*, texture_id*/ };
	}

	AppObject(id_t objId /*, int texture_id */) : id{objId}, texture_id{texture_id} {}

	AppObject(AppObject&&) = default;
	AppObject(const AppObject&) = delete;
	AppObject& operator=(const AppObject&) = delete;
	AppObject& operator=(AppObject&&) = default;

	inline const id_t getId() { return id; }
	inline int get_texture() { return texture_id; }
	inline void set_texture(int texture) { texture_id = texture; }

	TransformComponent transform{};
	glm::vec3 color{};
	std::unique_ptr<Model3D> model{};

private:

	int texture_id;
	id_t id;

};