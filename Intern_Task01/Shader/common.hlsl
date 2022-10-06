//���̃t�@�C���͑��̃V�F�[�_�[�t�@�C���փC���N���[�h����܂�
// �e��}�g���N�X���󂯎��ϐ���p��
cbuffer WorldBuffer : register(b0)//�萔�o�b�t�@ 0 ��
{
	matrix World;
}
cbuffer ViewBuffer : register(b1) //�萔�o�b�t�@ 1 ��
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2) //�萔�o�b�t�@ 2 ��
{
	matrix Projection;
}
cbuffer CameraBuffer : register(b5) //�o�b�t�@�̂T�ԂƂ���
{
	float4 CameraPosition; //�J�������W���󂯂Ƃ�ϐ�
}

//���_�V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
//����͒��_�o�b�t�@�̓��e���̂���
struct VS_IN
{
	float4 Position : POSITION0; //�Z�}���e�B�N�X�͒��_���C�A�E�g�ɑΉ�
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};
//�s�N�Z���V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
struct PS_IN
{
	float4 Position : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

//���C�g�I�u�W�F�N�g�\���̂ƃR���X�^���g�o�b�t�@
struct LIGHT
{
	bool  Enable;
	bool3 Dummy; //�z�u�A�h���X��4�̔{���ɂ���ƌ����������̂Œ����p
	float4 Direction; //����C����ł�������VisualStudio������Ă���Ă���B
	float4 Diffuse;
	float4 Ambient;
};
cbuffer LightBuffer : register(b4)//�R���X�^���g�o�b�t�@�S�ԂƂ���
{
	LIGHT Light; //���C�g�\����
}




/////////////////////EOF//////////////////////
