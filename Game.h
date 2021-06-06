#pragma once

namespace Game
{

	const HMODULE game_handle{ GetModuleHandleA("gamedll_x64_rwdi.dll") };

	//Our local player struct, contains health, view angles, position and many many many pointers to player modules(health, stamina, etc.) and controllers e.g. lockpickcontroller
	class PlayerDI
	{
	public:
		char pad_0000[4248]; //0x0000
		Vector3 m_vecOrigin; //0x1098
		char pad_10A4[104]; //0x10A4
		Vector2 m_vecViewAngles; //0x110C
		char pad_1114[20]; //0x1114
		Vector3 m_vecHeadPos; //0x1128

	};

	//Contains our player name, a pointer to the local player and more
	class LocalClientDI
	{

	public:
		char _pad[0x50];
		class PlayerDI* m_pPlayer;

	};

	//This is our current session, contains the current level, a pointer to the local player and a pointer to the camera manager.
	class SessionDI
	{

	public:
		char _pad[0xB0];
		Engine::ILevel* m_pLevel;
		LocalClientDI* m_pLocalClient;
		Engine::CameraManagerDI* m_pCameraManager;

	};

	//Overarching struct pointers to almost everything ingame I imagine
	class IGame
	{

	public:
		char _pad[0x508];
		SessionDI* m_pSession;

		static IGame* GetInstance()
		{

			static IGame* game = nullptr;

			if (!game)
			{

				static uint64_t CreateGameFn = (uint64_t)GetProcAddress(GetModuleHandleA("engine_x64_rwdi.dll"), "CreateGame");
				uint32_t rel_offset = *(uint32_t*)(CreateGameFn + 0xF6);
				uint64_t rip = CreateGameFn + 0xFA;

				uint64_t c_game = *(uint64_t*)(rel_offset + rip);

				game = *(Game::IGame**)(c_game + 0x98);

			}

			return game;

		}

	};

	

}

