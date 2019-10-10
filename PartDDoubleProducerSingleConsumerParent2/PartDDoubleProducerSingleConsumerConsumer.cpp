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

	// Create two datapools, once for each producer
	CDataPool dp1("MyDataPoolName1", sizeof(struct MyDataPool));
	dataPoolPointer1 = (struct MyDataPool*)dp1.LinkDataPool(); // link datapool
	CDataPool dp2("MyDataPoolName2", sizeof(struct MyDataPool));
	dataPoolPointer2 = (struct MyDataPool*)dp2.LinkDataPool(); // link datapool

	cout << "Consumer is running..." << endl;

	while (1) {
		if (ps1.Read() > 0) {
			cout << "\nHit return to consume data from producer 1..." << endl;
			getchar();
			ps1.Wait();
			cout << "Consumed " << dataPoolPointer1->x << " from producer 1..." << endl;
			cs1.Signal();
		}
		if (ps2.Read() > 0) {
			cout << "\nHit return to consume data from producer 2..." << endl;
			getchar();
			ps2.Wait();
			cout << "Consumed " << dataPoolPointer2->x << " from producer 2..." << endl;
			cs2.Signal();
		}
	}

	return 0;
}