#pragma once
#include <iostream>
#include <vector>
#include "Debug.h"
#include "SafeArray.h"

namespace SpaRcle {
	namespace Helper {
		class EventsManager {
		public:
			enum class Event {
				None, Exit, Error
			};
		private:
			inline static SafeArray<Event>		m_events		= SafeArray<Event>();
			inline static unsigned long			m_count_events = 0;
		private:
			EventsManager()  { };
			~EventsManager() { };
		public:
			static void PushEvent(Event _event) {
				EventsManager::m_count_events++;
				EventsManager::m_events.Add(_event);
			}
			static Event PopEvent() {
				if (m_count_events > 0) {
					try {
						Event ev = m_events[m_count_events - 1];

						EventsManager::m_count_events--;
						m_events.RemoveBack();

						return ev;
					}
					catch (...) {
						Debug::Error("EventsManager::PopEvent() : unknown error!");
						return Event::None;
					}
				}
				else return Event::None;
			};
		};
	}
}

