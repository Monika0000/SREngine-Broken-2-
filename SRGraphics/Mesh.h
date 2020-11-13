#pragma once
#include "IResource.h"

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;

		class Mesh : public IResource {
			friend class ResourceManager;
		public:
			Mesh();
		public:
			bool Destroy() override;
		private:

		};
	}
}

