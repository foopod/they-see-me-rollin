#include "dr_scene_intro.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_log.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_regular_bg_items_downhill_bg.h"
#include "bn_sprite_items_rolling.h"


namespace dr
{
    Intro::Intro(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}


    void Intro::execute(){

        bn::random random = bn::random();

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::downhill_bg.create_bg(-6, 6);

        _text_generator->set_center_alignment();
        // _text_generator->generate(0, -50, "Don't Drop Me", text_sprites);
        _text_generator->generate(0, 60, "press START when ready", text_sprites);

        // van sprite
        bn::sprite_ptr van = bn::sprite_items::rolling.create_sprite(0, 0);
        bn::sprite_animate_action<64> rolling_action = bn::create_sprite_animate_action_forever(van, 0.2, bn::sprite_items::rolling.tiles_item(), 0, 1, 2, 3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
                    35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,
                    59,60,61,62,63);

        bool reverse = true;

        while(!bn::keypad::start_pressed()){
            rolling_action.update();
            if(reverse){
                van.set_y(van.y() + (25-van.y())/70);
                if(van.y() >= 15){
                    reverse = !reverse;
                }
            }else {
                van.set_y(van.y() + (-25-van.y())/30);
                if(van.y() <= -20){
                    reverse = !reverse;
                }
            }
            
            map.set_x(map.x() - 2);
            map.set_y(map.y() - 2);

            bn::core::update();
        }
    }

    
}