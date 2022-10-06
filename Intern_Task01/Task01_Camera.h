#pragma once

class Task01Camera
{
public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

private:
    D3DXVECTOR3 m_Position;
    D3DXVECTOR3 m_Target;
};

