#include "Bomb.h"

Bomb::Bomb()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 40;
    rect_.h = 40;

    x_val_ = 0;
    y_val_ = 0;
}

Bomb::~Bomb()
{

}

void Bomb::HandleMove()
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT)
    {
        rect_.y = 0;
        rect_.x = SDLCommonFunc::getRandomNumber(0, SCREEN_WIDTH);
    }
}
