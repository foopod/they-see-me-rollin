#include "dr_scene_right_fridge.h"

#include "bn_core.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_right_fridge_bg.h"
#include "bn_regular_bg_items_green_fridge_bg.h"
#include "bn_sprite_items_oops.h"
#include "bn_sprite_items_no_squish.h"


namespace dr
{
    RightFridge::RightFridge(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void RightFridge::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::right_fridge_bg.create_bg(0, 0);
        
        int timer = 0;
        
        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool RightFridge::play_game(){
        int timer = 0;
        bool success = true;
        bool failed = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::green_fridge_bg.create_bg(0, -40);
        map.set_camera(camera);

        bn::sprite_ptr no_squish = bn::sprite_items::no_squish.create_sprite(-80,35);

        //oops
        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(-60, -35);
        oops.set_rotation_angle(90);
        oops.set_visible(false);

        while (timer < 5 * 60){
            

            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }

            if(!failed){
                map.set_y(map.y() + 1);
                if(bn::keypad::a_pressed() || bn::keypad::b_pressed()){
                    map.set_y(map.y() - 10);
                    if(map.y() < -40){
                        map.set_y(-40);
                    }
                }
                
                if(map.y() >40){
                    failed = true;
                    success = false;
                    oops.set_visible(true);
                }
            }

            bn::core::update();
            ++timer;
        }
        return success;
    }

    bool RightFridge::execute(){
        show_directions();
        return play_game();
    }

    
}