#pragma once
#include <string>
#include "Debug.h"

namespace SpaRcle {
	namespace Helper {
		class FormatType {
		public:
			enum Value {
				Unknown,
				_640_360,
				_1280_720,
				_1366_768,
				_1600_900
			};

			FormatType(Value v) : value(v) {

			}
		public:
			const unsigned int Width() const noexcept {
				switch (value) {
				case FormatType::Unknown:		return 0;
				case FormatType::_640_360:		return 640;
				case FormatType::_1280_720:		return 1280;
				case FormatType::_1366_768:		return 1366;
				case FormatType::_1600_900:		return 1600;
				default: Debug::Error("FormatType::Width() : unknown type " + std::to_string((int)value) + "!"); return 0;
				}
			}
			const unsigned int Height() const noexcept {
				switch (value) {
					case FormatType::Unknown:		return 0;
					case FormatType::_640_360:		return 360;
					case FormatType::_1280_720:		return 720;
					case FormatType::_1366_768:		return 768;
					case FormatType::_1600_900:		return 900;
					default: Debug::Error("FormatType::Height() : unknown type " + std::to_string((int)value) + "!"); return 0;
				}
			}
		private:
			Value value;
		};
	}
}