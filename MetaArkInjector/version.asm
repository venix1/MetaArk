EXTRN versionFunctions:QWORD

.code

PUBLIC GetFileVersionInfoA
PUBLIC GetFileVersionInfoByHandle
PUBLIC GetFileVersionInfoExA
PUBLIC GetFileVersionInfoExW
PUBLIC GetFileVersionInfoSizeA
PUBLIC GetFileVersionInfoSizeExA
PUBLIC GetFileVersionInfoSizeExW
PUBLIC GetFileVersionInfoSizeW
PUBLIC GetFileVersionInfoW
PUBLIC VerFindFileA
PUBLIC VerFindFileW
PUBLIC VerInstallFileA
PUBLIC VerInstallFileW
PUBLIC VerLanguageNameA
PUBLIC VerLanguageNameW
PUBLIC VerQueryValueA
PUBLIC VerQueryValueW

GetFileVersionInfoA:
		jmp versionFunctions[0 * 8];

GetFileVersionInfoByHandle:
		jmp versionFunctions[1 * 8];

GetFileVersionInfoExA:
		jmp versionFunctions[2 * 8];

GetFileVersionInfoExW:
		jmp versionFunctions[3 * 8];

GetFileVersionInfoSizeA:
		jmp versionFunctions[4 * 8];

GetFileVersionInfoSizeExA:
		jmp versionFunctions[5 * 8];

GetFileVersionInfoSizeExW:
		jmp versionFunctions[6 * 8];

GetFileVersionInfoSizeW:
		jmp versionFunctions[7 * 8];

GetFileVersionInfoW:
		jmp versionFunctions[8 * 8];

VerFindFileA:
		jmp versionFunctions[9 * 8];

VerFindFileW:
		jmp versionFunctions[10 * 8];

VerInstallFileA:
		jmp versionFunctions[11 * 8];

VerInstallFileW:
		jmp versionFunctions[12 * 8];

VerLanguageNameA:
		jmp versionFunctions[13 * 8];

VerLanguageNameW:
		jmp versionFunctions[14 * 8];

VerQueryValueA:
		jmp versionFunctions[15 * 8];

VerQueryValueW:
		jmp versionFunctions[16 * 8];

END