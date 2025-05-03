

#include <iostream>
#include <Windows.h>
#include <Wininet.h>
#include <ShlObj.h>

int main(void) {
	CoInitialize(nullptr);// initiallization for com object quering
	IActiveDesktop* iactd;
	WCHAR WallpaperPath[2000];
	CoCreateInstance(
		CLSID_ActiveDesktop, // what object to query com to create
		nullptr,
		CLSCTX_INPROC_SERVER, // This object will created localy to my process , this handle can be used only for this process
		__uuidof(IActiveDesktop), // Thats the id of the interface the com server must search for this object if is supported :)
		(void**)&iactd // fill the handle to the object you created for me
	);

	iactd->GetWallpaper(WallpaperPath, 2000, 0);
	iactd->Release(); // Release the reference and dicrements the reference counter , if zero object i destroyed
	std::wcout << WallpaperPath << std::endl;


	IShellLink* ISL_Handle = nullptr;
	CoCreateInstance(
		CLSID_ShellLink, // object for Server Com to create
		nullptr,
		CLSCTX_INPROC_SERVER, // This interface will be visible only from this process
		__uuidof(IShellLink), // This is the interface id that i querry 
		(void**)&ISL_Handle // Fill the handle pointer
	);

	char path[2000];
	wcstombs(path, WallpaperPath, 2000);


	CoUninitialize(); // finnalize the com object quering

	std::cin.get();
	return 0;
}