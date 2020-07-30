#pragma once

#include <QMap>

template <class Key, class T>
class QMapV2 : public QMap<Key, T> {
      public:
	void get(const Key& key, T& val) {
		getReal(key, val);
	}

	bool get(const Key& key, T& val, const T& def) {
		return getReal(key, val, &def);
	}

	bool getReal(const Key& key, T& val, const T* def = nullptr) {
		auto iter = this->find(key);
		if (iter == this->end()) {
			if (def) {
				val = *def;
				return false;
			} else {
				throw QString("no key > %1 < and missing default value, what should I do ?").arg(QString(key));
			}
		}
		val = iter.value();
		return true;
	}

	T get(const Key& key, const T& def) {
		T v;
		getReal(key, v, &def);
		return v;
	}

	T get(const Key& key) {
		T v;
		getReal(key, v);
		return v;
	}
};
