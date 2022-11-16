#pragma once
#include "math/Vector3.h"
#include <Model.h>
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include <affin.h>

//�����蔻��pAABB
typedef struct AABB {
	Vector3 min_;
	Vector3 size_;
};

class PlayerBullet {
  public:
	///< summary>
	///������
	///</summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	///< summary>
	///������
	///</summary>
	void Update();

	///< summary>
	///������
	///</summary>
	void Draw(const ViewProjection& viewProjection);

	bool CheckHit(Vector3 boss);

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();


  public:
	bool InDead() const { return isDead_; }
	int GetR() { return r; }

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
	
	//����
	static const int32_t kLifeTime = 60 * 3;
	//�f�X�喃
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
	int r = 2;
	
};
