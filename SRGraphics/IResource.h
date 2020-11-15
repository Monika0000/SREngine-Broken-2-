#pragma once
#include <windows.h>
#include <string>

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;
		class IResource {
			friend class ResourceManager;
		protected:
			IResource(const char* name, unsigned short CountPossibleUses) : m_CountUses(CountPossibleUses), m_res_name(name) {

			};
			~IResource() {
				
			}
		protected:
			bool				m_isDestroy		= false;
			const char*			m_res_name		= "Unknown";
			/* use only from resource manager */
			std::string			m_res_id		= "NoId";
		private:
			/*
				example:
					render:			+ 1
					video player:	+ 1
					engine:			+ 1
				if (count uses == 0 and isDestroy == true) => delete pointer
			*/
			size_t		m_CountUses		= 0;
		public:
			virtual bool Destroy() = 0;
		public:
			const char* GetResourceName() const noexcept { return m_res_name; }
			const std::string GetResourceID() const noexcept { return m_res_id; }
			void RemoveUsePoint() {
				if (m_CountUses > 0)
					m_CountUses--;
				else
					Sleep(1);
			}
			void AddUsePoint() {
				m_CountUses++;
			}
			size_t GetCountUses() const noexcept { return m_CountUses; };
		};
	}
}