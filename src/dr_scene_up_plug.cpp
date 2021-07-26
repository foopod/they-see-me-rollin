#include "dr_scene_up_plug.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_blue_plug_bg.h"
#include "bn_regular_bg_items_up_plug_bg.h"
#include "bn_sprite_items_nice.h"
#include "bn_sprite_items_plug.h"


namespace dr
{
    UpPlug::UpPlug(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void UpPlug::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::up_plug_bg.create_bg(0, 0);


        int timer = 0;

        

        while(timer < 180){
            
            
        
           
            ++timer;
            bn::core::update();
        }

    }

    bool UpPlug::play_game(){
        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // socket
        bn::regular_bg_ptr map = bn::regular_bg_items::blue_plug_bg.create_bg(0, 0);
        map.set_camera(camera);
        
        // plug
        bn::sprite_ptr plug = bn::sprite_items::plug.create_sprite(0,0);
        plug.set_camera(camera);

        bn::sprite_ptr nice = bn::sprite_items::nice.create_sprite(0,40);
        nice.set_visible(false);

        int timer = 0;

        bool success = false;
        bool connected = false;

        while(timer < 5*60){
            
            if(random.get() % 100 < 3){
                camera.set_y(camera.y() - 2);
            } else {
                camera.set_y(0);
            }


            if(!connected){
                if(bn::keypad::up_held()){
                    plug.set_y(plug.y() - 1);
                }
                if(bn::keypad::right_held()){
                    plug.set_x(plug.x() + 1);
                }
                if(bn::keypad::down_held()){
                    plug.set_y(plug.y() + 1);
                }
                if(bn::keypad::left_held()){
                    plug.set_x(plug.x() - 1);
                }

                if(bn::abs(plug.x() - 40) < 5){
                    if(bn::abs(plug.y() - -28) < 5){
                        plug.set_x( 40);
                        plug.set_y( -28);
                        connected = true;
                        nice.set_visible(true);
                        success = true;
                    }
                }
            }
        
           
            ++timer;
            bn::core::update();
        }

        return success;
    }

    bool UpPlug::execute(){
        show_directions();
        return play_game();
    }

    
}