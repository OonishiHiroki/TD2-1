#include "Enemy.h"
#include "Player/Player.h"
#include <GameScene.h>
#include <cmath>

Enemy::Enemy() {}

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 5,5,5 };

	//�������W���Z�b�g
	worldTransform_.translation_ = { 0,0,30 };
}

void Enemy::Update() {

	////�G�̈ړ��̑���
	//const float kCharacterSpeed = 0.09f;
	//const float kCharacterSpeed2 = 0.1f;


	////�s��X�V
	//AffinTrans::affin(worldTransform_);

	//worldTransform_.TransferMatrix();

	////�ړ�(�x�N�g�������Z)
	//if (isChangeFlag == 0) {
	//	worldTransform_.translation_ += {kCharacterSpeed, 0, 0};
	//}
	//else if (isChangeFlag == 1) {
	//	worldTransform_.translation_ += {-kCharacterSpeed2, 0, 0};
	//}

	//if (worldTransform_.translation_.x >= 8.0f && isChangeFlag == 0) {
	//	isChangeFlag = 1;
	//}
	//else if (worldTransform_.translation_.x <= -8.0f && isChangeFlag == 1) {
	//	isChangeFlag = 0;
	//}

	debugText_->SetPos(50, 250);
	debugText_->Printf(
		"Enemytranslation : %f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
		worldTransform_.translation_.z);
}

void Enemy::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

Vector3 Enemy::GetWorldPosition() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() { isDead_ = true; }
