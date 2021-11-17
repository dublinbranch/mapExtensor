#include "lockguardv2.h"
#include "QStacker/exceptionv2.h"
#include <QString>

#define QSL(str) QStringLiteral(str)

LockGuardV2::LockGuardV2() {
}

void LockGuardV2::setMutex(std::mutex* newMutex) {
	mutex = newMutex;
}

void LockGuardV2::lock() {
	if (didWeLockedIt) {
		throw ExceptionV2(QSL("You can not lock a lock twice..."));
	}
	mutex->lock();
	didWeLockedIt = true;
}

bool LockGuardV2::tryLock() {
	if (didWeLockedIt) {
		throw ExceptionV2(QSL("You can not lock a lock twice..."));
	}
	if (mutex->try_lock()) {
		didWeLockedIt = true;
		return true;
	}
	return false;
}
