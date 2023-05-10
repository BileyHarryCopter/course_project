#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "Texture.hpp"

namespace SDLGameObject
{
using texture = SDLTexture::Texture;
using point_t = SDLTexture::point_t;

enum Activity {
    ACTIVE     = 1,
    NON_ACTIVE = 0
};

class GameObject
{
    texture   texture_;
    Activity activity_;

public:
    GameObject (const texture& rhs) : texture_(rhs), activity_(NON_ACTIVE) { }
    virtual ~GameObject() {} 

    GameObject (const GameObject& rhs) : texture_(rhs.texture_), activity_(rhs.activity_) { }

    void set_texture_pos (point_t new_pos) { texture_.set_pos(new_pos); }

    void draw () { texture_.draw(); }

    void dump () {
        texture_.simple_dump();
        std::cout << "Activity = " << activity_ << std::endl;
    }  

    int     get_texture_w   () { return texture_.get_w(); }
    int     get_texture_h   () { return texture_.get_h(); }
    point_t get_texture_pos () { return texture_.get_pos(); }
};

} 

#endif
