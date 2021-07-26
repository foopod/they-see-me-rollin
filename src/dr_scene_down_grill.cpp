#include "dr_scene_down_grill.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_fixed.h"
#include "bn_random.h"
#include "bn_camera_ptr.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_down_grill_bg.h"
#include "bn_regular_bg_items_orange_grill_bg.h"
// #include "bn_regular_bg_items_blue_buns_bg.h"
#include "bn_sprite_items_grill.h"
#include "bn_sprite_items_person.h"
#include "bn_sprite_items_oops.h"


namespace dr
{
    DownGrill::DownGrill(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void DownGrill::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::down_grill_bg.create_bg(0, 0);

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        int timer = 0;
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool DownGrill::play_game(){
        int timer = 0;
        bool success = true;
        bool is_hit = false;
        bn::fixed dy = 0;
        bn::fixed gravity = -2;
        bn::fixed friction = 0.95;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::orange_grill_bg.create_bg(0, 0);
        map.set_camera(camera);

        //oops
        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(30, 10);
        oops.set_rotation_angle(180);
        oops.set_visible(false);

        // grill
        bn::sprite_ptr grill = bn::sprite_items::grill.create_sprite(-280,-60);
        grill.set_rotation_angle(180);
        grill.set_camera(camera);

        // person
        bn::sprite_ptr person = bn::sprite_items::person.create_sprite(40,-60);
        person.set_rotation_angle(180);
        person.set_camera(camera);

        while(timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_y(camera.y() - 2);
            } else {
                camera.set_y(0);
            }

            if(!is_hit){
                grill.set_x(grill.x() + 3);

                if(person.y() <= -60){
                    person.set_y(-60);
                    if(bn::keypad::b_pressed() || bn::keypad::a_pressed()){
                        dy += 12;
                    }
                }

                person.set_y(person.y() + gravity);
                person.set_y(person.y() + dy);
                dy = dy * friction;

                if(bn::abs(person.x() - grill.x()) < 32){
                    if(bn::abs(person.y() - grill.y()) < 32){
                        is_hit = true;
                        success = false;
                        oops.set_visible(true);
                    }
                }
            }

            

            bn::core::update();
            ++timer;
        }
        return success;
    }
    
    bool DownGrill::execute(){
        show_directions();
        return play_game();
    }

    
}