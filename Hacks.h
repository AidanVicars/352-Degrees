#pragma once

namespace Esp
{

    void DrawBox(Vector3 top, Vector3 bottom)
    {

        float height = abs(top.y - bottom.y);
        float width = height / 2.2f;
        float half_width = width / 2;

        renderer->DebugLine({ bottom.x - half_width, bottom.y }, bottom, { 255, 0, 0, 255 }, 0);
        renderer->DebugLine({ bottom.x + half_width, bottom.y }, bottom, { 255, 0, 0, 255 }, 0);
        renderer->DebugLine({ bottom.x + half_width, bottom.y }, { top.x + half_width, top.y - 12.0f }, { 255, 0, 0, 255 }, 0);
        renderer->DebugLine({ bottom.x - half_width, bottom.y }, { top.x - half_width, top.y - 12.0f }, { 255, 0, 0, 255 }, 0);
        renderer->DebugLine({ top.x + half_width, top.y - 12.0f }, { top.x - half_width, top.y - 12.0f }, { 255, 0, 0, 255 }, 0);

    }



    void DrawBone(Engine::EBones bone, Engine::EBones next_bone, Engine::IControlObject* object)
    {

        Engine::Camera* camera = Game::IGame::GetInstance()->m_pSession->m_pCameraManager->m_pCurrentCamera;

        Vector3 bone_pos = object->GetBoneJointPos(bone);
        Vector3 bone_pos2D = camera->WorldToScreen(bone_pos);

        Vector3 nextbone_pos = object->GetBoneJointPos(next_bone);
        Vector3 nextbone_pos2D = camera->WorldToScreen(nextbone_pos);

        renderer->DebugLine(bone_pos2D, nextbone_pos2D, { 255, 0, 0, 255 }, 0);

    }

    void DrawSkeleton(Engine::IControlObject* object)
    {
        //Disclaimer
        //This is shit code I know
        //I'd usually iterate through each bone and draw but the bones don't go in order in the enum

        DrawBone(Engine::EBones::RSole, Engine::EBones::RFoot, object);
        DrawBone(Engine::EBones::RFoot, Engine::EBones::RCalf, object);
        DrawBone(Engine::EBones::RCalf, Engine::EBones::RThigh, object);
        DrawBone(Engine::EBones::RThigh, Engine::EBones::Pelvis, object);

        DrawBone(Engine::EBones::LSole, Engine::EBones::LFoot, object);
        DrawBone(Engine::EBones::LFoot, Engine::EBones::LCalf, object);
        DrawBone(Engine::EBones::LCalf, Engine::EBones::LThigh, object);
        DrawBone(Engine::EBones::LThigh, Engine::EBones::Pelvis, object);

        DrawBone(Engine::EBones::Pelvis, Engine::EBones::Spine, object);
        DrawBone(Engine::EBones::Spine, Engine::EBones::Spine1, object);
        DrawBone(Engine::EBones::Spine1, Engine::EBones::Spine2, object);
        DrawBone(Engine::EBones::Spine2, Engine::EBones::Spine3, object);

        DrawBone(Engine::EBones::Spine3, Engine::EBones::Neck, object);
        DrawBone(Engine::EBones::Neck, Engine::EBones::Head, object);

        DrawBone(Engine::EBones::Neck, Engine::EBones::LClavicle, object);
        DrawBone(Engine::EBones::LClavicle, Engine::EBones::LUpperArm, object);
        DrawBone(Engine::EBones::LUpperArm, Engine::EBones::LForeArm, object);
        DrawBone(Engine::EBones::LForeArm, Engine::EBones::LHand, object);

        DrawBone(Engine::EBones::Neck, Engine::EBones::RClavicle, object);
        DrawBone(Engine::EBones::RClavicle, Engine::EBones::RUpperArm, object);
        DrawBone(Engine::EBones::RUpperArm, Engine::EBones::RForeArm, object);
        DrawBone(Engine::EBones::RForeArm, Engine::EBones::RHand, object);

    }

	void Render()
	{

        Game::IGame* game = Game::IGame::GetInstance();
		Engine::Camera* camera = game->m_pSession->m_pCameraManager->m_pCurrentCamera;
		Engine::AIManager* ai_manager = game->m_pSession->m_pLevel->m_pAiManager;
		
		for (int i = 0; i = ai_manager->ai_list.Size(); ++i)
		{

            Engine::IControlObject* current_object = ai_manager->ai_list.At(i);

            Vector3 head_screenpos = camera->WorldToScreen(current_object->m_vecHeadPos);
            Vector3 screen_pos = camera->WorldToScreen(current_object->m_vecOrigin);

            DrawBox(head_screenpos, screen_pos);
            DrawSkeleton(current_object);

		}

	}

}

namespace Crosshair
{

	void Render()
	{

		


	}

}