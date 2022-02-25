#include <windows.h>
#include <stdio.h>

#define RELEASE

int wmain(int argc, wchar_t *argv[])
{
	if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, VK_F1))
	{
		wprintf(L"Hotkey 'Alt+F1' registered, using MOD_NOREPEAT flag\n");
	}
	else
	{
		wprintf(L"Error registering hotkey\n");
		return 1;
	}

#ifdef RELEASE
	if (!FreeConsole())
	{
		wprintf(L"Could not detach from console\n");
	}
#endif

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			wprintf(L"WM_HOTKEY received\n");

			INPUT ip = { 0 };
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = VK_VOLUME_MUTE;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));

			wprintf(L"VK_VOLUME_MUTE sent\n");
		}
	}

	return 0;
}
