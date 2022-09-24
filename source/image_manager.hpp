#pragma once

#include <DxLib.h>
#include <string>
#include <vector>
#include <array>
#include "singleton.hpp"

class ImageManager final : public Singleton<ImageManager> {
public:
    ImageManager();
    ~ImageManager() = default;
    void load();
    void release();

    const int* get_player_a() const;
    std::array<int, 4> get_board() const;
    int get_background() const;
    const int* get_enemy(int type) const;

    const int* get_item(int type) const;

    const int* get_numbers() const;

    const int get_player_shot(int type) const;

    const int get_enemy_bullet(int type, int color) const;

    const int get_destroy_enemy_effect(int color) const;

private:
    /**
     * @brief 画像を読み込み, そのデータへのハンドル整数を返す.
     * @return -1: 読み込み失敗. otherwise: ハンドル整数.
     */
    int app_load_graph(std::string filename);
    /**
     * @brief 画像を分割読込してbufにハンドルを保存する.
     * @return -1: 読み込み失敗. 0: 成功
     */
    int app_load_div_graph(std::string filename, int n, int xn, int yn, int width, int height, int* buf);

    //! @brief 画像ハンドルを並べて格納する配列. 一括開放を可能にする.
    std::vector<int> _images;

    //! @brief デジタル数字画像
    int _numbers[10];

    int _player_a[6];
    int _player_shot[2];
    int _board[4];
    //! @brief ポーズ状態の画像
    int _pause_bg;
    int _background;

    int _enemies[4][3];

    int _items[7][2];

    int _destroy_enemy_effect[5];

    //! @brief 6種類x6色の配列とするが, 欠けている色もある.（ただの透過画像となるので表示されない）
    int _enemy_bullet[6][6];
};
