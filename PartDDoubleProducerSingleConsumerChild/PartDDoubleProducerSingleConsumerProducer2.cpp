#include "..\rt.h"

/* Producer 1 creates Producer 2 process and Consumer process*/

struct MyDataPool {
	int x;
};

struct MyDataPool* dataPoolPointer1;
struct MyDataPool* dataPoolPointer2;

int main(void) {
	CSemaphore ps1("PS1", 0, 1); // semaphore w/ init value 0; max 1
	CSemaphore cs1("CS1", 1, 1); // sempahore w/ init value 1; max 1
	CSemaphore ps2("PS2", 0, 1);
	CSemaphore cs2("CS2", 1, 1);
	
	CDataPool dp1("MyDataPoolName1", sizeof(struct MyDataPool));
	dataPoolPointer1 = (struct MyDataPool*)dp1.LinkDataPool(); // link datapool
	CDataPool dp2("MyDataPoolName2", sizeof(struct MyDataPool));
	dataPoolPointer2 = (struct MyDataPool*)dp2.LinkDataPool(); // link datapool

	cout << "Producer 2 is running..." << endl;

	for (int i = 10; i < 20; i++) {
		cs2.Wait();
		dataPoolPointer2->x = i;
		ps2.Signal();
		cout << "Produced " << i << "..." << endl;
	}

	return 0;
}