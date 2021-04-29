#ifndef BOMB_H
#define BOMB_H

#include "CommonFunction.h"
#include "BaseObject.h"

class Bomb : public BaseObject
{
public:
   Bomb();
   ~Bomb();
   void HandleMove();
   void set_y_val(const int& yVal) {y_val_ = yVal;}
   int get_y_val() const {return y_val_;}
private:
    int x_val_;
    int y_val_;
};

#endif // BOMB_H
