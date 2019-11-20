#pragma once

#include <queue>
#include <thread>
#include <mutex>

class Semaphore{
private:
	int maxThreadCount;
public:
	bool darfIch() {
		//wait();
		return maxThreadCount > 0;
	}
	void fertig() {
		maxThreadCount++;
	}
	Semaphore(int count) {
		this->maxThreadCount = count;
	}
};