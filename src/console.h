#ifndef _CONSOLE_
#define _CONSLOE_

#include <pthread.h>
class Console
{
private:
	std::string output_buffer;
	std::string input_buffer;
	static Console *instance = nullptr;
	static pthread_mutex_t = PTHREAD_MUTEX_INITIALIZER;
	Console();
	run();
public:
	/**
		start asynchronous input/output mode
	*/
	void startup();
	void stop();
}

#endif
