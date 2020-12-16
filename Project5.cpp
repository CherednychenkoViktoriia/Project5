#include <iostream>
#include <windows.h>
#include <time.h>

DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
	for (; ;) {
		char str[26] = {};
		time_t t = time(NULL);
		time(&t);
		ctime_s(str, sizeof(str), &t);
		std::cout << "Date and Time: " << str << std::endl;
		Sleep(5000);
	}
	return 0;
}

int main()
{
	time_t threadLifetimeBegin = time(NULL);
	
	DWORD threadId = 0;
	HANDLE h = CreateThread(
		NULL,
		0,
		MyThreadFunction,
		0,
		0,
		&threadId);

	Sleep(25000);

	time_t threadLifetimeEnd = time(NULL);

	char* pValue;
	size_t len;
	errno_t err = _dupenv_s(&pValue, &len, "MY_VAR");
	if (!err) {
		time_t threadLifetime = threadLifetimeEnd - threadLifetimeBegin;
		std::cout << "Thread lifetime in seconds: " << threadLifetime << std::endl;
	}
	free(pValue);

	return 0;
}