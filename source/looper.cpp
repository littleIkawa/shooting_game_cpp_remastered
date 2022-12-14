#include "looper.hpp"
#include "error.hpp"
#include "macro.hpp"
#include "keyboard.hpp"
#include "pad_input.hpp"
#include "image_manager.hpp"
#include "se_manager.hpp"

#include "title_scene.hpp"
#include "level_select_scene.hpp"
#include "game_scene.hpp"
#include "result_scene.hpp"

Looper::Looper() {
    // アセットロード
    ImageManager::get_instance()->load();
    SceneParameter param;
    // タイトルシーンを作成して追加し初期化
    // Looperはリスナー抽象クラスを継承しており, シーンのリスナーにはthisポインタを渡す.
    _scene_stack.push(std::make_shared<TitleScene>(this, param));
    // ゲームから始めるときはゲームシーンを作成して追加
    //_scene_stack.push(std::make_shared<GameScene>(this, param));
}

/**
 * @brief スタックの一番上にあるシーンについて処理を行う
 */
bool Looper::loop() {
    Keyboard::get_instance()->update();
    PadInput::get_instance()->update();
    // 各シーンのupdateでfalseが返ってきた場合ゲームを終了する.
    bool update_result = _scene_stack.top()->update();
    if (!update_result) return false;
    _scene_stack.top()->draw();
    SoundEffectManager::get_instance()->play_se();
    _frm.draw();
    // このwaitにより一定時間間隔でupdateやdrawが実行されることになる.
    _frm.wait();
    return true;
}


void Looper::pop_scene() {
    if (_scene_stack.empty()) APP_SYSTEM_ERROR("シーンスタックは空のためポップできません.");
    _scene_stack.pop();
}
/**
 * @brief シーン変更（各シーンからコールバックとして呼び出される）
 * @param scene 変更先のシーン
 * @param parameter 前のシーンから引き継ぐパラメータ
 * @param stackClear 現在のシーンのスタックをクリアするか
 */
void Looper::on_scene_changed(const AppScenes scene, const SceneParameter& param, const bool stack_clear) {
    if (stack_clear) {
        while (!_scene_stack.empty()) {
            _scene_stack.pop();
        }
    }
    switch (scene)
    {
    case Title:
        _scene_stack.push(std::make_shared<TitleScene>(this, param));
        break;
    case LevelSelect:
        _scene_stack.push(std::make_shared<LevelSelectScene>(this, param));
        break;
    case Game:
        _scene_stack.push(std::make_shared<GameScene>(this, param));
        break;
    case Result:
        _scene_stack.push(std::make_shared<ResultScene>(this, param));
        break;
        //case Staffroll:
            //break;
    default:
        APP_SYSTEM_ERROR("シーンエラー");
        break;
    }
}