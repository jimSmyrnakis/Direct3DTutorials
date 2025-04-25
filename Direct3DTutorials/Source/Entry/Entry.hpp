#pragma once
#include "../FrameWork/Window.hpp"
#include "../FrameWork/EventLisceners/Example/Button.hpp"
int CALLBACK WinMain( // CALLBACK is stdcall function conversion , is important for window methods calls 
	_In_ HINSTANCE hInstance, // the current instance of the application window 
	_In_ HINSTANCE hPrevInstance, // not used any more
	_In_ LPSTR lpCmdLine, // a string to the command line argument (all in one and not seperate)
	_In_ int  nCmdhow // how the window must be show when the program starts
);