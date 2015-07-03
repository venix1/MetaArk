#include "Stdafx.h"

#define PROG_NAME "ShooterGameServer.exe"

std::string pName;

#pragma region VersionWrapper
HINSTANCE hmMain = 0;
HINSTANCE hmVersion = 0;
extern "C" FARPROC versionFunctions[17] = { 0 };
#pragma endregion

void threadMain();

bool APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DWORD pID = GetCurrentProcessId();
		TCHAR buffer[MAX_PATH] = { 0 };
		DWORD bufSize = sizeof(buffer) / sizeof(*buffer);
		GetModuleFileName(NULL, buffer, bufSize);
		pName = PathFindFileName(buffer);

		if (pName == PROG_NAME)
		{
			hmMain = hModule;
			char infoBuf[MAX_PATH];
			strcpy_s(infoBuf, MAX_PATH, "c:\\windows\\system32\\version.dll");
			hmVersion = LoadLibrary(infoBuf);
			if (!hmVersion)
			{
				MessageBox(NULL, "The original version.dll could not be found.", "MetaArkInjector", MB_OK | MB_ICONERROR);
				return false;
			}
			versionFunctions[0] = GetProcAddress(hmVersion, "GetFileVersionInfoA");
			versionFunctions[1] = GetProcAddress(hmVersion, "GetFileVersionInfoByHandle");
			versionFunctions[2] = GetProcAddress(hmVersion, "GetFileVersionInfoExA");
			versionFunctions[3] = GetProcAddress(hmVersion, "GetFileVersionInfoExW");
			versionFunctions[4] = GetProcAddress(hmVersion, "GetFileVersionInfoSizeA");
			versionFunctions[5] = GetProcAddress(hmVersion, "GetFileVersionInfoSizeExA");
			versionFunctions[6] = GetProcAddress(hmVersion, "GetFileVersionInfoSizeExW");
			versionFunctions[7] = GetProcAddress(hmVersion, "GetFileVersionInfoSizeW");
			versionFunctions[8] = GetProcAddress(hmVersion, "GetFileVersionInfoW");
			versionFunctions[9] = GetProcAddress(hmVersion, "VerFindFileA");
			versionFunctions[10] = GetProcAddress(hmVersion, "VerFindFileW");
			versionFunctions[11] = GetProcAddress(hmVersion, "VerInstallFileA");
			versionFunctions[12] = GetProcAddress(hmVersion, "VerInstallFileW");
			versionFunctions[13] = GetProcAddress(hmVersion, "VerLanguageNameA");
			versionFunctions[14] = GetProcAddress(hmVersion, "VerLanguageNameW");
			versionFunctions[15] = GetProcAddress(hmVersion, "VerQueryValueA");
			versionFunctions[16] = GetProcAddress(hmVersion, "VerQueryValueW");
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)threadMain, NULL, NULL, NULL);
		}
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		if (pName == PROG_NAME)
			FreeLibrary(hmVersion);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return true;
}