#include "dr_scene_left_rocks.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_left_bg.h"
#include "bn_regular_bg_items_green_rocks_bg.h"
#include "bn_sprite_items_rolling_top.h"
#include "bn_sprite_items_rocks.h"
#include "bn_sprite_items_oops.h"

namespace dr
{
    LeftRocks::LeftRocks(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void LeftRocks::show_directions()
    {
        
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::left_bg.create_bg(0, 0);

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        int timer = 0;
        
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool LeftRocks::play_game(){
        int timer = 0;
        bool success = true;
        bool hit = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::green_rocks_bg.create_bg(0, 0);
        map.set_camera(camera);

        //person
        bn::sprite_ptr van = bn::sprite_items::rolling_top.create_sprite(-150,0);
        van.set_rotation_angle(270);
        van.set_camera(camera);
        bn::sprite_animate_action<64> rolling_action = bn::create_sprite_animate_action_forever(van, 0.2, bn::sprite_items::rolling_top.tiles_item(), 0, 1, 2, 3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
                    35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,
                    59,60,61,62,63);

        //oops
        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(50, -35);
        oops.set_rotation_angle(270);
        oops.set_bg_priority(0);
        oops.set_visible(false);

        // rocks
        bn::sprite_ptr rocks[3] = {
            bn::sprite_items::rocks.create_sprite(0,0,1),
            bn::sprite_items::rocks.create_sprite(0,0,0),
            bn::sprite_items::rocks.create_sprite(0,0,2),
        };
        rocks[0].set_position(bn::fixed_point(-30, -40));
        rocks[1].set_position(bn::fixed_point(40, 0));
        rocks[2].set_position(bn::fixed_point(90, 40));
        for(bn::sprite_ptr rock : rocks){
            rock.set_rotation_angle(270);
            rock.set_camera(camera);
            oops.set_bg_priority(3);
        }
        

        while (timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }
            
            if(!hit){
                rolling_action.update();
                van.set_x(van.x() + 2);
                if(bn::keypad::up_held() && van.y() > -60){ //left
                    van.set_y(van.y() -2);
                }

                if(bn::keypad::down_held() && van.y() < 60){ //down
                    van.set_y(van.y() +2);
                }

                for(bn::sprite_ptr rock : rocks){
                    if(bn::abs(van.x() - rock.x()) < 20){
                        if(bn::abs(van.y() - rock.y()) < 20){
                            hit = true;
                            oops.set_visible(true);
                            success = false;
                        }
                    }
                    // cut.set_x(cut.x() - 4);
                }
            }
            

            bn::core::update();
            ++timer;
        }

        return success;
    }

    bool LeftRocks::execute(){
        show_directions();
        return play_game();
    }
    
}