#pragma once
#include "Input.h"
#include <cassert>
#include "DebugText.h"
#include <Model.h>
#include <WorldTransform.h>
#include <affin.h>
#include "ViewProjection.h"
#include "Time.h"

typedef struct Bullet {
	WorldTransform worldTransform;
	int bulletTime;
};

class Boss {
public:
	Boss();
	///<summary>
	///初期化
	///</summary>
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	///初期化
	///</summary>
	void Update(Vector3 player);

	///< summary>
	///初期化
	///</summary>
	void Draw(ViewProjection viewProjection_);

	void AttackPattern(Vector3 player);

	void Impact(Vector3 player);

	void OnCollision();

	Vector3 GetWorldPos();

	int GetR() { return r; }

	bool GetIsDead() { return isDead; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	Bullet* bullet = new Bullet;

	///------------------------------------------///
	//メンバ変数
	int isJump = 0;
	//攻撃クールタイム
	int coolTime;
	//攻撃パターン
	int attackNum;
	float jumpPower = 0;
	int waitTime = 0;
	int attackTmp;
	bool isImpact = false;
	float speed = 0;
	int r = 4;
	bool isDead = false;
};
