#pragma once

#include <vector>
#include <memory>

// abstract_enemy.hppでenemy_mover.hppを読み込んでおり循環参照になるので, 型名だけ宣言しておき後で解決してもらう.
class AbstractEnemy;

class EnemyMover {
public:
    EnemyMover();
    virtual ~EnemyMover() = default;
    void move(AbstractEnemy* enemy);

private:
    using MoveFunc = void(EnemyMover::*)(AbstractEnemy* enemy);
    std::vector<MoveFunc> _move_pattern;

    //! @brief 下がって止まり、また下がる
    void move_pattern_00(AbstractEnemy* enemy);
    //! @brief 左下へ移動
    void move_pattern_01(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_02(AbstractEnemy* enemy);
};

