#ifndef MEMMNGR_TEST_CASES
#define MEMMNGR_TEST_CASES


class TestCases {
private:
	void initMemMngr();

	void poolAllocDealloc();
	void stackAllocDealloc();

public:
	TestCases();
	~TestCases();

	void runTestcases();

};

#endif //MEMMNGR_TEST_CASES