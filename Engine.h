#pragma once

namespace Engine
{

	HMODULE engine_handle{ GetModuleHandleA("engine_x64_rwdi.dll") };

	//Enum containing the index for every bone (1 - 25)
	enum EBones
	{

		Pelvis = 0,
		Spine,
		Spine1,
		Spine2,
		Spine3,
		Neck,
		Neck1,
		Neck2,
		Head,
		EyeCamera,
		LClavicle,
		LUpperArm,
		LForeArm,
		LHand,
		RClavicle,
		RUpperArm,
		RForeArm,
		RHand,
		LThigh,
		RThigh,
		LCalf,
		RCalf,
		LFoot,
		RFoot,
		LSole,
		RSole

	};

	//Array class, this can be found in the game's memory often
	template <typename T>
	class Array
	{

	public:
		uint64_t* m_pItems;
		uint32_t m_pItemCount;

		T* At(int32_t i)
		{
			return (T*)m_pItems[i];
		}

		int32_t Size()
		{
			return m_pItemCount;
		}

	};

	//Every physical entity ingame has one of these, by every I mean the zombie ai, human ai and other players
	class IControlObject
	{

	public:
		char _pad[0x808];
		Vector3 m_vecOrigin; //Foot level coords
		char pad_0814[1996]; 
		Vector3 m_vecHeadPos; //Head level coords

		Vector3 GetBoneJointPos(unsigned char index)
		{
			
			using GetBoneJointPos_T = void(*__fastcall)(IControlObject*, Vector3*, unsigned char index);
			static GetBoneJointPos_T GetBoneJointPos_ = (GetBoneJointPos_T)GetProcAddress(engine_handle, "?GetBoneJointPos@IModelObject@@QEBA?AVvec3@@E@Z");

			Vector3 ret;
			GetBoneJointPos_(this, &ret, index);

			return ret;

		}

	};

	//Contains a pointer to an inner class, which holds the viewmatrix. Could use that if the exported W2S function wasn't working
	class Camera
	{

	public:
		Vector3 WorldToScreen(Vector3 coords)
		{

			Vector3 ret;

			using PointToScreen_T = void(*__fastcall)(Camera*, Vector3*, Vector3);
			static PointToScreen_T PointToScreen = (PointToScreen_T)GetProcAddress(engine_handle, "?PointToScreenClampToFrustum@IBaseCamera@@QEAA?BVvec3@@AEBV2@@Z");
			PointToScreen(this, &ret, coords);

			return ret;

		}

	};

	//Points to the current camera
	class CameraManagerDI
	{

	public:
		char _pad[0x50];
		Camera* m_pCurrentCamera; 

	};

	//AIManager. this holds the list of nearby AI's and more.
	class AIManager
	{

	public:
		char _pad[0x138];
		Array<IControlObject> ai_list;

	};

	//The actual game level, pointers to AIManager, PlayerList(unimplemented in hack currently) and more
	class ILevel
	{
	public:
		virtual void Function0();
		virtual void Function1();
		virtual void Function2();
		virtual void Function3();
		virtual void Function4();
		virtual void Function5();
		virtual void Function6();
		virtual void Function7();
		virtual void Function8();
		virtual void Function9();
		virtual void Function10();
		virtual void Function11();
		virtual void Function12();
		virtual void Function13();
		virtual void Function14();
		virtual void Function15();
		virtual void Function16();
		virtual void Function17();
		virtual void Function18();
		virtual void Function19();
		virtual void Function20();
		virtual void Function21();
		virtual void Function22();
		virtual void Function23();
		virtual void Function24();
		virtual void Function25();
		virtual void Function26();
		virtual void Function27();
		virtual void Function28();
		virtual void Function29();
		virtual void Function30();
		virtual void Function31();
		virtual void Function32();
		virtual void Function33();
		virtual AIManager* GetIAIManager();
		virtual void GetIAIDataManager();
		virtual void GetPlayableArea();

		char _pad[0x9F0];
		AIManager* m_pAiManager;

	};

	//Game's debug renderer, contains some handy stuff, still cant get text drawing to work
	class CDebugRenderer
	{

	public:
		virtual void AddLine(Vector3 const& point_one, Vector3 const& point_two, Vector4 const& color, __int64 unk_0) = 0;
		virtual void AddLineAA() = 0;
		virtual void AddArrowAA() = 0;
		virtual void AddConvexPoly() = 0;
		virtual void AddText(wchar_t const* text, Vector4 const& color, Vector4 const& _color, float x, float y) = 0;

	};

	//Game's renderer contains debug drawing function
	class CRenderer
	{
	public:

		virtual void DTor();
		virtual void GetImmediateContext();
		virtual void GetNewContext();
		virtual void ReleaseContext();
		virtual void ApplyVideoSettings();
		virtual void Shutdown();
		virtual void FindBoolVar();
		virtual void GetDesktopResolution();
		virtual void BeginFrame();
		virtual void EndFrame();
		virtual void Present();
		virtual void DiscardDynamicBuffers();
		virtual void SetGamma();
		virtual void GetGammaRanges();
		virtual void Function14();
		virtual void Function15();
		virtual void Function16();
		virtual void Function17();
		virtual void Function18();
		virtual void Function19();
		virtual void Function20();
		virtual void Function21();
		virtual void Function22();
		virtual void Function23();
		virtual void Function24();
		virtual void Function25();
		virtual void Function26();
		virtual void Function27();
		virtual void Function28();
		virtual void Function29();
		virtual void Function30();
		virtual void Function31();
		virtual void Function32();
		virtual void Function33();
		virtual void Function34();
		virtual void Function35();
		virtual void Function36();
		virtual void Function37();
		virtual void Function38();
		virtual void Function39();
		virtual void Function40();
		virtual void Function41();
		virtual void Function42();
		virtual void Function43();
		virtual void Function44();
		virtual void Function45();
		virtual void Function46();
		virtual void Function47();
		virtual void Function48();
		virtual void Function49();
		virtual void Function50();
		virtual void Function51();
		virtual void Function52();
		virtual void Function53();
		virtual void Function54();
		virtual void Function55();
		virtual void Function56();
		virtual void Function57();
		virtual void Function58();
		virtual void Function59();
		virtual void Function60();
		virtual void Function61();
		virtual void Function62();
		virtual void Function63();
		virtual void Function64();
		virtual void Function65();
		virtual void Function66();
		virtual void Function67();
		virtual void Function68();
		virtual void Function69();
		virtual void Function70();	
		virtual void Function71();
		virtual void Function72();
		virtual void Function73();
		virtual void Function74();
		virtual void Function75();
		virtual void Function76();
		virtual void Function77();
		virtual CDebugRenderer* GetDebugRenderer();
		virtual void DebugRender();
		virtual void DebugLine(Vector3 const& point_one, Vector3 const& point_two, Vector4 const& color, __int64 unk_0);
		virtual void DebugLineAA();
		virtual void DebugArrowAA();
		virtual void DebugPoint();
		virtual void DebugExtents();
		virtual void DebugExtentsAA();
		virtual void DebugExtents1();
		virtual void DebugExtentsAA2();
		virtual void DebugEllipse();
		virtual void DebugTri();
		virtual void DebugTri1();
		virtual void ConvexPoly();
		virtual void DebugText(float x, float y, wchar_t const*, Vector4 const& color, Vector4 const& unknown);
		virtual void DebugText(Vector3 const& pos, wchar_t const* text, Vector4 const& color, Vector2 const& unknown);
		virtual void DebugScreenQuad() = 0;
		virtual void DebugScreenQuad(float, float, float, float, unsigned int) = 0;
		virtual void CalcDebugTextExtents() = 0;
		virtual void CalcDebugTextExtents_() = 0;
		virtual void CalcDebugTextWidth(wchar_t const*) = 0;
		virtual void CalcDebugTextHeight(wchar_t const*) = 0;



	};

}

extern Engine::CRenderer* renderer = nullptr;