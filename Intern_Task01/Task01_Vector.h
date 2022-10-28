#pragma once
//
//	vector.h
//

//カラー構造体
struct COLOR
{
	float	r;
	float	g;
	float	b;
	float	a;
};
//2Dベクトル構造体
struct VECTOR2D
{
	VECTOR2D()//コンストラクター
	{
		x = 0;
		y = 0;
	}
	//引数付きコンストラクター
	VECTOR2D(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
	//メンバー変数
	float	x;
	float	y;
};

//3Dベクトル構造体
struct VECTOR3D
{
	VECTOR3D()//コンストラクター
	{
		x = 0;
		y = 0;
		z = 0;
	}
	//引数付きコンストラクター
	VECTOR3D(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
	//メンバー変数
	float	x;
	float	y;
	float	z;
};

//4Dベクトル構造体
struct VECTOR4D
{
	VECTOR4D()//コンストラクター
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	//引数付きコンストラクター
	VECTOR4D(float inX, float inY,
		float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
	//メンバー変数
	float	x;
	float	y;
	float	z;
	float	w;
};

//頂点構造体
struct VERTEX_3D
{
	VECTOR2D	TexturePos;	//テクスチャ座標
	COLOR		Diffuse;	//デフューズ
	VECTOR3D	Normal;		//法線
	VECTOR3D	Position;	//頂点座標
};
