#include "dr_scene_up_button.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_grey_button_bg.h"
#include "bn_regular_bg_items_up_button_bg.h"
#include "bn_sprite_items_button_sprite.h"
#include "bn_sprite_items_oops.h"


namespace dr
{
    UpButton::UpButton(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void UpButton::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::up_button_bg.create_bg(0, 0);


        int timer = 0;

        

        while(timer < 180){
            
            
        
           
            ++timer;
            bn::core::update();
        }

    }

    bool UpButton::play_game(){
        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        bn::regular_bg_ptr map = bn::regular_bg_items::grey_button_bg.create_bg(0, 0);
        map.set_camera(camera);
        
        bn::sprite_ptr button = bn::sprite_items::button_sprite.create_sprite(0,0);
        button.set_camera(camera);

        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(0,55);
        oops.set_visible(false);

        int timer = 0;

        bool success = true;

        while(timer < 5*60){
            
            
            if(bn::keypad::a_pressed() || bn::keypad::b_pressed()){
                button.set_tiles(bn::sprite_items::button_sprite.tiles_item().create_tiles(1));
                oops.set_visible(true);
                success = false;
            }

            if(random.get() % 100 < 3){
                camera.set_y(camera.y() - 2);
            } else {
                camera.set_y(0);
            }
        
           
            ++timer;
            bn::core::update();
        }

        return success;
    }

    bool UpButton::execute(){
        show_directions();
        return play_game();
    }

    
}