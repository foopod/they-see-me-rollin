#include "dr_scene_down_dog.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_random.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_down_dog_bg.h"
#include "bn_regular_bg_items_blue_dog_bg.h"
#include "bn_sprite_items_nice.h"
#include "bn_sprite_items_hand_down.h"
#include "bn_sprite_items_dog.h"


namespace dr
{
    DownDog::DownDog(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void DownDog::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::down_dog_bg.create_bg(0, 0);

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        int timer = 0;
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool DownDog::play_game(){
        int timer = 0;
        bool success = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::blue_dog_bg.create_bg(0, 0);
        map.set_camera(camera);

        // hand
        bn::sprite_ptr hand = bn::sprite_items::hand_down.create_sprite(0,0);
        hand.set_rotation_angle(180);
        hand.set_scale(0.8);
        hand.set_bg_priority(0);
        hand.set_camera(camera);

        // dog
        bn::sprite_ptr dog = bn::sprite_items::dog.create_sprite(80,60);
        dog.set_rotation_angle(180);
        dog.set_bg_priority(3);
        dog.set_camera(camera);

        // nice
        bn::sprite_ptr nice = bn::sprite_items::nice.create_sprite(0, +8);
        nice.set_rotation_angle(180);
        nice.set_visible(false);

        bn::fixed_point targets[4] = {
            bn::fixed_point(80,60),
            bn::fixed_point(-80,60),
            bn::fixed_point(-80,-60),
            bn::fixed_point(80,-60),
        };

        int current_target = 0;
        

        while(timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_y(camera.y() - 2);
            } else {
                camera.set_y(0);
            }

            if(!success){
                dog.set_x(dog.x() + (targets[current_target].x() - dog.x())/20);
                dog.set_y(dog.y() + (targets[current_target].y() - dog.y())/20);

                if(bn::abs(dog.x() - targets[current_target].x()) < 4){
                    if(bn::abs(dog.y() - targets[current_target].y()) < 4){
                        current_target = (current_target + 1) % 4;
                    }
                }


                if(bn::keypad::up_held()){
                    hand.set_y(hand.y() - 2);
                }
                if(bn::keypad::right_held()){
                    hand.set_x(hand.x() + 2);
                }
                if(bn::keypad::down_held()){
                    hand.set_y(hand.y() + 2);
                }
                if(bn::keypad::left_held()){
                    hand.set_x(hand.x() - 2);
                }

                if(bn::abs(dog.x() - hand.x()) < 20){
                    if(bn::abs(dog.y() - hand.y()) < 20){
                        success = true;
                        nice.set_visible(true);
                    }
                }
            }
            

            bn::core::update();
            ++timer;
        }
        return success;
    }
    
    bool DownDog::execute(){
        show_directions();
        return play_game();
    }

    
}