#include <windows.h>
#include <stdio.h>

int main()
{
	byte change[] = { 0xC2, 0x04, 0x00 };
	byte original[] = { 0x55, 0x8B, 0xEC };
	LPVOID address = 0x4F04A0;
	DWORD oldp = 0;
	BOOL hackEnabled = TRUE;

	SetConsoleTitleA("1.9 GDPS noclip");

	HWND window = FindWindowA(NULL, "Geometry Dash");

	printf("Waiting for Geometry Dash...\n");

	while (!window)
	{
		Sleep(250);
		window = FindWindowA(NULL, "Geometry Dash");
	}

	system("cls");

	DWORD pid;
	GetWindowThreadProcessId(window, &pid);

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (process == INVALID_HANDLE_VALUE)
	{
		printf("Couldn't attach to Geometry Dash\n");
		return 1;
	}

	VirtualProtectEx(process, address, sizeof(change), PAGE_EXECUTE_READWRITE, &oldp);

	for (;;)
	{
		printf("Cos8o's 1.9 GDPS noclip hack\n");

		if (hackEnabled)
		{
			WriteProcessMemory(process, address, change, sizeof(change), NULL);
			printf("Hack state: enabled\n");
		}
		else
		{
			WriteProcessMemory(process, address, original, sizeof(original), NULL);
			printf("Hack state: disabled\n");
		}


		getchar();

		if (hackEnabled)
			hackEnabled = FALSE;
		else
			hackEnabled = TRUE;

		system("cls");
	}

	return 0;
}
