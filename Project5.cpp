#include <iostream>
#include <windows.h>
#include <chrono>
#include <ctime>

const int g_wakeUpTimeout = 5000;

DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
	int timeout = *static_cast<int*>(lpParam);
	while (timeout > 0) {
		time_t time = std::time(nullptr);
		char timeStr[26] = {};		
		ctime_s(timeStr, sizeof(timeStr), &time);
		std::cout << "Date and Time: " << timeStr << std::endl;
		timeout -= g_wakeUpTimeout;
		Sleep(g_wakeUpTimeout);
	}
	return 0;
}

int main()
{
	char* pValue = {};
	size_t len = {};
	errno_t err = _dupenv_s(&pValue, &len, "My_Time");
	int timeout = atoi(pValue);
	if (!err) {
		DWORD threadId = 0;
		HANDLE h = CreateThread(
			NULL,
			0,
			MyThreadFunction,
			&timeout,
			0,
			&threadId);
		Sleep(timeout + g_wakeUpTimeout);

		time_t threadLifetimeEnd = time(NULL);
		CloseHandle(h);
		free(pValue);
	}
	return 0;
}