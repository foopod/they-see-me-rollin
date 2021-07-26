#include "dr_scene_left_cutlery.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_left_bg.h"
#include "bn_regular_bg_items_yellow_cutlery_bg.h"
#include "bn_sprite_items_cutlery.h"
#include "bn_sprite_items_person.h"
#include "bn_sprite_items_oops.h"

namespace dr
{
    LeftCutlery::LeftCutlery(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void LeftCutlery::show_directions()
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

    bool LeftCutlery::play_game(){
        int timer = 0;
        bool success = true;
        bool hit = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::yellow_cutlery_bg.create_bg(0, 0);
        map.set_camera(camera);

        //person
        bn::sprite_ptr person = bn::sprite_items::person.create_sprite(-100,0);
        person.set_rotation_angle(270);
        person.set_camera(camera);

        //oops
        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(50, -35);
        oops.set_rotation_angle(270);
        oops.set_visible(false);

        // cutlery
        bn::sprite_ptr cutlery[3] = {
            bn::sprite_items::cutlery.create_sprite(0,0,1),
            bn::sprite_items::cutlery.create_sprite(0,0,0),
            bn::sprite_items::cutlery.create_sprite(0,0,2),
        };
        cutlery[0].set_position(bn::fixed_point(200, 40));
        cutlery[1].set_position(bn::fixed_point(500, -40));
        cutlery[2].set_position(bn::fixed_point(700, 0));
        for(bn::sprite_ptr cut : cutlery){
            cut.set_rotation_angle(270);
            cut.set_camera(camera);
        }
        

        while (timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }
            
            if(!hit){
                if(bn::keypad::up_held() && person.y() > -60){ //left
                    person.set_y(person.y() -2);
                }

                if(bn::keypad::down_held() && person.y() < 60){ //down
                    person.set_y(person.y() +2);
                }

                for(bn::sprite_ptr cut : cutlery){
                    if(bn::abs(person.x() - cut.x()) < 20){
                        if(bn::abs(person.y() - cut.y()) < 20){
                            hit = true;
                            oops.set_visible(true);
                            success = false;
                        }
                    }
                    cut.set_x(cut.x() - 4);
                }
            }
            

            bn::core::update();
            ++timer;
        }

        return success;
    }

    bool LeftCutlery::execute(){
        show_directions();
        return play_game();
    }
    
}