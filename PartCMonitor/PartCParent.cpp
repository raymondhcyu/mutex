#include "..\\rt.h"
#include "theMonitor.h"

/*	Benefit of using hidden mutex or monitor: won't forget to wait() or signal(),
	instead allowing computer to manage resource
*/

int main(void) {
	TheMonitor NamedMonitor;

	cout << "Setting initial value to 1000..." << endl;
	NamedMonitor.write(1000);

	CProcess p1("D:\\Documents\\CPEN333\\CPEN333Lab5\\Debug\\PartCMonitorChild.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);

	// Increment to 101,000
	for (int i = 0; i < 100000; i++) {
		NamedMonitor.increment();
	}

	// Should be 51,000 since child decremented 50,000 times
	cout << "Final value is: " << NamedMonitor.read() << endl;
	p1.WaitForProcess();
	return 0;
}