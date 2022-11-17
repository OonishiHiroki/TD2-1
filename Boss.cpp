#include "Boss.h"

Boss::Boss() {
	srand(time(NULL));
}

void Boss::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, 3, 30 };
	worldTransform_.scale_ = { 6,4,4 };

	//メンバ変数
	coolTime = 0;
	attackTmp = 0;
	isImpact = false;
	isJump = 0;
	speed = 0.3;
	hp = 30;
	isDead = false;
	isHit = false;
	hitTime = 0;
	tackleTime = 0;
	isTackle = false;
}

void Boss::Update(Vector3 player,Vector3 scale) {

	//重力
	if (isJump == 0) {
		if (worldTransform_.translation_.y > 3) {
			worldTransform_.translation_.y -= 1.3f;
		}
		else if (worldTransform_.translation_.y <= 3) {
			worldTransform_.translation_.y = 3.0f;
		}
	}
	//ボスの行動を抽選
	AttackPattern(player);
	if (isImpact == true) {
		Impact();
	}
	if (isTackle == true) {
		Tackle();
	}

	if (isHit == true) {
		hitTime++;
		if (hitTime == 15) {
			isHit = false;
			hitTime = 0;
		}
	}

	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
	//デバッグテキスト
	debugText_->SetPos(50, 250);
	debugText_->Printf(
		"translation : %f,%f,%f", worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
	debugText_->SetPos(50, 300);
	debugText_->Printf(
		"%d", attackNum);
}

void Boss::Draw(ViewProjection viewProjection_) {
	if (isHit == false) {
		model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	}
	else {
		if (hitTime % 3 != 0) {
			model_->Draw(worldTransform_, viewProjection_, textureHandle_);
		}
	}
	if (isImpact == true) {
		model_->Draw(bullet->worldTransform, viewProjection_, textureHandle_);
	}
}

void Boss::AttackPattern(Vector3 player) {
	switch (attackNum) {
		//攻撃パターン抽選
	case 0:
		//抽選
		coolTime++;
		if (coolTime == 200) {
			attackTmp = rand() % 2 + 1;
		}

		//シーン遷移のための変数初期化
		if (attackTmp == 1) {
			isJump = 1;
			jumpPower = 0.5f;
			coolTime = 0;
		}
		else if (attackTmp == 2) {
			coolTime = 0;
		}

		//抽選していたならシーン遷移
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
				playerTmp = player;
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
		if (coolTime == 20) {
			isTackle = true;
			playerTmp = player;
			bossTmp = worldTransform_.translation_;
		}
		if (coolTime == 120) {
			coolTime = 0;
			attackNum = 0;
			attackTmp = 0;
		}
		break;
	}
}

Vector3 Boss::GetWorldPos() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Boss::Impact() {


	//yの仮ベクトル
	Vector3 yTmpVec = { 0, 1, 0 };
	yTmpVec.normalize();
	//正面仮ベクトル
	Vector3  frontTmp = playerTmp - worldTransform_.translation_;
	frontTmp.normalize();
	//右ベクトル
	Vector3  rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//正面ベクトル
	Vector3  frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();


	if (bullet->bulletTime >= 50) {
		if (speed < 0.8) {
			speed += 0.025;
		}
	}

	//弾を発射
	bullet->worldTransform.translation_ += frontVec * speed;

	//
	if (bullet->worldTransform.scale_.y > 0.2) {
		bullet->worldTransform.scale_.y -= 0.01;
	}
	bullet->worldTransform.scale_.x += 0.05;

	//行列更新
	AffinTrans::affin(bullet->worldTransform);
	bullet->worldTransform.TransferMatrix();

	//時間経過で弾を消す
	bullet->bulletTime++;
	if (bullet->bulletTime == 250) {
		/*delete bullet;*/
		isImpact = false;
	}
}

void Boss::OnCollision(){
	hp--;
	isHit = true;
	if (hp == 0) {
		isDead = true;
	}
}

int Boss::CheckHit(Vector3 player,Vector3 scale) {
	//弾座標
	float blx = bullet->worldTransform.translation_.x - bullet->worldTransform.scale_.x;
	float brx = bullet->worldTransform.translation_.x + bullet->worldTransform.scale_.x;
	float bty = bullet->worldTransform.translation_.y + bullet->worldTransform.scale_.y;
	float bby = bullet->worldTransform.translation_.y - bullet->worldTransform.scale_.y;
	float bfz = bullet->worldTransform.translation_.z - bullet->worldTransform.scale_.z;
	float bbz = bullet->worldTransform.translation_.z + bullet->worldTransform.scale_.z;
	//プレイヤー座標
	float plx = player.x - scale.x;
	float prx = player.x + scale.x;
	float pty = player.y + scale.y;
	float pby = player.y - scale.y;
	float pfz = player.z - scale.z;
	float pbz = player.z + scale.z;
	if (isImpact == true) {
		//右
		if (blx < plx && brx > plx && bfz < pfz && pfz < bbz && bty > pby) {
			return true;
		}
		else if (blx < plx && brx > plx && bfz < pbz && pbz < bbz && bty > pby) {
			return true;
		}
		//左
		else if (blx < prx && brx > prx && bfz < pfz && pfz < bbz && bty > pby) {
			return true;
		}
		else if (blx < prx && brx > prx && bfz < pbz && pbz < bbz && bty > pby) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Boss::Tackle() {
	//yの仮ベクトル
	Vector3 yTmpVec = { 0, 1, 0 };
	yTmpVec.normalize();
	//正面仮ベクトル
	Vector3  frontTmp = playerTmp - worldTransform_.translation_;
	frontTmp.normalize();
	Vector3 BackHomeTmp = bossTmp - worldTransform_.translation_;
	BackHomeTmp.normalize();
	//右ベクトル
	Vector3  rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	Vector3  rightHome = yTmpVec.cross(BackHomeTmp);
	rightVec.normalize();
	//正面ベクトル
	Vector3  frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
	Vector3  BackHome = rightHome.cross(yTmpVec);
	BackHome.normalize();
	if (tackleTime < 5) {
		worldTransform_.translation_.z += 0.5f;
	}
	else if (tackleTime < 10) {
		worldTransform_.rotation_.x = frontVec.x / PI;
	}
	else if (tackleTime >= 50 && tackleTime < 75) {
		worldTransform_.translation_ += frontVec*2.5;
	}
	else if(tackleTime > 85) {
		worldTransform_.translation_ += BackHome * 0.5f;
		Vector3 len = bossTmp - worldTransform_.translation_;
		len.length();
		if (len.z <= 0.5 && len.x <= 0.5) {
			worldTransform_.translation_ = { 0, 3, 30 };
			tackleTime = 0;
			isTackle = false;
		}
	}
	tackleTime++;
}