#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

void f1(int n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 1 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void f2(int& n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

class foo
{
public:
	void bar()
	{
		for (int i = 0; i < 5; ++i) {
			std::cout << "Thread 3 executing\n";
			++n;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	int n = 0;
};

int main()
{
	int n = 0;
	foo f;
	std::thread t1; // t1 is not a thread
	std::thread t2(f1, n + 1); // pass by value
	std::thread t3(f2, std::ref(n)); // pass by reference
	std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
	t2.join();
	t4.join();
	t5.join();
	std::cout << "Final value of n is " << n << '\n';
	std::cout << "Final value of foo::n is " << f.n << '\n';
}

/*running results
Thread 1 executing
Thread 2 executing
Thread 3 executing
Thread 1 executing
Thread 2 executing
Thread 3 executing
Thread 1 executing
Thread 3 executing
Thread 2 executing
Thread 1 executing
Thread 3 executing
Thread 2 executing
Thread 1 executing
Thread 3 executing
Thread 2 executing
Final value of n is 5
Final value of foo::n is 5
*/
