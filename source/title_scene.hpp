#pragma once

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "abstract_scene.hpp"
#include "abstract_bg.hpp"

class TitleScene : public AbstractScene {
public:
    TitleScene(IOnSceneChangedListener* impl, const SceneParameter& param);
    virtual ~TitleScene() = default;

    bool update() override;
    void draw() const override;

private:
    std::shared_ptr<AbstractBackground> _background;
    int _cursor_pos;

    std::vector<std::pair<std::string, int>> _option_list;
};
