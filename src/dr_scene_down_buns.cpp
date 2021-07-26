#include "dr_scene_down_buns.h"

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

#include "bn_regular_bg_items_down_buns_bg.h"
#include "bn_regular_bg_items_blue_buns_bg.h"
#include "bn_sprite_items_bowl.h"
#include "bn_sprite_items_buns.h"
#include "bn_sprite_items_oops.h"


namespace dr
{
    DownBuns::DownBuns(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void DownBuns::show_directions()
    {
        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::down_buns_bg.create_bg(0, 0);

        // text sprites
        bn::vector<bn::sprite_ptr, 12> text_sprites;

        int timer = 0;
        

        while(timer < 180){
            bn::core::update();
            ++timer;
        }

    }

    bool DownBuns::play_game(){
        int timer = 0;
        bool success = true;
        bool hit_edge = false;

        bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
        bn::random random = bn::random();

        // bg
        bn::regular_bg_ptr map = bn::regular_bg_items::blue_buns_bg.create_bg(0, 0);
        map.set_camera(camera);

        //bowl
        bn::sprite_ptr bowl_left = bn::sprite_items::bowl.create_sprite(16,-60);
        bowl_left.set_rotation_angle(180);
        bowl_left.set_camera(camera);
        bn::sprite_ptr bowl_right = bn::sprite_items::bowl.create_sprite(-16,-60);
        bowl_right.set_rotation_angle(180);
        bowl_right.set_horizontal_flip(true);
        bowl_right.set_camera(camera);

        //oops
        bn::sprite_ptr oops = bn::sprite_items::oops.create_sprite(0, 10);
        oops.set_rotation_angle(180);
        oops.set_visible(false);

        // buns
        bn::sprite_ptr buns[3] = {
            bn::sprite_items::buns.create_sprite(0,0,0),
            bn::sprite_items::buns.create_sprite(0,0,1),
            bn::sprite_items::buns.create_sprite(0,0,2),
        };
        buns[0].set_position(bn::fixed_point(90, 500));
        buns[1].set_position(bn::fixed_point(-40, 400));
        buns[2].set_position(bn::fixed_point(60, 800));
        for(bn::sprite_ptr bun : buns){
            bun.set_rotation_angle(180);
            bun.set_camera(camera);
        }

        while(timer < 5 * 60){

            if(random.get() % 100 < 3){
                camera.set_y(camera.y() - 2);
            } else {
                camera.set_y(0);
            }

            if(!hit_edge){
                if(bn::keypad::right_held() && bowl_left.x() < 90){ //right
                    bowl_left.set_x(bowl_left.x() +4);
                    bowl_right.set_x(bowl_right.x() +4);
                }

                if(bn::keypad::left_held() && bowl_right.x() > -90){ //left
                    bowl_left.set_x(bowl_left.x() -4);
                    bowl_right.set_x(bowl_right.x() -4);
                }

                int bowl_x = ((bowl_left.x() + bowl_right.x())/2).integer();
                int bowl_y = bowl_left.y().integer();

                for(bn::sprite_ptr bun : buns){
                    
                    if(bun.visible()){
                        if(bn::abs(bowl_x - bun.x()) < 32){
                            if(bn::abs(bowl_y - bun.y()) < 28){
                                bun.set_visible(false);
                            }
                        } else if(bun.y() < -60){
                            hit_edge = true;
                            success = false;
                            oops.set_visible(true);
                        }
                        bun.set_y(bun.y() - 3);
                    }
                }
            }
            

            bn::core::update();
            ++timer;
        }
        return success;
    }
    
    bool DownBuns::execute(){
        show_directions();
        return play_game();
    }

    
}