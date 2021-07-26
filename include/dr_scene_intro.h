#ifndef DR_SCENE_INTRO_H
#define DR_SCENE_INTRO_H

#include "bn_sprite_text_generator.h"

#include "dr_scene_type.h"
#include "dr_player_data.h"


namespace dr
{
    class Intro
    {       
        private:
            PlayerData* _player_data;
            bn::sprite_text_generator* _text_generator;
        public:
            Intro(PlayerData& player_data, bn::sprite_text_generator& text_generator);
            void execute();
    };
}

#endif