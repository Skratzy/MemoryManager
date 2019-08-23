#include "../MemoryManager.h"
#include "TestCases.h"
#include "../Defines.h"

unsigned int g_rm_megabyte = 1024 * 1024;
unsigned int g_persistentStackSize = g_rm_megabyte / 512; // 2 KB
unsigned int g_functionStackSize = g_rm_megabyte * 128; // 128 MB

void TestCases::initMemMngr() {
	std::vector<StackInstance> stackInstances;
	// Persistent stack
	stackInstances.push_back(StackInstance{ g_persistentStackSize });
	// Function stack
	stackInstances.push_back(StackInstance{ g_functionStackSize });

	std::vector<PoolInstance> poolInstances;
	unsigned int size = 64; // The size of a 4x4 matrix of floats
	unsigned int numAssignments = ARCH_BYTESIZE * 50;
	unsigned int maxSizeBytes = size * numAssignments;
	poolInstances.push_back(PoolInstance{ size, numAssignments, 4 });

	MemoryManager& memMngr = MemoryManager::getInstance();
	memMngr.init(stackInstances, poolInstances);
}

TestCases::TestCases() {
	initMemMngr();
}

TestCases::~TestCases() {}

void TestCases::runTestcases() {
	std::cout << "_____________________________________" << std::endl;
	std::cout << "Running pool alloc dealloc." << std::endl;
	poolAllocDealloc();
	std::cout << "End of pool alloc dealloc." << std::endl;
	std::cout << "_____________________________________" << std::endl;

	std::cout << "_____________________________________" << std::endl;
	std::cout << "Running stack alloc dealloc." << std::endl;
	stackAllocDealloc();
	std::cout << "End of stack alloc dealloc." << std::endl;
	std::cout << "_____________________________________" << std::endl;
}

void TestCases::poolAllocDealloc() {
	MemoryManager& memMgr = MemoryManager::getInstance();
	memMgr.cleanUp();

	std::vector<PoolInstance> pi;

	unsigned int size = 64; // The size of a 4x4 matrix of floats
	unsigned int numAssignments = ARCH_BYTESIZE * 50;
	unsigned int maxSizeBytes = size * numAssignments;
	pi.push_back(PoolInstance{ size, numAssignments, 4 });

	std::vector<StackInstance> stackInstances;
	stackInstances.push_back(StackInstance{ size * numAssignments });

	memMgr.init(stackInstances, pi);

	auto testFunc = [&numAssignments, &size]() {
		MemoryManager& memMgr = MemoryManager::getInstance();

		srand(static_cast<unsigned int>(time(0)));
		std::vector<void*> poolPointers;
		while (true) {
			// Try-catch clause to catch any overflow-throws
			try {
				// "40%" chance of allocating from the pool
				if (rand() % 10 < 4 || poolPointers.size() < numAssignments / 8) {
					poolPointers.push_back(memMgr.poolAllocate(size));
				}
				// "60%" chance of deallocating from the pool
				else {
					if (poolPointers.size() > 0) {
						unsigned int index = rand() % poolPointers.size();
						memMgr.deallocateSinglePool(poolPointers[index], size);
						std::swap(poolPointers[index], poolPointers.back());
						poolPointers.pop_back();
					}
				}
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(40));
		}

	};
	std::thread t1(testFunc);
	std::thread t2(testFunc);
	std::thread t3(testFunc);
	std::thread t4(testFunc);
	std::cout << "blah" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "blah" << std::endl;

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

void TestCases::stackAllocDealloc() {
	MemoryManager& memMgr = MemoryManager::getInstance();
	memMgr.cleanUp();

	std::vector<PoolInstance> pi;

	unsigned int size = 64; // The size of a 4x4 matrix of floats
	unsigned int numAssignments = ARCH_BYTESIZE * 50;
	unsigned int maxSizeBytes = size * numAssignments;
	pi.push_back(PoolInstance{ size, numAssignments, 4 });

	std::vector<StackInstance> stackInstances;
	stackInstances.push_back(StackInstance{ size * numAssignments });

	memMgr.init(stackInstances, pi);

	auto testFunc = [&numAssignments, &size]() {
		MemoryManager& memMgr = MemoryManager::getInstance();

		srand(static_cast<unsigned int>(time(0)));
		std::vector<void*> poolPointers;
		while (true) {
			// Try-catch clause to catch any overflow-throws
			try {
				// "90%" chance of allocating from the stack
				if (rand() % 100 < 90) {
					memMgr.stackAllocate(rand() % 256, 0);
				}
				// "10%" chance of deallocating everything from the stack
				else {
					memMgr.deallocateStack(0);
				}

			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(40));
		}

	};
	std::thread t1(testFunc);
	std::thread t2(testFunc);
	std::thread t3(testFunc);
	std::thread t4(testFunc);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
