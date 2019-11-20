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

void testF(Semaphore& s, int i) {
	s.darfIch();

	std::cout << "In testF -> i=" << i << std::endl;
	for (int i = 0; i < 9999999999999; i++)
		//std::cout << "testF->i=" << i << " ";
		;
	std::cout << "Ende testF -> i=" << i << std::endl;
	s.fertig();
}



int main() {

	std::vector<std::thread> threads;

	threads.push_back(std::thread(writeSmallAlphabet));
	
	threads.push_back(std::thread(writeNatNumbers));

	threads.push_back(std::thread(writeLargeAlphabet));

	//std::for_each(threads.begin(), threads.end(), [](std::thread t) {t.join(); });
	for (auto i = 0; i < threads.size(); i++)
		threads.at(i).join();

	/*Semaphore s1{3};
	for (int i = 0; i < 13; i++)
		testF(s1, i);*/

	std::cin.get();
	return 0;
}