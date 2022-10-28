#pragma once
//
//	vector.h
//

//�J���[�\����
struct COLOR
{
	float	r;
	float	g;
	float	b;
	float	a;
};
//2D�x�N�g���\����
struct VECTOR2D
{
	VECTOR2D()//�R���X�g���N�^�[
	{
		x = 0;
		y = 0;
	}
	//�����t���R���X�g���N�^�[
	VECTOR2D(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
	//�����o�[�ϐ�
	float	x;
	float	y;
};

//3D�x�N�g���\����
struct VECTOR3D
{
	VECTOR3D()//�R���X�g���N�^�[
	{
		x = 0;
		y = 0;
		z = 0;
	}
	//�����t���R���X�g���N�^�[
	VECTOR3D(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
	//�����o�[�ϐ�
	float	x;
	float	y;
	float	z;
};

//4D�x�N�g���\����
struct VECTOR4D
{
	VECTOR4D()//�R���X�g���N�^�[
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	//�����t���R���X�g���N�^�[
	VECTOR4D(float inX, float inY,
		float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
	//�����o�[�ϐ�
	float	x;
	float	y;
	float	z;
	float	w;
};

//���_�\����
struct VERTEX_3D
{
	VECTOR2D	TexturePos;	//�e�N�X�`�����W
	COLOR		Diffuse;	//�f�t���[�Y
	VECTOR3D	Normal;		//�@��
	VECTOR3D	Position;	//���_���W
};
