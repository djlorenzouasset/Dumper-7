#include <Windows.h>
#include <iostream>
#include <chrono>

#include "Generators/Generator.h"
#include "MultiCapture/MultiCapture.h"

DWORD MainThread(HMODULE Module)
{
	AllocConsole();
	FILE* Dummy;
	freopen_s(&Dummy, "CONIN$", "r", stdin);
	freopen_s(&Dummy, "CONOUT$", "w", stderr);
	std::cerr.clear(); // clear internal error flags on cerr after redirect
	std::cerr << std::boolalpha << std::hex;

	std::cerr << "Initializing [Dumper-7]\n";

	Settings::Config::Load();
	Settings::Config::DelayDumperStart();

	Generator::InitEngineCore();

	//if (Settings::Debug::bExecuteSDKTestScript)
	//{
	//	/* Executes a python script to test if the SDK compiles correctly. */
	//	CppGenerator::ExecuteSDKCompilationTestScript();
	//}

	std::cerr << "\n[Dumper-7] Press:\n";
	std::cerr << "  F4 = Capture current classes (press in each level)\n";
	std::cerr << "  F5 = Generate SDK from all captured classes\n";
	std::cerr << "  F6 = Eject\n\n";

	while (true)
	{
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			MultiCapture::Capture();
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			MultiCapture::Generate();
		}

		if (GetAsyncKeyState(VK_F6) & 1)
		{
			fclose(stderr);
			if (Dummy) 
			{
				fclose(Dummy);
			}
			FreeConsole();

			FreeLibraryAndExitThread(Module, 0);
		}

		Sleep(100);
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
		break;
	}

	return TRUE;
}
