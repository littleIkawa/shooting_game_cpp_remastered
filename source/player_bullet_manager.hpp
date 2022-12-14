#pragma once

#include <memory>
#include <list>
#include "task.hpp"
#include "euclid_vec.hpp"

class GameScene;
class Player;
class PlayerBullet;

class PlayerBulletManager : public Task {
public:
    PlayerBulletManager(GameScene* scene);
    virtual ~PlayerBulletManager() = default;
    bool update() override;
    void draw() const override;

    void push_bullet(int power, Vec2 pos);

private:
    //! @brief 敵との当たり判定を行い, 敵にダメージを与える命令と自機弾を消滅させる命令を送る.
    void collision_against_enemies();
    void collision_against_boss();

    GameScene* _game_scene;
    int _counter;
    std::list<std::shared_ptr<PlayerBullet>> _bullet_list;
};
