#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_Camera.h"
#include "Task01_3DPolygon.h"
#include "Task01_Input.h"

#ifdef USE_DX11

Task01Camera* p_Camera = NULL;
Task013DPolygon* p_3DPolygon = NULL;

#endif // USE_DX11
void Task01Manager::Init()
{
    Task01Renderer::Init();
    Task01_Input::Init();

#ifdef USE_DX11


    p_Camera = new Task01Camera();
    p_3DPolygon = new Task013DPolygon();

    p_Camera->Init();
    p_3DPolygon->Init();

#endif // USE_DX11
}

void Task01Manager::Uninit()
{
#ifdef USE_DX11

    p_Camera->Uninit();
    p_3DPolygon->Uninit();

    delete p_Camera;
    delete p_3DPolygon;


#endif // USE_DX11

    Task01_Input::Uninit();
    Task01Renderer::Uninit();
}

void Task01Manager::Update()
{
#ifdef USE_DX11

    Task01_Input::Update();

    p_3DPolygon->Update();
    p_Camera->Update();

#endif // USE_DX11
}

void Task01Manager::Draw()
{
    Task01Renderer::Begin();

#ifdef USE_DX11


    /// ここから描画したいオブジェクトのDraw関数を記述

    p_3DPolygon->Draw();
    p_Camera->Draw();

    /// ここまで


#endif // USE_DX11

#ifdef USE_DX12

    /// ここから描画したいオブジェクトのDraw関数を記述

    /// ここまで

#endif // USE_DX12

    Task01Renderer::End();

}
