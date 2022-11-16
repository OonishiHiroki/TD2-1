#include "Boss.h"
#include "Player.h"

Boss::Boss() {
	srand(time(NULL));
	coolTime = 0;
	attackTmp = 0;
	isImpact = false;
	speed = 0.3;
}

void Boss::Initialize(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, 3, 30 };
	worldTransform_.scale_ = { 6,4,4 };
}

void Boss::Update(Vector3 player) {

	//�d��
	if (isJump == 0) {
		if (worldTransform_.translation_.y > 3) {
			worldTransform_.translation_.y -= 1.3f;
		}
		else if (worldTransform_.translation_.y <= 3) {
			worldTransform_.translation_.y = 3.0f;
		}
	}
	//�{�X�̍s���𒊑I
	AttackPattern(player);
	if (isImpact == true) {
		Impact(player);
	}

	//�s��X�V
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
	//�f�o�b�O�e�L�X�g
	debugText_->SetPos(50, 250);
	debugText_->Printf(
		"translation : %f,%f,%f", worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
	debugText_->SetPos(50, 300);
	debugText_->Printf(
		"%f", speed);
}

void Boss::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	if (isImpact == true) {
		model_->Draw(bullet->worldTransform, viewProjection_, textureHandle_);
	}
}

void Boss::AttackPattern(Vector3 player) {
	switch (attackNum) {
		//�U���p�^�[�����I
	case 0:
		//���I
		coolTime++;
		if (coolTime == 200) {
			attackTmp = rand() % 2 + 1;
			/*attackTmp = 1;*/
		}

		//�V�[���J�ڂ̂��߂̕ϐ�������
		if (attackTmp == 1) {
			isJump = 1;
			jumpPower = 0.5f;
			coolTime = 0;
		}
		else if (attackTmp == 2) {
			coolTime = 0;
		}

		//���I���Ă����Ȃ�V�[���J��
		if (attackTmp != 0) {
			attackNum = attackTmp;
		}
		break;

	case 1:
		if (isJump == 1) {
			worldTransform_.translation_.y += jumpPower;

			jumpPower *= 1.02;
			if (jumpPower >= 0.7) {
				jumpPower = 0;
				isJump = 2;
			}
		}
		else if (isJump == 2) {
			waitTime++;
			if (waitTime == 65) {
				isJump = 0;
			}
		}

		coolTime++;
		if (coolTime >= 100) {
			if (isImpact == false) {
				bullet->worldTransform.Initialize();
				bullet->worldTransform.scale_ = { 8,1,0.5 };
				bullet->worldTransform.translation_ = { worldTransform_.translation_.x,-0.3,worldTransform_.translation_.z };
				bullet->bulletTime = 0;
				speed = 0.3;
				isImpact = true;
			}
		}
		if (coolTime == 120) {
			coolTime = 0;
			isJump = 0;
			waitTime = 0;
			attackNum = 0;
			attackTmp = 0;
		}
		break;

	case 2:
		coolTime++;
		if (coolTime == 100) {
			coolTime = 0;
			attackNum = 0;
			attackTmp = 0;
		}
		break;
	}
}

Vector3 Boss::GetWorldPos() {
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Boss::Impact(Vector3 player) {

	//y�̉��x�N�g��
	Vector3 yTmpVec = { 0, 1, 0 };
	yTmpVec.normalize();
	//���ʉ��x�N�g��
	Vector3  frontTmp = player - worldTransform_.translation_;
	frontTmp.normalize();
	//�E�x�N�g��
	Vector3  rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//���ʃx�N�g��
	Vector3  frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();

	if (bullet->bulletTime >= 50) {
		if (speed < 0.8) {
			speed += 0.025;
		}
	}

	//�e�𔭎�
	/*bullet->worldTransform.translation_.z += speed;*/
	bullet->worldTransform.translation_ += frontVec * speed;

	//
	if (bullet->worldTransform.scale_.y > 0.2) {
		bullet->worldTransform.scale_.y -= 0.01;
	}
	bullet->worldTransform.scale_.x += 0.05;

	//�s��X�V
	AffinTrans::affin(bullet->worldTransform);
	bullet->worldTransform.TransferMatrix();

	//���Ԍo�߂Œe������
	bullet->bulletTime++;
	if (bullet->bulletTime == 250) {
		/*delete bullet;*/
		isImpact = false;
	}
}

void Boss::OnCollision(){

}