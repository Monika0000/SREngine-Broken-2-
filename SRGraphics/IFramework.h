#pragma once

namespace SpaRcle {
	namespace Graph {
		class IFramework {
		protected:
			IFramework() {};
			~IFramework() {};
		protected:
			inline static volatile bool			m_isCreate = false;
			inline static volatile bool			m_isInit = false;
			inline static volatile bool			m_isRun = false;
			inline static volatile bool			m_isClose = false;
		};
	}
}