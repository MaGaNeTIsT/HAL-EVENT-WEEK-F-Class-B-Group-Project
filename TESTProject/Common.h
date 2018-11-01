#ifndef _COMMON_H
#define _COMMON_H

#define SAFE_RELEASE(x) {if(x) { (x)->Release(); (x) = NULL;}}
#define PTR_RELEASE(x) {if((x) != NULL) { delete[](x); (x) = NULL;}}

#define CLASS_NAME        "GAMEWindow"
#define WINDOW_CAPTION    "GAMEWindow"

#define WINDOW_WIDTH                    (1600)
#define WINDOW_HEIGHT                   (900)

#define FVF_VERTEX2D                    (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_FADEINOUT                   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#define MY_SOUND_MAIN_FLAGS             (DSBCAPS_PRIMARYBUFFER)
#define MY_SOUND_FLAGS                  (DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY)
#define SOUND_BUFFER_COUNT              (11)
#define SOUND_FILE_COUNT                (10)

#define MAP_SCENE_COUNT                 (1)

#define TEXTURE_COUNT                   (20)
#define TEXTURE_FPS_COUNT               (10)

#define TEXTFONT_COUNT                  (5)

#define FADE_ALPHA_SPEED                (10.0)
#define FADE_INDEX                      (99999)

#define SCORE_COUNT                     (30)
#define SCORE_FONT_WIDTH                (64)
#define SCORE_FONT_HEIGHT               (64)

#define PI                              (3.1415926f)
#define BALL_ANGLE                      (0.0f)
#define BALL_ROLL_SEED                  (10)
#define BALL_ROLL_SPEED                 (0.3f)
#define BALL_SPEEDX                     (0.0f)
#define BALL_SPEEDY                     (0.0f)
#define EFFECT_DISTANCE                 (8.0f)
#define CIRECLEBULLET_POS_X             (800)
#define CIRECLEBULLET_POS_Y             (300)

#define PLAYER_TEXTURE_INDEX            (1)
#define PLAYER_TEXTURE_U                (4)
#define PLAYER_TEXTURE_V                (1)
#define PLAYER_MOVEX                    (9.0f)
#define PLAYER_MOVEY                    (6.0f)
#define PLAYER_RUNSPEED                 (0.5f)
#define PLAYER_BULLETPOOL_COUNT         (20)
#define PLAYER_PROPERTY_HP              (50.0f)
#define PLAYER_PROPERTY_ATK             (2.0f)
#define PLAYER_HURT_RANGEX              (2.0f)
#define PLAYER_HURT_RANGEY              (2.0f)

#define BOSS_TEXTURE_INDEX              (5)
#define BOSS_TEXTURE_U                  (5)
#define BOSS_TEXTURE_V                  (2)
#define BOSS_MOVEX                      (13.0f)
#define BOSS_MOVEY                      (0.0f)
#define BOSS_PROPERTY_HP                (50.0f)
#define BOSS_PROPERTY_ATK               (1.0f)

#define BULLET_MOVEX                    (20.0f)
#define BULLET_MOVEY                    (13.0f)
#define BULLET_WIDTH                    (48)
#define BULLET_HEIGHT                   (32)
#define BULLET_DAMAGE                   (1.0f)
#define BULLET_COUNT_CIRCLE             (24)
#define BULLET_CIRCLE_POOL              (30)
#define BULLET_CIRCLE_SPEED             (6.0f)
#define BULLET_TEXTURE_U                (8)
#define BULLET_TEXTURE_V                (2)

#define STRAIGHT_BULLET_COUNT           (8)
#define STRAIGHT_BULLET_MEMBER_COUNT    (6)
#define STRAIGHT_BULLET_MEMBER_SPEED    (4.7)

#endif // !_COMMON_H