#ifndef LOCKGUARDV2_H
#define LOCKGUARDV2_H

#include <atomic>
#include <mutex>

class LockGuardV2 {
      public:
	LockGuardV2();
	LockGuardV2(std::mutex* newMutex, bool lockNow = true) {
		mutex = newMutex;
		if (lockNow) {
			lock();
		}
	}
	~LockGuardV2() {
		if (didWeLockedIt) {
			mutex->unlock();
		}
	}

	void setMutex(std::mutex* newMutex);
	void lock();
	bool tryLock();

      private:
	std::mutex* mutex = nullptr;
	//of course this is not if the MUTEX is locked, but if WE locked it (to avoid a try lock unlock... which is orrible)
	std::atomic_bool didWeLockedIt = false;
};

#endif // LOCKGUARDV2_H
