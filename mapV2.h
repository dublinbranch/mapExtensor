#pragma once

#include "QStacker/exceptionv2.h"
#include "fmt/core.h"
#include <map>

template <typename K, typename V>
class mapV2 : public std::map<K, V> {
      public:
	/*
	 * Use like
	map2<int, string> bla;
	bla.insert({5, "ciao"});

	if (auto f = bla.get(5)) {
		cout << f.val << "\n";
	} else {
		cout << "nada\n";
	}
	 */
	[[nodiscard]] auto get(const K& k) const {
		struct Founded {
			const V* val   = nullptr;
			bool     found = false;
			operator bool() const {
				return found;
			}
		};

		if (auto iter = this->find(k); iter != this->end()) {
			return Founded{&iter->second, true};
		} else {
			return Founded();
		}
	}

	[[nodiscard]] V getDefault(const K& k) const {
		if (auto v = this->get(k); v) {
			return v.val;
		}
		return V();
	}

	[[nodiscard]] V getDefault(const K& k, const V& v) const {
		if (auto found = this->get(k); found) {
			return found.val;
		}
		return v;
	}

	[[nodiscard]] const auto& operator[](const K& k) const {
		if (auto iter = this->find(k); iter != this->end()) {
			return iter->second;
		} else {
			throw ExceptionV2(fmt::format("key {} not found in {}", k, __PRETTY_FUNCTION__));
		}
	}
	/*
	 *For obscure reason the compiler elect to use the const version, ignoring the base class NON const one
	 * so we redefine ...
	 */
	[[nodiscard]] auto& operator[](const K& k) {
		return std::map<K, V>::operator[](k);
	}

	const V& first() const {
		return this->begin()->second;
	}
};

template <typename K, typename V>
class multiMapV2 : public std::multimap<K, V> {
      public:
	/*
	 * Use like
	map2<int, string> bla;
	bla.insert({5, "ciao"});

	if (auto f = bla.get(5)) {
		cout << f.val << "\n";
	} else {
		cout << "nada\n";
	}
	 */
	[[nodiscard]] auto get(const K& k) const {
		struct Founded {
			const V* val   = nullptr;
			bool     found = false;
			operator bool() const {
				return found;
			}
		};

		if (auto iter = this->find(k); iter != this->end()) {
			return Founded{&iter->second, true};
		} else {
			return Founded();
		}
	}
};
