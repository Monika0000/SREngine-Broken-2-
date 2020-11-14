#pragma once
#include <windows.h>
#include <string>

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;
		class IResource {
			friend class ResourceManager;
		protected:
			IResource(const char* name, unsigned short CountPossibleUses) : m_CountPossibleUses(CountPossibleUses), m_res_name(name) {

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
			unsigned short		m_CountPossibleUses		= 0;
		public:
			virtual bool Destroy() = 0;
		public:
			const char* GetResourceName() const noexcept { return m_res_name; }
			const std::string GetResourceID() const noexcept { return m_res_id; }
			void RemoveUsePoint() {
				if (m_CountPossibleUses > 0)
					m_CountPossibleUses--;
				else
					Sleep(1);
			}
		};
	}
}