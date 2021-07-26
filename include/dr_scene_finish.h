#ifndef DR_SCENE_FINISH_H
#define DR_SCENE_FINISH_H

#include "bn_sprite_text_generator.h"

#include "dr_rotation.h"
#include "dr_player_data.h"


namespace dr
{
    class Finish
    {       
        private:
            PlayerData* _player_data;
            bn::sprite_text_generator* _text_generator;
        public:
            Finish(PlayerData& player_data, bn::sprite_text_generator& text_generator);
            void execute(int successes);
    };
}

#endif