#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunction.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void SetRect(const int& x, const int& y) {rect_.x = x; rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object_;}
    void Render(SDL_Renderer* des);
    void Free();
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif // BASE_OBJECT_H

