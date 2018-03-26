#include <iostream>
#include <string>
#include <thread>

// Part 2: Passing in a functor object to a thread
class MyFunctor
{
	public:
		void operator()()
		{
			std::cout << "Functor\n";
		}
};

// Part 1: Passing in a function into a thread
//void ThreadFunction()
//{
//	std::cout << "Thread function\n";
//}

// Part 3: Passing parameters to a thread
//void ThreadFunction(std::string s)
//{
//	std::cout << "Thread function message is = " << s << std::endl;
//}

// Part 4: Passing parameters to a thread by reference
void ThreadFunction(std::string& s)
{
	std::cout << "Thread function message is = " << s << std::endl;
	s = "Harry Warner";
}

int main()
{ 
	// Part 1: Creating a thread
	//std::thread t(&ThreadFunction);

	// Part 2: Passing in a functor to a thread
	//MyFunctor functor;
	//std::thread t(MyFunctor);
	//std::thread t(MyFunctor());	// Will not compile - expression must have a class type

	// Part 3: Passing parameters to a thread
	//std::string s = "Walt Disney";
	//std::thread t(&ThreadFunction, s);

	// Part 4: Passing parameters by reference
	std::string s = "Walt Disney";
	std::thread t(&ThreadFunction, std::ref(s));

	std::cout << "Main thread message is = " << s << std::endl;

	t.join();

	return 0;
}