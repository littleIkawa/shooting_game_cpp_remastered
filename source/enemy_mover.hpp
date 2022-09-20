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
    //! @brief 右下へ移動
    void move_pattern_03(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_04(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_05(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_06(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_07(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_08(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_09(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_10(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_11(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_12(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_13(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_14(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_15(AbstractEnemy* enemy);
    //! @brief 右下へ移動
    void move_pattern_16(AbstractEnemy* enemy);
};

