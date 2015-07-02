// This is the main DLL file.

#include "stdafx.h"

#include "MetaArkInjector.h"

std::fstream logger;

typedef int(*StructureDamageHook)(void* self, float Damage, void* DamageEvent, void* EventInstigator, void*  DamageCauser);

StructureDamageHook fpStructureDamage = NULL;

int HookStructureDamage(void* self, float Damage, void* DamageEvent, void* EventInstigator, void*  DamageCauser)
{
	// logger << "Structure Damage - Original:" << Damage;
	Damage = MetaArk::MetaArk::instance->DoStructureDamage(Damage);
	// logger << "\tNew:" << Damage << std::endl;
	// logger.flush();
	return fpStructureDamage(self, Damage, DamageEvent, EventInstigator, DamageCauser);
}


#pragma region Main
void threadMain() {
	logger.open("ArkPluginLoader.log", std::fstream::out | std::fstream::app);
	logger << "Hello from ShooterGameServer.exe" << std::endl;
	logger.flush();

	// Init symbols
	HANDLE hProcess = GetCurrentProcess();
	SymInitialize(hProcess, NULL, TRUE);

	SYMBOL_INFO symbol = { 0 };
	symbol.SizeOfStruct = sizeof(symbol);
	BOOL result = SymFromName(hProcess, "APrimalStructure::TakeDamage", &symbol);

	logger << "symbol : " << std::hex << symbol.Address << std::endl;
	logger << "error : " << GetLastError << ", result : " << result << std::endl;
	logger.flush();

	// Initailize .NET runtime
	MetaArk::MetaArk();

	// Initialize MinHook.
	if (MH_Initialize() != MH_OK)
	{
		return;
	}

	// Create a hook for MessageBoxW, in disabled state.
	if (MH_CreateHook((LPVOID)symbol.Address, &HookStructureDamage, reinterpret_cast<LPVOID*>(&fpStructureDamage)) != MH_OK)
	{
		return;
	}

	if (MH_EnableHook((LPVOID)symbol.Address) != MH_OK)
	{
		return;
	}
	logger << "All systems go!" << std::endl;
}
#pragma endregion