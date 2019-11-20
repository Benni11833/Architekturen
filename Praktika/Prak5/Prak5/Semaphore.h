#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

int threadCountWeilLambdaDumm;

class Semaphore{

private:
    int maxThreadCount;
	std::mutex sem_mutex;
	std::condition_variable cv;

public:
    Semaphore(int maxThreadCount){
        this->maxThreadCount = maxThreadCount;
		threadCountWeilLambdaDumm = this->maxThreadCount;
    }
    void darfIch(){
        std::unique_lock<std::mutex> lk(sem_mutex);
		//std::cout << "threadCountWeilLambdaDumm= " << threadCountWeilLambdaDumm << std::endl;
		if(!this->maxThreadCount)
			cv.wait(lk);

        --maxThreadCount;
		//--threadCountWeilLambdaDumm;
		std::cout << "Darfst..., noch " << this->maxThreadCount << "Threads\n";
        return;
    }
    void fertig(){
		std::cout << "Fertig...\n";
        maxThreadCount++;
		//threadCountWeilLambdaDumm++;
        cv.notify_one();
    }

};