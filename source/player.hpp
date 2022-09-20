#pragma once

#include "task.hpp"
#include "euclid_vec.hpp"

class Player : public Task {
public:
    Player();
    virtual ~Player() = default;
    bool update() override;
    void draw() const override;

private:
    void move();

    Vec2 _pos;
    int _counter;
    //! @brief このフレームでの移動方向.
    Vec2 _move_dir;
};
