#include "..\rt.h"

struct myDataPoolData {
	unsigned long long int x;
};

int main(void) {
	unsigned long long int a;

	CDataPool dp1("MyDataPoolName", sizeof(struct myDataPoolData));
	struct myDataPoolData* dataPtr = (struct myDataPoolData*) dp1.LinkDataPool(); // ptr to dp

	cout << "Child resource updating..." << endl;

	CMutex M("MyMutex");

	for (unsigned long long int i = 0; i < 400000; i++)
	{
		M.Wait();
		a = dataPtr->x;
		a = a + 1;
		dataPtr->x = a;
		M.Signal();
	}

	return 0;
}