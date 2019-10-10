#include "..\rt.h"

CMutex M("MyMutex"); // global mutex created with inital value 1, meaning resource free

/*
	Problem: Parent and child thread both trying to access console at once to move cursor
	Solution 2: Use mutex semaphore
	Spinlock: Wait for resource to be free so another program can access
	Indefinite lockout: Forget to free resource
*/

UINT __stdcall thread1(void* args) {
	cout << "Hello from mutex child thread!" << endl;

	M.Wait();
	for (int i = 0; i < 1000; i++) {
		MOVE_CURSOR(40, 40);
		cout.flush();
	}
	M.Signal();

	return 0;
}

int main(void) {
	CThread t1(thread1, ACTIVE, nullptr);

	cout << "Hello from mutex main thread!" << endl;
	M.Wait();
	for (int i = 0; i < 1000; i++) {
		MOVE_CURSOR(10, 10);
		cout.flush(); // force output to be written to screen
	}
	M.Signal();

	getchar();
	t1.WaitForThread();
	return 0;
}