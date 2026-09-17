#include <i.h>

void mem( )
{

	DWORD pid = 0;

	HANDLE ss = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );
	PROCESSENTRY32 process{ };
	process.dwSize = sizeof( process );

	while ( Process32Next( ss, &process ) )
	{
		if ( wcscmp ( process.szExeFile , L"javaw.exe" ) == 0 ) // javaw.exe is the process that we r looking 4
		{
			pid = process.th32ProcessID;
			break;
		}
	}

	CloseHandle( ss );

	if (!pid)
	{
	
		std::cout << ( "couldnt find process") << "\n" << std::endl;
		std::cin.get( );
		return;
	
	}
	
	HANDLE hProcess = OpenProcess( PROCESS_VM_READ , FALSE , pid );

	uintptr_t address = 0x611CBD160; // health addy for 1.21.11 
	float v = 0;

	ReadProcessMemory( hProcess , (void*)address , &v , sizeof( v ) , nullptr );	

	std::cout << "f -> " << v << "\n" << std::endl;

	CloseHandle(hProcess);
}

int main( )
{
	mem( );

	std::cin.get( );
	return 0;
}
