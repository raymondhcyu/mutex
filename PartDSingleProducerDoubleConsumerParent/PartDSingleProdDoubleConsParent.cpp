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

	CProcess p1("D:\\Documents\\CPEN333\\CPEN333Lab5\\Debug\\PartDSingleProducerDoubleConsumerChild.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);

	CProcess p2("D:\\Documents\\CPEN333\\CPEN333Lab5\\Debug\\PartDSingleProducerDoubleConsumerChild2.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);

	cout << "Producer is running..." << endl;

	for (int i = 0; i < 10; i++) {
		cs1.Wait(); 
		cs2.Wait();
		dataPoolPointer->x = i;
		ps1.Signal();
		ps2.Signal();
		cout << "Produced " << i << "..." << endl;
	}

	p1.WaitForProcess();
	p2.WaitForProcess();

	return 0;
}