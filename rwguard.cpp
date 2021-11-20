#include "rwguard.h"
#include "QStacker/exceptionv2.h"
#include "QStacker/qstacker.h"
#include <QDebug>
#include <QString>

#define QSL(str) QStringLiteral(str)

RWGuard::RWGuard(std::shared_mutex* newMutex) {
	mutex = newMutex;
}

RWGuard::~RWGuard() {
	if (shared) {
		mutex->unlock();
	}
}

void RWGuard::setMutex(std::shared_mutex* newMutex) {
	mutex = newMutex;
}

void RWGuard::lock() {
	if (exclusive) {
		throw ExceptionV2(QSL("Already locked in exclusive mode..."));
	}
	mutex->lock();
	shared = true;
}

void RWGuard::lockShared() {
	if (shared) {
		throw ExceptionV2(QSL("Already locked in shared mode..."));
	}
	mutex->lock_shared();
	shared = true;
}

void RWGuard::unlock() {
	if (shared) {
		mutex->unlock_shared();
		shared = false;
	} else if (exclusive) {
		mutex->unlock();
		exclusive = false;
	} else {
		qCritical() << QSL("You can not UNlock a NON locked mutex...") << QStacker16Light();
	}
}
