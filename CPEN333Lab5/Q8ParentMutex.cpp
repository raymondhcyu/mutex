#include "..\rt.h"

struct myDataPoolData {
	unsigned long long int x;
};

int main(void) {
	unsigned long long int a;

	CDataPool dp1("MyDataPoolName", sizeof(struct myDataPoolData));
	struct myDataPoolData* dataPtr = (struct myDataPoolData*) dp1.LinkDataPool(); // ptr to dp

	dataPtr->x = 0;

	CProcess p1("D:\\Documents\\CPEN333\\CPEN333Lab5\\Debug\\Q8ChildMutex.exe",
		NORMAL_PRIORITY_CLASS,
		PARENT_WINDOW,
		ACTIVE);

	cout << "Parent updating resource..." << endl;

	CMutex M("MyMutex"); // local mutex created with inital value 1, meaning resource free

	/*	Added Mutex, takes longer b/c child process needs to wait for signal to be clear/to be 1
		Allows both for loops in parent and child to complete, so result is 800,000
		Time-slicing: a = a + 1 instruction actually 3 instructions in assembly
		B/t cores/processes: a still a shared resource, can't gurantee that it'll be free
	*/
	for (unsigned long long int i = 0; i < 400000; i++)
	{
		M.Wait();
		a = dataPtr->x;
		a = a + 1;
		dataPtr->x = a;
		M.Signal();
	}

	p1.WaitForProcess();

	cout << "Final value of x is: " << dataPtr->x << endl;

	getchar();
	return 0;
}