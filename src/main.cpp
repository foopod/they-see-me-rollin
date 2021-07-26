#include "bn_core.h"
#include "bn_random.h"

#include "dr_scene_type.h"
#include "dr_rotation.h"
#include "dr_scene_intro.h"
#include "dr_scene_up_button.h"
#include "dr_scene_up_plug.h"
#include "dr_scene_down_buns.h"
#include "dr_scene_down_grill.h"
#include "dr_scene_down_dog.h"
#include "dr_scene_left_cutlery.h"
#include "dr_scene_left_fryer.h"
#include "dr_scene_left_rocks.h"
#include "dr_scene_right_mustard.h"
#include "dr_scene_right_fridge.h"
#include "dr_scene_right_dump.h"

#include "dr_scene_finish.h"

#include "dr_scene_success.h"
#include "dr_scene_failure.h"

#include "dr_player_data.h"

#include "dr_font.h"


int main()
{
    bn::core::init();

    bn::random random = bn::random();

    dr::Rotation outcome_rot = dr::Rotation::Right;

    //player data
    dr::PlayerData player_data = dr::PlayerData();

    //text generator
    bn::sprite_text_generator text_generator(dr::fixed_8x8_sprite_font);

    // scenes
    // bn::sprite_ptr scenes[5] = {
    //     dr::RightMustard(player_data, text_generator),
    //     dr::DownBuns(player_data, text_generator),
    //     dr::LeftCutlery(player_data, text_generator),
    //     dr::UpButton(player_data, text_generator),
    //     dr::RightFridge(player_data, text_generator),
    // };

    int successes = 0;

    //first scene
    dr::SceneType scene = dr::SceneType::INTRO;
    while(true)
    {
        bool outcome = false;
        switch (scene)
        {
            case dr::SceneType::UP_BUTTON :
                {
                    dr::UpButton upButton = dr::UpButton(player_data, text_generator);
                    outcome = upButton.execute();
                    outcome_rot = dr::Rotation::Normal;
                    scene = dr::SceneType::RIGHT_MUSTARD;
                    break;
                }
            case dr::SceneType::LEFT_CUTLERY :
                {
                    dr::LeftCutlery left_cutlery = dr::LeftCutlery(player_data, text_generator);
                    outcome = left_cutlery.execute();
                    outcome_rot = dr::Rotation::Left;
                    scene = dr::SceneType::UP_PLUG;
                    break;
                }
            case dr::SceneType::RIGHT_MUSTARD :
                {
                    dr::RightMustard right_mustard = dr::RightMustard(player_data, text_generator);
                    outcome = right_mustard.execute();
                    outcome_rot = dr::Rotation::Right;
                    scene = dr::SceneType::DOWN_GRILL;
                    break;
                }
            case dr::SceneType::DOWN_BUNS :
                {
                    dr::DownBuns down_buns = dr::DownBuns(player_data, text_generator);
                    outcome = down_buns.execute();
                    outcome_rot = dr::Rotation::UpsideDown;
                    scene = dr::SceneType::LEFT_FRYER;
                    break;
                }
            case dr::SceneType::RIGHT_FRIDGE :
                {
                    dr::RightFridge right_fridge = dr::RightFridge(player_data, text_generator);
                    outcome = right_fridge.execute();
                    outcome_rot = dr::Rotation::Right;
                    scene = dr::SceneType::DOWN_BUNS;
                    break;
                }
            case dr::SceneType::DOWN_GRILL :
                {
                    dr::DownGrill down_grill = dr::DownGrill(player_data, text_generator);
                    outcome = down_grill.execute();
                    outcome_rot = dr::Rotation::UpsideDown;
                    scene = dr::SceneType::LEFT_CUTLERY;
                    break;
                }
            case dr::SceneType::LEFT_FRYER :
                {
                    dr::LeftFryer left_fryer = dr::LeftFryer(player_data, text_generator);
                    outcome = left_fryer.execute();
                    outcome_rot = dr::Rotation::Left;
                    scene = dr::SceneType::UP_BUTTON;
                    break;
                }
            case dr::SceneType::UP_PLUG :
                {
                    dr::UpPlug up_plug = dr::UpPlug(player_data, text_generator);
                    outcome = up_plug.execute();
                    outcome_rot = dr::Rotation::Normal;
                    scene = dr::SceneType::RIGHT_DUMP;
                    break;
                }
            case dr::SceneType::RIGHT_DUMP :
                {
                    dr::RightDump right_dump = dr::RightDump(player_data, text_generator);
                    outcome = right_dump.execute();
                    outcome_rot = dr::Rotation::Right;
                    scene = dr::SceneType::DOWN_DOG;
                    break;
                }
            case dr::SceneType::DOWN_DOG :
                {
                    dr::DownDog down_dog = dr::DownDog(player_data, text_generator);
                    outcome = down_dog.execute();
                    outcome_rot = dr::Rotation::UpsideDown;
                    scene = dr::SceneType::LEFT_ROCKS;
                    break;
                }
            case dr::SceneType::LEFT_ROCKS :
                {
                    dr::LeftRocks left_rocks = dr::LeftRocks(player_data, text_generator);
                    outcome = left_rocks.execute();
                    outcome_rot = dr::Rotation::Left;
                    scene = dr::SceneType::FINISH;
                    break;
                }
            case dr::SceneType::FINISH :
                {
                    dr::Finish finish = dr::Finish(player_data, text_generator);
                    finish.execute(successes);
                    // finish.execute(5);
                    outcome_rot = dr::Rotation::Normal;
                    scene = dr::SceneType::INTRO;
                    break;
                }
            case dr::SceneType::INTRO :
                {
                    successes = 0;
                    dr::Intro intro = dr::Intro(player_data, text_generator);
                    intro.execute();
                    outcome_rot = dr::Rotation::Normal;
                    scene = dr::SceneType::RIGHT_FRIDGE;
                    break;
                }
            default:
                break;
        }

        if(scene != dr::SceneType::RIGHT_FRIDGE && scene != dr::SceneType::INTRO){
            if(outcome){ //success
                dr::Success success = dr::Success(player_data, text_generator);
                success.execute(outcome_rot);
                ++successes;
            } else { //fail
                dr::Failure failure = dr::Failure(player_data, text_generator);
                failure.execute(outcome_rot);
            }
        }
        

        // if(random.get() % 100 < 25){
        //     scene = dr::SceneType::UP;
        // } else if(random.get() % 100 < 50) {
        //     scene = dr::SceneType::DOWN;
        // } else if(random.get() % 100 < 75) {
        //     scene = dr::SceneType::LEFT;
        // } else  {
        //     scene = dr::SceneType::RIGHT;
        // }
        
        bn::core::update();
    }
}
