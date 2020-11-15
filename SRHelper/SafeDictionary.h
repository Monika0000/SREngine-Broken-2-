#pragma once
#include <iostream>
#include <map>
#include <mutex>
#include <cassert>

namespace SpaRcle {
    namespace Helper {
        template <typename K, typename T>
        class SafeDictionary {
            std::mutex      m_lock;
            std::map<K, T>  m_elements;
            size_t          m_size = 0;
        public:
            T& operator[](K key)
            {
                m_lock.lock();
                T& val = m_elements[key];
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
            void Remove(K key) {
                m_lock.lock();
                m_elements.erase(key);
                m_size--;
                m_lock.unlock();
            }

            void Add(K key, T element) {
                m_lock.lock();
                m_elements.insert(std::make_pair(key, element));
                m_size++;
                m_lock.unlock();
            }

            /*T* Find(K key) {
                m_lock.lock();
                auto find = m_elements.find(key);
                T* res = nullptr;
                if (find != m_elements.end())
                    res = &find->second;
                m_lock.unlock();
                return res;
            }*/

            /* T* Find(K key) {
                m_lock.lock();
                typename std::map<K, T>::iterator it = m_elements.find(key);
                //T* res = &it->second;
                //if (it != m_elements.end()) {
                //    res = &it->second;
                //}
                m_lock.unlock();
                return nullptr;
            }*/

            void ForEach(std::function<bool(T&)> action) {
                m_lock.lock();
                auto it = m_elements.begin();
                for (it; it != m_elements.end(); it++)
                {
                    if (action(it->second))
                        break;
                }
                m_lock.unlock();
            }
        };
    }
}

