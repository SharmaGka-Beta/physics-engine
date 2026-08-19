#pragma once

#include "ball.h"


class Collision{

    public:
        static void worldBorder(Ball&, float);
        static void ballToBall(Entity&, Entity&, float);

};