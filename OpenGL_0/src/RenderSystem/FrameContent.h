#pragma once
#include "Camera.h"
#include "GameSystem/AppObject.h"
#include "UBO.h"
#include <vector>

struct FrameContent {
	Camera& camera;
	AppObject::Map& appObjects;
	UBO& ubo;
};

