#include "NoteEnemy.hpp"
#include "Scene/RhythmGameConfig.hpp"
#include "Engine/GameEngine.hpp"
#include "Scene/RhythmGameScene.hpp"
#include "Engine/LOG.hpp"
NoteEnemy::NoteEnemy(int lane, float appearTime) :
    Sprite("play/qKao1.png", LANE_START_X + lane * LANE_WIDTH, NOTE_START_Y),
    lane(lane), appearTime(appearTime) {
    Anchor = Engine::Point(0.5, 0.5);
    Engine::LOG(Engine::INFO) << "[DEBUG] Loading image: Resource/images/play/qKao.png";
}


void NoteEnemy::Update(float deltaTime) {
    if (!Visible) return;

    auto* scene = dynamic_cast<RhythmGameScene*>(Engine::GameEngine::GetInstance().GetScene("rhythm"));
    float currentTime = scene->GetCurrentTime() / 20000.0f;

    float timeSinceAppear = (currentTime - appearTime) / 1000.0f; 

    // 如果還沒到出現時間，不動作
    if (timeSinceAppear < 0) return;

    // 計算 Y 座標：從 NOTE_START_Y 開始下落
    Position.y = NOTE_START_Y + NOTE_SPEED * (timeSinceAppear) ;
    //Engine::LOG(Engine::INFO) << "[DEBUG] Note y = " << Position.y;
    //Engine::LOG(Engine::INFO) << "[Note] lane = " << lane << ", y = " << Position.y << ", t = " << timeSinceAppear;

    // 超出畫面後設為不可見
    if (Position.y > TARGET_Y + 300) {
        Visible = false;
        /**/
        Engine::LOG(Engine::INFO) << "[NoteEnemy::Update] y = " << Position.y
                          << ", appearTime = " << appearTime
                          << ", currentTime = " << currentTime;
        
    }

    Sprite::Update(deltaTime);
}
