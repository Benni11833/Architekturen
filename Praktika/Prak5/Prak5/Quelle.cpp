#include "Semaphore.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

bool ready = false;

void writeSmallAlphabet() {
	//mtx.lock();
	for (char c = 'a'; c <= 'z'; c++)
		std::cout << c << " ";
	std::cout << std::endl;
	//mtx.unlock();
}

void writeNatNumbers() {
	//mtx.lock();
	for (int i = 0; i <= 32; i++)
		std::cout << i << " ";
	std::cout << std::endl;
	//mtx.unlock();
}

void writeLargeAlphabet() {
	//mtx.lock();
	for (char c = 'A'; c <= 'Z'; c++)
		std::cout << c << " ";
	std::cout << std::endl;
	//mtx.unlock();
}

void testF() {
	std::unique_lock<std::mutex> lk(mtx);
	cv.wait(lk, [] {return ready; });
	std::cout << "In testF\n";

	ready = false;
	lk.unlock();
	cv.notify_one();
}



void testF2() {
	s.darfIch();
	/*std::unique_lock<std::mutex> lk(mtx);
	cv.wait(lk, [] {return !ready; });
	std::cout << "In testF2\n";

	ready = true;
	lk.unlock();
	cv.notify_one();*/
}

int main() {

	/*std::vector<std::thread> threads;

	threads.push_back(std::thread(writeSmallAlphabet));
	
	threads.push_back(std::thread(writeNatNumbers));

	threads.push_back(std::thread(writeLargeAlphabet));

	//std::for_each(threads.begin(), threads.end(), [](std::thread t) {t.join(); });
	for (auto i = 0; i < threads.size(); i++)
		threads.at(i).join();*/

	std::thread testT(testF);
	std::thread testT2(testF2);

	testT.join();
	testT2.join();

	std::cin.get();
	return 0;
}