#pragma once
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <Windows.h>

#define GetKeyDown(key) Input::BaseGetKeyDown(key, __FILE__, __LINE__)
#define GetKeyUp(key) Input::BaseGetKeyUp(key, __FILE__, __LINE__)
#define GetKey(key) Input::BaseGetKey(key)

enum class KeyboardLayout { EN, RU, UNKNOWN };

enum class KeyCode {
	MouseLeft = 1, MouseRight = 2, MouseMiddle = 4, BackSpace = 8, Tab = 9, Enter = 13, LShift = 16, Ctrl = 17, Alt = 18,
	Esc = 27, Space = 32, LeftArrow = 37, UpArrow = 38, RightArrow = 39, DownArrow = 40, Del = 46, A = 65, B = 66, C = 67, D = 68,
	E = 69, F = 70, I = 73, L = 76, M = 77, O = 79, P = 80, Q = 81, S = 83, R = 82, T = 84, U = 85, W = 87, Y = 89,
	Minus = 189, Dot = 190, Tilde = 192,

	_0 = 48, _1 = 49, _2 = 50, _3 = 51, _4 = 52, _5 = 53, _6 = 54, _7 = 55, _8 = 56, _9 = 57
};

class Input {
private:
	//inline static std::thread									m_task					= std::thread();
	//inline static volatile bool									m_isRun					= false;
	static std::map<const char*, std::map<int, bool>>	m_registred_calls;
private:
	Input() {

	}
	~Input() {

	}
public:
	/*
	static bool Run() {
		if (m_isRun) return false;
		else m_isRun = true;

		m_task = std::thread([] {

		});

		return true;
	}
	static void Stop() {
		if (!m_isRun)
			return;

		m_isRun = false;
		m_task.join();
	}*/
public:
	static int GetKeyPressedId();

	static bool BaseGetKey(KeyCode key);
	
	static bool BaseGetKeyDown(KeyCode key, const char* file, int line) noexcept {
		bool is_pressed = BaseGetKey(key);

		auto find_file = m_registred_calls.find(file);
		if (find_file == m_registred_calls.end())
			m_registred_calls.insert(std::make_pair(file, std::map<int, bool>()));
		auto& found_file = m_registred_calls[file];

		auto find_line = found_file.find(line);
		if (find_line == found_file.end()) {
			found_file.insert(std::make_pair(line, is_pressed));
			return is_pressed;
		}
		else {
			bool& temp = find_line->second;
			if (is_pressed && temp)
				return false;
			else if (!is_pressed && !temp)
				return false;
			else {
				temp = is_pressed;
				return is_pressed;
			}
		}
	}

	static bool BaseGetKeyUp(KeyCode key, const char* file, int line) noexcept {
		bool is_pressed = BaseGetKey(key);

		auto find_file = m_registred_calls.find(file);
		if (find_file == m_registred_calls.end())
			m_registred_calls.insert(std::make_pair(file, std::map<int, bool>()));
		auto& found_file = m_registred_calls[file];

		auto find_line = found_file.find(line);
		if (find_line == found_file.end()) {
			found_file.insert(std::make_pair(line, is_pressed));
			return is_pressed;
		}
		else {
			bool& temp = find_line->second;
			if (is_pressed && temp)
				return false;
			else if (!is_pressed && !temp)
				return false;
			else {
				temp = is_pressed;
				return !is_pressed;
			}
		}
	}
};

