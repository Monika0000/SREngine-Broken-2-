#pragma once
#include <glm/glm.hpp>

namespace SpaRcle {
	namespace Graph {
		struct Vertex {
			glm::vec3 position;
			glm::vec2 texCoords;
			glm::vec3 normal;
			glm::vec3 tangent;
			int boneID1;
			int boneID2;
			int boneID3;
			int boneID4;
		};
	}
}