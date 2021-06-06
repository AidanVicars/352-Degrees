#pragma once


namespace Util
{

	template<typename T = uint64_t>
	T PatternScan(const char* module_name, std::vector<uint8_t> pattern)
	{
		//Get the required module information
		const HMODULE mod = GetModuleHandleA(module_name);
		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), mod, &module_info, sizeof(module_info));

		//Module size and base
		uint64_t module_size = module_info.SizeOfImage;
		uint8_t* module_start = reinterpret_cast<uint8_t*>(mod);
		const size_t pattern_length = pattern.size();

		//Begin iteration of the modules bytes
		for (uint64_t i{ 0 }; i < module_size; ++i)
		{

			bool found = true;
			//Check these against the bytes of the pattern
			for (int j{ 0 }; j < pattern_length; j++)
			{

				if (pattern[j] != 0x00 && module_start[i + j] != pattern[j])
				{

					found = false;
					break;

				}

			}

			if (found) return (T)&module_start[i];

		}

		//Failed
		return 0;

	}

	IDXGISwapChain* GetSwapChain()
	{

		/*IDXGISwapChain* return_val = nullptr;
		ID3D11Device* device = nullptr;

		D3D_FEATURE_LEVEL feat_level;
		DXGI_SWAP_CHAIN_DESC swap_desc{ 0 };
		swap_desc.BufferCount = 1;
		swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_desc.BufferDesc.Height = 800;
		swap_desc.BufferDesc.Width = 600;
		swap_desc.BufferDesc.RefreshRate = { 60, 1 };
		swap_desc.OutputWindow = GetForegroundWindow();
		swap_desc.Windowed = TRUE;
		swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_desc.SampleDesc.Count = 1;
		swap_desc.SampleDesc.Quality = 0;

		D3D_FEATURE_LEVEL desired_level[6] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_NULL, nullptr, 0, desired_level, 6, D3D11_SDK_VERSION, &swap_desc, &return_val, &device, &feat_level, nullptr);
		if (FAILED(hr))
			return nullptr;

		device->Release();

		return return_val;*/

		uint64_t swapchain_ptr = Util::PatternScan("rd3d11_x64_rwdi.dll", { 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x41, 0x8B });
		uint32_t offset_rel = *(uint32_t*)(swapchain_ptr + 0x3);

		uint64_t rip = swapchain_ptr + 0x7;

		return *(IDXGISwapChain**)(rip + offset_rel);

	}

}