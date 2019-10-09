#include "..\rt.h"
#include <atomic>

atomic_flag flag;

/*
	Problem: Parent and child thread both trying to access console at once to move cursor
	Solution 1: Use atomic, indivisable flag which can be TAS and uninterrupted
	Spinlock: Wait for resource to be free so another program can access
	Indefinitely lockout: Forget to free resource
*/

UINT __stdcall thread1(void* args) {
	cout << "Hello from child thread!" << endl;
	for (int i = 0; i < 1000; i++) {
		while (flag.test_and_set() == true); // wait while busy
		MOVE_CURSOR(40, 40);
		cout.flush();
		flag.clear(); // clear flag
	}
	return 0;
}

int main(void) {
	flag.clear();
	CThread t1(thread1, ACTIVE, nullptr);

	cout << "Hello from main thread!" << endl;
	for (int i = 0; i < 1000; i++) {
		while (flag.test_and_set() == true);
		MOVE_CURSOR(10, 10);
		cout.flush(); // force output to be written to screen
		flag.clear();
	}
	getchar();
	t1.WaitForThread();
	return 0;
}