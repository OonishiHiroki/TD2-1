#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "affin.h"
#include "Player.h"
#include "Boss.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "EnemyBullet.h"
#include <sstream>
#include <DirectXMath.h>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public:
	// メンバ関数
	/// <summary>
	/// コンストクラタ
	GameScene();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdataEnemyPopCommands();

	/// <summary>
	/// 敵の発生
	/// </summary>
	void GenerEnemy(Vector3 EnemyPos);

	//シーン切り替え
	enum class SceneNo {
		Title, //タイトル
		Operate, //操作説明(チュートリアル)
		Game,  //射撃
		Clear, //ゲームクリア
		Over   //ゲメオーバー
	};

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//タイトル
	uint32_t bgmHandle = 0;
	int soundHandle = -1;
	//戦闘
	uint32_t bgmHandle2 = 0;
	int soundHandle2 = -1;
	//クリア
	uint32_t bgmHandle3 = 0;
	int soundHandle3 = -1;
	//オーバー
	uint32_t bgmHandle4 = 0;
	int soundHandle4 = -1;
	// UI音
	uint32_t bgmDecision = 0;
	uint32_t bgmRock = 0;


	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle1_ = 0;
	uint32_t textureHandle2_ = 0;

	// タイトル
	std::unique_ptr<Sprite> spriteTitle;
	//ゲームクリア
	std::unique_ptr<Sprite> spriteClear;
	//ゲームオーバー
	std::unique_ptr<Sprite> spriteOver;

	// 3Dモデル
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//カメラ上方向
	float viewAngle = 0.0f;

	//自キャラ
	Player* player_ = nullptr;
	int playerRadius = 1;
	int playerBulletRadius = 1;

	//ボス
	Boss* boss_ = nullptr;
	int bossRadius = 5;
	
	

	//スカイドーム
	Skydome* skydome_ = nullptr;
	//3Dモデル
	Model* modelSkydome_ = nullptr;

	//レールカメラ
	RailCamera* railCamera_ = nullptr;

	Vector3 vector3(float x, float y, float z);
	Vector4 vector4(int x, int y, int z, int w);

	//待機中フラグ
	bool isStand_ = false;

	//待機タイマー
	int standTime_ = 0;

	/*SceneNo sceneNo_ = SceneNo::Title;*/

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//カメラターゲット
	WorldTransform target_;

	//ベジェ点2と点3
	WorldTransform targetSide1;
	WorldTransform targetSide2;

	//ブーメラン
	WorldTransform boomerang_;

	//ブーメラン(ベジェ)フラグ
	bool bezierMode;

	//ベジェタイマー
	int timer = 0;

	//ベジェに必要な変数
	int splitNum = 100;
	float t = 0;

};