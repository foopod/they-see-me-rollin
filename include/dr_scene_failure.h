#ifndef DR_SCENE_FAILURE_H
#define DR_SCENE_FAILURE_H

#include "bn_sprite_text_generator.h"

#include "dr_rotation.h"
#include "dr_player_data.h"


namespace dr
{
    class Failure
    {       
        private:
            PlayerData* _player_data;
            bn::sprite_text_generator* _text_generator;
        public:
            Failure(PlayerData& player_data, bn::sprite_text_generator& text_generator);
            void execute(Rotation rotation);
    };
}

#endif