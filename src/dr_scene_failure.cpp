#include "dr_scene_failure.h"

#include "bn_core.h"
#include "bn_affine_bg_ptr.h"

#include "bn_affine_bg_items_failure_bg.h"
#include "bn_affine_bg_items_failure_no_rotate_bg.h"


namespace dr
{
    Failure::Failure(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void Failure::execute(Rotation rotation){
        bn::affine_bg_ptr map = bn::affine_bg_items::failure_bg.create_bg(0, 0);

        int timer = 0;
        switch(rotation){
            case dr::Rotation::Right :
                {
                    map.set_rotation_angle(90);
                }
                break;
            case dr::Rotation::Left :
                {
                    map.set_rotation_angle(270);
                }
                break;
            case dr::Rotation::UpsideDown :
                {
                    map.set_rotation_angle(180);
                }
                break;
            case dr::Rotation::NONE :
                {
                    map = bn::affine_bg_items::failure_no_rotate_bg.create_bg(0, 0);
                }
                break;
            case dr::Rotation::Normal :
                break;
            default:
                break;
        }

        while(timer < 60){
            ++timer;
            bn::core::update();
        }
    }

    
}