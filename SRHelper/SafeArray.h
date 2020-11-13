#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <cassert>

namespace SpaRcle {
    namespace Helper {
        template <typename T>
        class SafeArray {
            std::mutex      m_lock;
            std::vector<T>  m_elements;
            size_t          m_size = 0;
        public:
            T& operator[](size_t index)
            {
                m_lock.lock();
                assert(index >= m_size);
                T& val = m_elements[index];
                m_lock.unlock();
                return val;
            }

            void Clear() {
                m_lock.lock();
                m_elements.clear();
                m_size = 0;
                m_lock.unlock();
            }
            const size_t Size() {
                m_lock.lock();
                size_t t = m_size;
                m_lock.unlock();
                return t;
            }
            void Remove(size_t index)
            {
                m_lock.lock();
                assert(index >= m_size);
                m_elements.erase(m_elements.begin() + index);
                m_size--;
                m_lock.unlock();
            }

            void Add(T element)
            {
                m_lock.lock();
                m_elements.push_back(element);
                m_size++;
                m_lock.unlock();
            }
            /*void addrange(int num, ...)
            {
                va_list arguments;
                va_start(arguments, num);
                for (int i = 0; i < num; i++)
                {
                    _lock.lock();
                    add(va_arg(arguments, T));
                    _lock.unlock();
                }
                va_end(arguments);
            }
            void dump()
            {
                m_lock.lock();
                for (auto e : m_elements)
                    std::cout << e << std::endl;
                m_lock.unlock();
            }*/
        };
    }
}

