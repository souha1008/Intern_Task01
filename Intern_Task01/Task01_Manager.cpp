#include "Task01_Main.h"
#include "Task01_Manager.h"
#include "Task01_Renderer.h"
#include "Task01_Camera.h"
#include "Task01_3DPolygon.h"
#include "Task01Input.h"

Task01Camera* p_Camera = NULL;
Task013DPolygon* p_3DPolygon = NULL;

void Task01Manager::Init()
{
    Task01Renderer::Init();
    Task01_Input::Init();

    p_Camera = new Task01Camera();
    p_3DPolygon = new Task013DPolygon();

    p_Camera->Init();
    p_3DPolygon->Init();
}

void Task01Manager::Uninit()
{

    p_Camera->Uninit();
    p_3DPolygon->Uninit();

    delete p_Camera;
    delete p_3DPolygon;

    Task01_Input::Uninit();
    Task01Renderer::Uninit();
}

void Task01Manager::Update()
{
    Task01_Input::Update();

    p_3DPolygon->Update();
    p_Camera->Update();
}

void Task01Manager::Draw()
{
    Task01Renderer::Begin();

    /// ここから描画したいオブジェクトのDraw関数を記述

    p_3DPolygon->Draw();
    p_Camera->Draw();

    /// ここまで

    Task01Renderer::End();

}
