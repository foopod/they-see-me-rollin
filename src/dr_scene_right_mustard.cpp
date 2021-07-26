#include "dr_scene_right_mustard.h"

#include "bn_core.h"
#include "bn_camera_ptr.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_right_mustard_bg.h"
#include "bn_regular_bg_items_red_mustard_bg.h"
#include "bn_sprite_items_mustard_bottle2.h"
#include "bn_sprite_items_hand.h"
#include "bn_sprite_items_oops.h"
#include "bn_sprite_items_nice.h"


namespace dr
{
    RightMustard::RightMustard(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void RightMustard::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::right_mustard_bg.create_bg(0, 0);
        


        int timer = 0;
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool RightMustard::play_game(){
        int timer = 0;
        bool success = false;
        bool falling = true;
        bool hand_closed = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::red_mustard_bg.create_bg(0, 0);
        map.set_camera(camera);

        // mustard
        bn::sprite_ptr mustard_bottle = bn::sprite_items::mustard_bottle2.create_sprite(0,10);
        mustard_bottle.set_rotation_angle(90);
        mustard_bottle.set_x(-200);
        mustard_bottle.set_bg_priority(2);
        mustard_bottle.set_camera(camera);

        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(-0,35);
        oops.set_rotation_angle(90);
        oops.set_visible(false);

        bn::sprite_ptr nice = bn::sprite_items::nice.create_sprite(-10,35);
        nice.set_rotation_angle(90);
        nice.set_visible(false);

        // hand
        bn::sprite_ptr hand = bn::sprite_items::hand.create_sprite(60,0);
        hand.set_rotation_angle(90);
        hand.set_camera(camera);
        bn::sprite_ptr hand_front = bn::sprite_items::hand.create_sprite(60,0,2);
        hand_front.set_rotation_angle(90);
        hand_front.set_visible(false);
        hand_front.set_bg_priority(0);
        hand_front.set_camera(camera);
        bn::sprite_ptr wrist = bn::sprite_items::hand.create_sprite(60,-64,4);
        wrist.set_rotation_angle(90);
        wrist.set_camera(camera);

        while (timer < 5 * 60){


            if(random.get() % 100 < 3){
                camera.set_x(camera.x() - 2);
            } else {
                camera.set_x(0);
            }

            if(timer > 120 && falling){
                mustard_bottle.set_x(mustard_bottle.x() + 4);
                //trigger drop

                if(!hand_closed && (bn::keypad::a_pressed() || bn::keypad::b_pressed())){
                    hand_closed = true;
                    hand.set_tiles(bn::sprite_items::hand.tiles_item().create_tiles(1));
                    if(mustard_bottle.x() > 30 && mustard_bottle.x() < 100){
                        success = true;
                        falling = false;
                        hand_front.set_visible(true);
                        mustard_bottle.set_x(mustard_bottle.x() - 8);
                        nice.set_visible(true);
                    } else {
                       hand.set_bg_priority(3); 
                       oops.set_visible(true);
                    }
                }
            }

            bn::core::update();
            ++timer;
        }
        return success;
    }

    bool RightMustard::execute(){
        show_directions();
        return play_game();
    }

    
}