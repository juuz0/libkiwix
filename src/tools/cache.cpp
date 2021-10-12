/*
 * Copyright 2021 Maneesh P M <manu.pm55@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <list>
#include <unordered_map>
#include <assert.h>

template <typename Key_t, typename Value_t>
class LRUCache {
  typedef typename std::pair<Key_t, Value_t> Key_Value_pair_t;
  typedef typename std::list<Key_Value_pair_t>::iterator list_iterator_t;

  public: // Methods
    explicit LRUCache(unsigned int size)
    : m_size(size)
    {}

    bool exist(const Key_t& k) {
      return m_map.find(k) != m_map.end();
    }

    Value_t get(const Key_t& k) {
      assert(exist(k));

      auto it = m_map.find(k);
      m_list.splice(m_list.begin(), m_list, it->second);
      return it->second->second;
    }

    void put(const Key_t& k, const Value_t& v) {
      auto it = m_map.find(k);
      if (it != m_map.end()) {
        m_list.erase(it->second);
        m_map.erase(it);
      }
      m_list.push_front(std::make_pair(k, v));
      m_map[k] = m_list.begin();
      clean();
    }

  private:  // Methods
    void clean() {
      while (m_map.size() > m_size) {
        auto it = m_list.back();
        m_map.erase(it.first);
        m_list.pop_back();
      }
    }

	private:  // Data
    std::unordered_map<Key_t, list_iterator_t> m_map;
    std::list<Key_Value_pair_t> m_list;
    unsigned int m_size;
};