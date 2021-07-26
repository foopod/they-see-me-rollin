#include "dr_scene_left_fryer.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_left_fryer_bg.h"
#include "bn_regular_bg_items_purple_fryer_bg.h"
#include "bn_sprite_items_fryer_cover.h"
#include "bn_sprite_items_nice.h"

namespace dr
{
    LeftFryer::LeftFryer(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void LeftFryer::show_directions()
    {
        
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::left_fryer_bg.create_bg(0, 0);

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        int timer = 0;
        
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool LeftFryer::play_game(){
        int timer = 0;
        bool success = false;
        bool connected = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::purple_fryer_bg.create_bg(0, 0);
        map.set_camera(camera);

        //fryer
        bn::sprite_ptr fryer_cover_top = bn::sprite_items::fryer_cover.create_sprite(40,40-32,0);
        fryer_cover_top.set_camera(camera);
        bn::sprite_ptr fryer_cover_bottom = bn::sprite_items::fryer_cover.create_sprite(40,40+32,1);
        fryer_cover_bottom.set_camera(camera);

        // nice
        bn::sprite_ptr nice = bn::sprite_items::nice.create_sprite(70,35);
        nice.set_rotation_angle(270);
        nice.set_visible(false);
    
        while (timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }

            if(!connected){
                if(bn::keypad::up_held()){
                    fryer_cover_top.set_y(fryer_cover_top.y() - 1);
                    fryer_cover_bottom.set_y(fryer_cover_bottom.y() - 1);
                }
                if(bn::keypad::right_held()){
                    fryer_cover_top.set_x(fryer_cover_top.x() + 1);
                    fryer_cover_bottom.set_x(fryer_cover_bottom.x() + 1);
                }
                if(bn::keypad::down_held()){
                    fryer_cover_top.set_y(fryer_cover_top.y() + 1);
                    fryer_cover_bottom.set_y(fryer_cover_bottom.y() + 1);
                }
                if(bn::keypad::left_held()){
                    fryer_cover_top.set_x(fryer_cover_top.x() - 1);
                    fryer_cover_bottom.set_x(fryer_cover_bottom.x() - 1);
                }

                if(bn::abs(fryer_cover_top.x() - -21) < 5){
                    if(bn::abs(fryer_cover_top.y() - -67) < 5){
                        fryer_cover_top.set_x( -21);
                        fryer_cover_top.set_y( -67);
                        fryer_cover_bottom.set_x( -21);
                        fryer_cover_bottom.set_y( -67+64);
                        connected = true;
                        nice.set_visible(true);
                        success = true;
                    }
                }
            }
            
            bn::core::update();
            ++timer;
        }

        return success;
    }

    bool LeftFryer::execute(){
        show_directions();
        return play_game();
    }
    
}