#include "Player.h"

Player::Player()
{
    rect_.x = 400;
    rect_.y = 450;
    rect_.w = BASKET_WIDTH;
    rect_.h = BASKET_HEIGHT;
    x_val_ = rect_.x;
    y_val_ = rect_.y;

}

Player::~Player()
{

}

void Player::HandleInputAction(SDL_Event events)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        /*case SDLK_UP:
            if (y_val_ - BASKET_HEIGHT/2 >=0 ) y_val_ -= BASKET_HEIGHT/2;
            break;
        case SDLK_DOWN:
            if (y_val_ + BASKET_HEIGHT/2 <= 450 ) y_val_ += BASKET_HEIGHT/2;
            break;*/
        case SDLK_LEFT:
            if (x_val_  > 0 ) x_val_ -= BASKET_WIDTH/2;
            break;
        case SDLK_RIGHT:
            if (x_val_ + BASKET_WIDTH < SCREEN_WIDTH ) x_val_ += BASKET_WIDTH/2;
            break;

        default:
            break;
        }
    }
}

void Player::HandleMove()
{
    rect_.x = x_val_;
    rect_.y = y_val_;

}
