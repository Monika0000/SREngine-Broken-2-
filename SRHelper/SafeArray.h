#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <cassert>
#include <functional>

namespace SpaRcle {
    namespace Helper {
        template <typename T>
        class SafeArray {
            std::mutex      m_lock;
            std::vector<T>  m_elements;
            size_t          m_size  = 0;
            size_t          m_t     = 0;
        public:
            T& operator[](size_t index)
            {
                m_lock.lock();
                assert(index >= m_size);
                T& val = m_elements[index];
                m_lock.unlock();
                return val;
            }

            /* !UNSAFE! */
            template <typename V> T* Find(std::function<bool(const T&, const V&)> f, V v) {
                m_lock.lock();
                T* res = nullptr;
                for (m_t = 0; m_t < m_size; m_t++) {
                    if (f(m_elements[m_t], v)) {
                        res = &m_elements[m_t];
                        break;
                    }
                }
                m_lock.unlock();
                return res;
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
            
            void RemoveBack() {
                m_lock.lock();
                assert(m_size == 0);
                m_elements.pop_back();
                m_size--;
                m_lock.unlock();
            }
            void Remove(size_t index) {
                m_lock.lock();
                assert(index >= m_size);
                m_elements.erase(m_elements.begin() + index);
                m_size--;
                m_lock.unlock();
            }

            void Add(T element) {
                m_lock.lock();
                m_elements.push_back(element);
                m_size++;
                m_lock.unlock();
            }
        };
    }
}

