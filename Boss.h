#pragma once
#include "Input.h"
#include <cassert>
#include "DebugText.h"
#include <Model.h>
#include <WorldTransform.h>
#include <affin.h>
#include "ViewProjection.h"
#include "Time.h"


class Player;

class GameScene;

class Boss {
public:
	Boss();
	///<summary>
	///������
	///</summary>
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	///������
	///</summary>
	void Update(Vector3 player);

	///< summary>
	///������
	///</summary>
	void Draw(ViewProjection viewProjection_);

	void Attack(Vector3 Player);

	Vector3 GetWorldPos();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	///------------------------------------------///
	//�����o�ϐ�
	int isJump = 0;
	//�U���N�[���^�C��
	int coolTime;
	//�U���p�^�[��
	int attackNum;
	float jumpPower = 0;
	int waitTime = 0;
	int attackTmp;
};
