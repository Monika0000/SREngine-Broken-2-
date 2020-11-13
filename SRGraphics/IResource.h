#pragma once
#include <windows.h>

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;
		class IResource {
			friend class ResourceManager;
		protected:
			IResource(const char* name, unsigned short CountPossibleUses) : m_CountPossibleUses(CountPossibleUses), m_name(name) {

			};
		protected:
			bool				m_isDestroy = false;
		private:
			/*
				example:
					render:			+ 1
					video player:	+ 1
					engine:			+ 1
				if (count uses == 0 and isDestroy == true) => delete pointer
			*/
			unsigned short		m_CountPossibleUses		= 0;
			const char*			m_name					= "Unknown";
		public:
			virtual bool Destroy() = 0;
		public:
			const char* Name() const noexcept { return m_name; }
			void RemoveUsePoint() {
				if (m_CountPossibleUses > 0)
					m_CountPossibleUses--;
				else
					Sleep(1);
			}
		};
	}
}