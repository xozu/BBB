#include <gnu/libc-version.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <iostream>
#include <signal.h>
using namespace std;

int main()
{
	cout << "The GNU libc version is " << gnu_get_libc_version() << endl;

	// process id tid is thread identifier - see: sys/syscall.h
	pid_t tid;
	tid = syscall(SYS_gettid);
	cout << "The Current PID is: " << tid << endl;
	// can also get by calling getpid() function from signal.h
	cout << "The Current PID is: " << getpid() << endl;

	// Can get Current UserID by using:
	int uid = syscall(SYS_getuid);
	cout << "It is being run by user with ID: " << uid << endl;
	// or getting the value from syscalls..
	uid = syscall(0xc7);
	cout << "It is being run by user with ID: " << uid << endl;
	return 0;
}
