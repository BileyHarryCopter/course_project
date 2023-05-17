#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <array>
#include <SDL2/SDL.h>
#include "Utility.hpp"

#include "Texture.hpp"
#include "Widget.hpp"
#include "Field.hpp"
#include "Die.hpp"

namespace SDLGame
{
using renderer_ptr  = SDL_Renderer*;
using texture_map_t = std::map<std::string, SDLTexture::Texture>;
using button_map_t  = std::map<std::string, SDLWidget::Button>;
using field_t       = SDLField::Field;
using die_t         = SDLDie::Die;

enum game_activity
{
    EXIT   = 0,
    ACTIVE = 1,

    IS_WAITING_ROLLING_DIE = 2,
    IS_WAITING_SRC_CELL    = 3,
    IS_WAITING_DST_CELL    = 4
};

const size_t NO_CELL = 24;

struct game_state_info {
    game_activity      activity_  = IS_WAITING_ROLLING_DIE;
    int                colour_    = SDLFeature::WHITE;
    size_t             src_cell_  = NO_CELL;
    size_t             dest_cell_ = NO_CELL;
    std::array<int, 4>      ways_ =     {0};

    void switch_colour() { colour_ *= -1; }
};

class Game
{
    game_state_info        state_;
    field_t                field_;
    texture_map_t       textures_;
    button_map_t         buttons_;
    std::pair<die_t, die_t> dies_;

public:
    //----------
    // Creation
    //----------
        Game() {}

        void loadmedia(const std::string& path, renderer_ptr renderer);
        void show_game_state_info ();

    //-----------------------
    // Work with texture map
    //-----------------------
        void set_pos_texture       (const std::string& id, int x, int y);
        void set_demension_texture (const std::string& id, int width, int height);
        void move_texture          (const std::string& id, int delta_x, int delta_y);

        void draw_texture          (const std::string& id);
        
    //-----------------
    // Work with field
    //-----------------
        void move_feature (size_t cell, size_t steps) { field_.move_feature(cell, steps); }
    private:
        void draw_field() { field_.draw_all(); }
    public:

    //----------------
    // Work with dies
    //----------------
        bool is_dies_active(SDL_Event * event);
        std::pair<int, int> dies_status();
    
    //----------
    // Draw all
    //----------
        void draw();

    //------------------
    // Work with events
    //------------------
        void handle_event (SDL_Event* event);

        game_state_info get_state() { return state_; }

        bool is_active ()    { return state_.activity_ == game_activity::ACTIVE; }
        bool is_nonactive()  { return state_.activity_ == game_activity::EXIT; }
};

}

#endif