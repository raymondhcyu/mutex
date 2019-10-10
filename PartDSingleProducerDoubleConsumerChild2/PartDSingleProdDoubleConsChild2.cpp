#include "..\rt.h"

struct MyDataPool {
	int x;
};

struct MyDataPool* dataPoolPointer;

int main(void) {
	CSemaphore ps1("PS1", 0, 1); // semaphore w/ init value 0; max 1
	CSemaphore cs1("CS1", 1, 1); // sempahore w/ init value 1; max 1
	CSemaphore ps2("PS2", 0, 1);
	CSemaphore cs2("CS2", 1, 1);

	CDataPool dp1("MyDataPoolName", sizeof(struct MyDataPool));
	dataPoolPointer = (struct MyDataPool*)dp1.LinkDataPool(); // link datapool

	cout << "Consumer 2 is running..." << endl;

	for (int i = 0; i < 10; i++) {
		cout << "Hit return to consume data..." << endl;
		getchar();
		ps2.Wait();
		cout << "Consumed " << dataPoolPointer->x << "..." << endl;
		cs2.Signal();
	}

	getchar();
	return 0;
}