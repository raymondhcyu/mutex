#include "..\\rt.h"
#include "..\\PartCMonitor\theMonitor.h"

int main(void) {
	cout << "Hello from child process!" << endl;

	TheMonitor NamedMonitor;

	for (int i = 0; i < 50000; i++) {
		NamedMonitor.decrement();
	}

	getchar();
	return 0;
}