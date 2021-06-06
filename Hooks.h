#pragma once

//VMT ptrs
VMT* swapchain_hook = nullptr;
VMT* renderer_hook = nullptr;

//Function prototype and a pointer to the original function
using Present_T = HRESULT(*__fastcall)(IDXGISwapChain*, UINT, UINT);
Present_T o_present = nullptr;

//Game begin scene not Dx11
using BeginScene_T = uint64_t(*__fastcall)(Engine::CRenderer* thisptr, void* unk0);
BeginScene_T o_beginscene = nullptr;



namespace Hooks
{

	uint64_t __fastcall hkBeginScene(Engine::CRenderer* thisptr, void* unk0)
	{

		Esp::Render();

		return o_beginscene(thisptr, unk0);

	}

	HRESULT hkPresent(IDXGISwapChain* thisptr, UINT sync_interval, UINT flags)
	{

		return o_present(thisptr, sync_interval, flags);

	}

	bool Init()
	{

		IDXGISwapChain* swap_chain = Util::GetSwapChain();
		renderer = *(Engine::CRenderer**)(Engine::engine_handle + 0xA2EF00);
		
		if (!swap_chain || !renderer) return false;
		
		//Create a vmt hook on the swapchain vmt
		swapchain_hook = new VMT((uintptr_t**)swap_chain);

		//Get original function before hooking
		o_present = swapchain_hook->GetOriginal<Present_T>(8);

		//Hook IDXGISwapChain::Present
		//swapchain_hook->Hook(8, (PVOID)hkPresent);

		//Create a vmt hook on renderer's vmt
		renderer_hook = new VMT((uintptr_t**)renderer);

		//Get the original function
		o_beginscene = renderer_hook->GetOriginal<BeginScene_T>(8);

		//Hook CRenderer::BeginScene
		renderer_hook->Hook(8, hkBeginScene);

		return true;

	}

	void Unhook()
	{

		delete swapchain_hook;
		delete renderer_hook;

	}

}