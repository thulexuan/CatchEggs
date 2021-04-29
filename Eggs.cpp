#include "Eggs.h"

Eggs::Eggs()
{
    rect_.x = SCREEN_WIDTH / 4;
    rect_.y = 0;
    rect_.w = EGG_WIDTH;
    rect_.h = EGGS_HEIGHT;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = true;

}

Eggs::~Eggs()
{

}

void Eggs::HandleMove()
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT )
    {
        rect_.y = 0;
        rect_.x = SDLCommonFunc::getRandomNumber(0, SCREEN_WIDTH);
    }
}


