#pragma once
#include <SRString.h>
#include <glm/glm.hpp>

namespace SpaRcle {
	namespace Helper {
		inline static glm::vec3 MakeVec3(const char* source, char chr, unsigned short start) {
			glm::vec3		position = glm::vec3();
			unsigned char   found_floats = 0;

			unsigned short	count = 0;
			unsigned short	found = start;

			static short t = 0;
			static short len = 0;

			len = SRString::FastStrLen(source);

			for (t = start; t < len; t++) {
				count++;

				if (t + 1 == len) {
					if (found_floats == 3)
						return position;

					char* temp = new char[count + 1]; strcpy(temp, "");

					strncat(temp, source + found, count);
					position[found_floats] = (float)atof(temp);
					found_floats++;

					delete[] temp;

					return position;
				}
				else if (source[t] == chr) {
					if (found_floats + 1 == 3)
						return position;

					char* temp = new char[count + 1]; strcpy(temp, "");

					strncat(temp, source + found, count - 1);
					position[found_floats] = (float)atof(temp);
					found_floats++;

					delete[] temp;

					found = t + 1;
					count = 0;
				}
			}
			return position;
		}
		inline static glm::vec2 MakeVec2(const char* source, char chr, unsigned short start) {
			glm::vec2		position = glm::vec3();
			unsigned char   found_floats = 0;

			unsigned short	count = 0;
			unsigned short	found = start;

			static short t = 0;
			static short len = 0;

			len = SRString::FastStrLen(source);

			for (t = start; t < len; t++) {
				count++;

				if (t + 1 == len) {
					if (found_floats == 2)
						return position;

					char* temp = new char[count + 1]; strcpy(temp, "");

					strncat(temp, source + found, count);
					position[found_floats] = (float)atof(temp);
					found_floats++;

					delete[] temp;

					//std::cout << ">>" << temp << "<<" << std::endl;
					return position;
				}
				else if (source[t] == chr) {
					if (found_floats == 2) //if (found_floats + 1 == 2) - bug
						return position;

					char* temp = new char[count + 1]; strcpy(temp, "");

					strncat(temp, source + found, count - 1);
					position[found_floats] = (float)atof(temp);
					found_floats++;

					delete[] temp;
					//std::cout << ">>" << temp << "<<" << std::endl;

					found = t + 1;
					count = 0;
				}
			}
			return position;
		}
	}
}