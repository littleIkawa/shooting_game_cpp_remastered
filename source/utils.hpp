#pragma once

namespace utils {
    //! @brief valの小数以下point位を四捨五入する
    extern float round_point(float val, int point);
    extern float clamp(const float val, const float min, const float max);
}
