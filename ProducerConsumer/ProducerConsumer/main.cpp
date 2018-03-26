#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

int meal = 0;

// Consumer
void waiter(int orderNumber)
{
	std::unique_lock<std::mutex> lck(mtx);

	while (meal == 0) cv.wait(lck);

	std::cout << "Order: ";
	std::cout << orderNumber + 1 << " being take care of with ";
	std::cout << meal - 1 << " meals also ready." << std::endl;

	meal--;
}

// Producer
void makeMeal(int orderNumber)
{
	std::unique_lock<std::mutex> lck(mtx);
	meal++;

	cv.notify_one();
}

int main()
{
	std::thread chefs[10];
	std::thread waiters[10];

	// Initialize customers and chefs
	for (int order = 0; order < 10; ++order)
	{
		chefs[order] = std::thread(makeMeal, order);
		waiters[order] = std::thread(waiter, order);
	}

	// Join the threads to the main thread
	for (int order = 0; order < 10; ++order)
	{
		waiters[order].join();
		chefs[order].join();
	}

	return 0;
}