#include "bullet_path.h"
#include "data.h"

Vec2 Paths::ThetaMag::loc(int t) {
    return v * (double)t;
}

Vec2 Paths::VelAcc::loc(int t) {
    return vel * (double)t + acc * (double)t*t/2.0;
}
