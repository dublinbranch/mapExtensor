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
			const V val;
			bool    found = false;
			operator bool() {
				return found;
			}
		};

		if (auto iter = this->find(k); iter != this->end()) {
			return Founded{iter->second, true};
		} else {
			return Founded{};
		}
	}
};
