#include "dr_scene_finish.h"

#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_log.h"
#include "bn_keypad.h"
#include "bn_format.h"
#include "bn_string.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_regular_bg_items_finish_bg.h"
#include "bn_sprite_items_rolling.h"

#include "bn_sprite_items_twinkle.h"
#include "bn_sprite_items_explosion.h"
#include "bn_sprite_items_burn_mark.h"

namespace dr
{
    Finish::Finish(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void Finish::execute(int successes){

        int success_min = 8;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::regular_bg_ptr map = bn::regular_bg_items::finish_bg.create_bg(0, 0);
        map.set_camera(camera);

        // van sprite
        bn::sprite_ptr van = bn::sprite_items::rolling.create_sprite(0, -200, 1);
        van.set_camera(camera);

        // twinkle
        bn::sprite_ptr twinkle = bn::sprite_items::twinkle.create_sprite(4, -8);
        twinkle.set_visible(false);
        bn::optional<bn::sprite_animate_action<3>> twinkle_action;

        // boom
        bn::sprite_ptr boom = bn::sprite_items::explosion.create_sprite(0, 0);
        boom.set_visible(false);
        bn::optional<bn::sprite_animate_action<10>> boom_action;

        // burn mark
        bn::sprite_ptr burn = bn::sprite_items::burn_mark.create_sprite(0, 18);
        burn.set_visible(false);
    
        int timer = 0;
        bool hit = false;
        bool effect_played = false;

        _text_generator->set_center_alignment();

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        while(!bn::keypad::start_pressed()){
            if(!hit){
                van.set_y(van.y() + 3);
                if(van.y() >= 0){
                    van.set_y(0);
                    hit = true;
                    van.set_tiles(bn::sprite_items::rolling.tiles_item().create_tiles(0));
                    camera.set_y(-10);
                    _text_generator->generate(0, 40,  bn::to_string<32>(successes) + " / 11", text_sprites);
                }
            }

            if(timer > 180 && !effect_played){
                effect_played = true;
                if(successes >=  success_min){
                    twinkle.set_visible(true);
                    twinkle_action = bn::create_sprite_animate_action_once(
                        twinkle, 6, bn::sprite_items::twinkle.tiles_item(), 
                        0,1,0);
                    _text_generator->generate(0, 56,  "Great Job!", text_sprites);
                } else {
                    boom.set_visible(true);
                    boom_action = bn::create_sprite_animate_action_once(
                        boom, 2, bn::sprite_items::explosion.tiles_item(), 
                        0,1,2,3,4,5,6,7,8,9);
                    burn.set_bg_priority(3);
                    burn.set_visible(true);
                    van.set_visible(false);
                    _text_generator->generate(0, 56,  "Ooof", text_sprites);
                }
            }

            if(twinkle_action.has_value() && !twinkle_action->done()){
                twinkle_action->update();
            } else if(twinkle_action.has_value() && twinkle_action->done()){
                twinkle.set_visible(false);
            }
            if(boom_action.has_value() && !boom_action->done()){
                boom_action->update();
            }
            
            camera.set_y(camera.y() + (0-camera.y())/2);

            ++timer;
            bn::core::update();
        }
    }

    
}