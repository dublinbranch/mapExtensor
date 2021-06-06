#ifndef INDEXEDVECTOR_H
#define INDEXEDVECTOR_H
#include <map>

template <class T>
concept isIterable = requires(const T& t) {
	t.begin();
	t.end();
};

template <class T>
class indexedVector {
	using innerMap = std::multimap<int, T>;

      private:
	innerMap content;

      public:
	void push_back(const T& r) {
		constexpr bool hasRty = requires() {
			r.rty;
		};
		constexpr bool hasRty_ptr = requires() {
			r->rty;
		};
		constexpr bool hasHeader = requires() {
			r.header.rty;
		};
		constexpr bool hasHeader_ptr = requires() {
			r->header.rty;
		};

		//Due to an orrible error that Roy did we now need this hack, well not entirely
		if constexpr (hasRty) {
			content.insert({r.rty, r});
		} else if constexpr (hasRty_ptr) {
			content.insert({r->rty, r});
		} else if constexpr (hasHeader) {
			content.insert({r.header.rty, r});
		} else if constexpr (hasHeader_ptr) {
			content.insert({r->header.rty, r});
		} else {
			static_assert(true, "what is that now ?");
		}
	}

	void push_back(isIterable auto& n) {
		for (auto& x : n) {
			this->push_back(x);
		}
	}

	struct Iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = size_t;
		using value_type        = T;
		using pointer           = typename innerMap::iterator; // or also value_type*
		using reference         = T&;                          // or also value_type&

		Iterator() = default;

		static Iterator dummy() {
			return Iterator();
		}
		Iterator(pointer ptr)
		    : m_ptr(ptr) {
		}
		reference operator*() const {
			return m_ptr->second;
		}
		//we hide the indexing part
		T& operator->() const {
			return m_ptr->second;
		}
		//when shared ptr are used looks like the two -> are merged ?
		T& second() const {
			return m_ptr->second;
		}

		// Prefix increment
		Iterator& operator++() {
			m_ptr++;
			return *this;
		}

		Iterator after() {
			auto tmp = *this;
			tmp++;
			return tmp;
		}

		// Postfix increment
		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}
		Iterator operator+(int count) {
			return m_ptr + count;
		}

		friend bool operator==(const Iterator& a, const Iterator& b) {
			return a.m_ptr == b.m_ptr;
		};

		friend bool operator!=(const Iterator& a, const Iterator& b) {
			return a.m_ptr != b.m_ptr;
		};

	      private:
		pointer m_ptr;
	};

	//poor man tag dispatch for concepts ?
	static bool isIndexedVector;

	bool empty() const {
		return content.empty();
	}

	Iterator begin() {
		return Iterator(content.begin());
	}
	Iterator end() {
		return Iterator(content.end());
	}
	const Iterator begin() const {
		//not sure what is going on here
		auto c = content.cbegin();
		return Iterator(c._M_const_cast());
	}
	const Iterator end() const {
		//not sure what is going on here
		return Iterator(content.cend()._M_const_cast());
	}
};

#endif // INDEXEDVECTOR_H
