#pragma once
#include "Input.h"
#include <cassert>
#include "DebugText.h"
#include <Model.h>
#include <WorldTransform.h>
#include <affin.h>
#include "ViewProjection.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>


class Player {
  public:
	  ///<summary>
	  ///������
	  ///</summary>
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	///������
	///</summary>
	void Update(ViewProjection viewProjection_,Vector3 boss);

	///< summary>
	///������
	///</summary>
	void Draw(ViewProjection viewProjection_);

	///< summary>
	///������
	///</summary>
	void Attack(ViewProjection viewProjection_,Vector3 boss);
	void Move(ViewProjection viewProjection_);

	//�L�����̌����ɉ����������ɋ�������
	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	//���[���h���W���擾
	Vector3 GetWorldPosition2();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	void setparent(WorldTransform* worldTransform);

	void ResetPlayer();

	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	

public:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0, 0, 0 };
	//�W�����v
	float jumpPower = 0.0f;
	bool isJump = 0;
	float airPower = 1.0f;
	Vector3 viewLength;

	//�ړ�
	Vector3 yTmpVec = { 0, 1, 0 };
	//���ʉ��x�N�g��
	Vector3 frontTmp;
	//�E�x�N�g��
	Vector3 rightVec;
	//���x�N�g��
	Vector3 leftVec;
	//���ʃx�N�g��
	Vector3 frontVec;
	//�w�ʃx�N�g��
	Vector3 behindVec;
	float adJustMent = 0.5f;
	//�U���N�[���^�C��
	float coolTime = 0.0f;

	bool isPushZ = false;
	//�e
	//���� 
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

};