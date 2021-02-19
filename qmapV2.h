#pragma once

#include "QStacker/exceptionv2.h"
#include <QMap>

class MissingKeyEX : public ExceptionV2 {
      public:
	MissingKeyEX(const QString& _msg)
	    : ExceptionV2(_msg, 6) {
		forcePrint = true;
	}
};

template <class Key, class T>
class QMapV2 : public QMap<Key, T> {
      public:
	/**
	 * use like
	 * QMap x
	 * if( auto v = x.fetch(); v){
	 *	ok present
	 * res = *v.value();
	 * }else{
	 *	missing
	 * }
	 */
	[[nodiscard]] auto fetch(const Key& key) const {
		struct OK {
			operator bool() const {
				return present;
			}
			const T* value   = nullptr;
			bool     present = false;
		};
		auto iter = this->find(key);
		if (iter == this->end()) {
			return OK();
		} else {
			return OK{&iter.value(), true};
		}
	}

	void get(const Key& key, T& val) const {
		getReal(key, val);
	}

	bool get(const Key& key, T& val, const T& def) const {
		return getReal(key, val, &def);
	}

	bool getReal(const Key& key, T& val, const T* def = nullptr) const {
		if (auto v = this->fetch(key); v) {
			val = *v.value;
			return true;
		} else {
			if (def) {
				val = *def;
				return false;
			} else {
				throw MissingKeyEX(QString("no key > %1 < and missing default value, what should I do ?").arg(QString(key)));
			}
		}
	}

	T get(const Key& key, const T& def) const {
		T v;
		getReal(key, v, &def);
		return v;
	}

	T get(const Key& key) const {
		T v;
		getReal(key, v);
		return v;
	}
};
