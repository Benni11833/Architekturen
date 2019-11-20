#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore{
private:
    std::condition_variable cv;
    int maxThreadCount;
public:
    Semaphore(int maxThreadCount){
        this->maxThreadCount = maxThreadCount;
    }
    void darfIch(){
        std::unique_lock<std::mutex> lk(cv);
        cv.wait(lk, []{return !this->maxThreadCount;});
        --maxThreadCount;
        return;
    }
    void fertig(){
        maxThreadCount++;
        cv.notify_one();
    }
};