#ifndef DR_SCENE_RIGHT_FRIDGE_H
#define DR_SCENE_RIGHT_FRIDGE_H

#include "bn_sprite_text_generator.h"

#include "dr_scene_type.h"
#include "dr_player_data.h"


namespace dr
{
    class RightFridge
    {       
        private:
            PlayerData* _player_data;
            bn::sprite_text_generator* _text_generator;
        public:
            RightFridge(PlayerData& player_data, bn::sprite_text_generator& text_generator);
            void show_directions();
            bool play_game();
            bool execute();
    };
}

#endif