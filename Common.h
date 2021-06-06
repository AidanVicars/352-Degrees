#pragma once

//STL
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

//WinApi
#include <Windows.h>
#include <Psapi.h>

//D3D11
#include <dxgi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

//inline ID3D11DeviceContext* context = nullptr;

//FW1
//#include "FW1FontWrapper.h"
//#pragma comment(lib, "FW1FontWrapper.lib")



//ImGui
//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_win32.h"
//#include "ImGui/imgui_impl_dx11.h"

//Custom Headers
	#include "Util.h"
	#include "Structs.h"
	#include "VMT.h"

	//Game Structures
	#include "Engine.h"
	#include "Game.h"


	//Actual code
	#include "Hacks.h"
	#include "Hooks.h"