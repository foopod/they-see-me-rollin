#include "dr_scene_success.h"

#include "bn_core.h"
#include "bn_affine_bg_ptr.h"

#include "bn_affine_bg_items_success_bg.h"
#include "bn_affine_bg_items_success_no_rotate_bg.h"


namespace dr
{
    Success::Success(PlayerData& player_data, bn::sprite_text_generator& text_generator)
    : _player_data(&player_data), _text_generator(&text_generator){}

    void Success::execute(Rotation rotation){
        bn::affine_bg_ptr map = bn::affine_bg_items::success_bg.create_bg(0, 0);

        switch (rotation)
        {
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
                    map = bn::affine_bg_items::success_no_rotate_bg.create_bg(0, 0);
                }
                break;
            case dr::Rotation::Normal :
                break;
            default:
                break;
        }

        int timer = 0;

        while(timer < 60){
            ++timer;
            bn::core::update();
        }
    }

    
}