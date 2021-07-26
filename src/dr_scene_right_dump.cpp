#include "dr_scene_right_dump.h"

#include "bn_core.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_right_dump_bg.h"
#include "bn_regular_bg_items_green_dump_bg.h"
#include "bn_sprite_items_nice.h"
#include "bn_sprite_items_grill.h"
#include "bn_sprite_items_button_dump.h"


namespace dr
{
    RightDump::RightDump(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void RightDump::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::right_dump_bg.create_bg(0, 0);
        
        int timer = 0;
        
        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool RightDump::play_game(){
        int timer = 0;
        bool success = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::green_dump_bg.create_bg(0, 0);
        map.set_camera(camera);

        //buton
        bn::sprite_ptr button = bn::sprite_items::button_dump.create_sprite(-20, 0,0);
        button.set_rotation_angle(90);

        //nice
        bn::sprite_ptr nice = bn::sprite_items::nice.create_sprite(90, -50);
        nice.set_rotation_angle(90);
        nice.set_visible(false);

        //grill
        bn::sprite_ptr grill = bn::sprite_items::grill.create_sprite(45, 0);
        grill.set_visible(false);
        grill.set_scale(0.8);

        while (timer < 5 * 60){
            

            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }

            if(!success){
                if(bn::keypad::a_pressed() || bn::keypad::b_pressed()){
                    //open
                    button.set_tiles(bn::sprite_items::button_dump.tiles_item().create_tiles(1));
                    grill.set_visible(true);
                    nice.set_visible(true);
                    success = true;
                }
                
                
            }else{
                grill.set_rotation_angle(grill.rotation_angle()+ 0.5);
                grill.set_x(grill.x() +1);
            }

            bn::core::update();
            ++timer;
        }
        return success;
    }

    bool RightDump::execute(){
        show_directions();
        return play_game();
    }

    
}