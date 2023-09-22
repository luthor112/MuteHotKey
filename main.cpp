#include <windows.h>
#include <stdio.h>

#define RELEASE

int wmain(int argc, wchar_t* argv[])
{
	if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, VK_ESCAPE) &&
		RegisterHotKey(NULL, 2, MOD_ALT | MOD_NOREPEAT, VK_F11) &&
		RegisterHotKey(NULL, 3, MOD_ALT | MOD_NOREPEAT, VK_F12) &&
		RegisterHotKey(NULL, 4, MOD_ALT | MOD_NOREPEAT, VK_F8))
	{
		wprintf(L"Hotkeys registered, using MOD_NOREPEAT flag\n");
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
			switch (msg.wParam)
			{
			case 1:
				ip.ki.wVk = VK_VOLUME_MUTE;
				break;
			case 2:
				ip.ki.wVk = VK_VOLUME_DOWN;
				break;
			case 3:
				ip.ki.wVk = VK_VOLUME_UP;
				break;
			case 4:
				ip.ki.wVk = VK_MEDIA_PLAY_PAUSE;
				break;
			}
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));

			wprintf(L"INPUT_KEYBOARD sent\n");
		}
	}

	return 0;
}
