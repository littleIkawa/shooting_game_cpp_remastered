#include <DxLib.h>
#include "enemy_manager.hpp"
#include "global_define.hpp"
#include "game_scene.hpp"
#include "enemy_a.hpp"
#include "macro.hpp"
#include "destroy_enemy_effect.hpp"

#include <fstream>
#include <sstream>

void EnemyManager::load_enemy_story(std::string filename) {
    using std::getline;
    using std::stoi;
    using std::stof;

    std::string str_buf;
    std::string data_buf;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream ifs_csv_file(filename);

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (getline(ifs_csv_file, str_buf)) {
        // /で始まっている行は読み飛ばす
        if (str_buf[0] == '/') continue;
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream i_stream(str_buf);

        int col_num = 0;
        EnemyInfo new_enemy_info{};
        // 「,」区切りごとにデータを読み込む
        while (getline(i_stream, data_buf, ',')) {
            // カラムごとにデータを処理して構造体に格納
            switch (col_num) {
            case 0: new_enemy_info.spawn_count = stoi(data_buf); break;
            case 1: new_enemy_info.move_pattern = stoi(data_buf); break;
            case 2: new_enemy_info.enemy_type = stoi(data_buf); break;
            case 3: new_enemy_info.x = stof(data_buf); break;
            case 4: new_enemy_info.y = stof(data_buf); break;
            case 5: new_enemy_info._speed = stof(data_buf); break;
            case 6: new_enemy_info.start_attack_count = stoi(data_buf); break;
            case 7: new_enemy_info.attack_pattern = stoi(data_buf); break;
            case 8: new_enemy_info.bullet_color = stoi(data_buf); break;
            case 9: new_enemy_info.hp = stoi(data_buf); break;
            case 10:new_enemy_info.bullet_id = stoi(data_buf); break;
            case 11:new_enemy_info.wait_time = stoi(data_buf); break;
            case 12:new_enemy_info.item[0] = stoi(data_buf); break;
            case 13:new_enemy_info.item[1] = stoi(data_buf); break;
            case 14:new_enemy_info.item[2] = stoi(data_buf); break;
            case 15:new_enemy_info.item[3] = stoi(data_buf); break;
            case 16:new_enemy_info.item[4] = stoi(data_buf); break;
            case 17:new_enemy_info.item[5] = stoi(data_buf); break;
            }
            ++col_num;
        }
        // 出来上がったデータ構造をリストに追加
        _enemy_info_list.push_back(new_enemy_info);
    }
}

EnemyManager::EnemyManager(GameScene* scene, std::shared_ptr<EnemyBulletManager> bullet_manager) {
    _game_scene = scene;
    //_enemy_bullet_manager = std::make_shared<EnemyBulletManager>(_game_scene);
    _enemy_bullet_manager = bullet_manager;
    // ここを変えればステージの途中から始められる
    _counter = 0;

    // csvから敵情報を読み込み
    load_enemy_story("./dat/csv/storyH0.csv");
    //_list.emplace_back(std::make_shared<EnemyA>(GlobalValues::CENTER_X, 100.0));

    for (auto enemy : _list) {
        enemy->initialize();
    }
}

void EnemyManager::push_bullet(std::shared_ptr<EnemyBullet> bullet) {
    this->_enemy_bullet_manager->push_bullet(bullet);
}

bool EnemyManager::update() {
    for (auto& enemy_info : _enemy_info_list) {
        if (enemy_info.spawn_count == _counter) {
            _list.emplace_back(std::make_shared<EnemyA>(enemy_info, this));
        }
    }
    for (auto iter = _list.begin(); iter != _list.end();) {
        if ((*iter)->update()) {
            ++iter;
        }
        else {
            // イテレータを用いてループして, updateがfalseになったものが取り除かれるように
            iter = _list.erase(iter);
        }
    }
    if (!_game_scene->boss_exist()) {
        ++_counter;
    }
    return true;
}

void EnemyManager::draw() const {
    //clsDx();
    //printfDx("enemy_manager count : %d\n", _counter);
    //DrawFormatString(0, 20, GetColor(255, 255, 255), "敵の数 : %d", _list.size());
    for (const auto enemy : _list) {
        enemy->draw();
    }
}

Vec2 EnemyManager::get_player_pos() const {
    return _game_scene->get_player_pos();
}

std::list<std::shared_ptr<AbstractEnemy>> EnemyManager::get_all_enemies_iterator() const {
    return this->_list;
}


void EnemyManager::set_destroy_effect(Vec2 pos, int color) {
    // スコア加算
    _game_scene->modify_score(150);
    auto effect = std::make_shared<DestroyEnemyEffect>(pos, color);
    _game_scene->set_effect(effect);
}
void EnemyManager::spawn_items(std::array<int, 6> items, Vec2 pos) {
    _game_scene->spawn_items(items, pos);
}
