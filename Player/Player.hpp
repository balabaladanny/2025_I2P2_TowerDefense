#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/color.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Engine/Sprite.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp" 

class Player : public Engine::Sprite {
protected:
    int speed;
    int hp, maxHp;
    int mp, maxMp;
    int exp = 0;
    int attack, defense;


    int level = 1;                   
    int expToLevelUp = 100*level;          
    int prevExpToLevelUp = 100*level;
    bool justLeveledUp = false;
    bool shouldClearLevelUpFlag = false; //延遲清除flag:畫EXP條用

    enum Direction { UP, DOWN, LEFT, RIGHT } direction;
    enum WeaponType { UNARMED, SWORD, HANDCANNON };
    WeaponType currentWeapon = UNARMED;

    std::vector<ALLEGRO_BITMAP*> standAnimations[3];
    std::vector<ALLEGRO_BITMAP*> walkAnimations[3];
    std::vector<ALLEGRO_BITMAP*> jumpAnimations[3];
    std::vector<ALLEGRO_BITMAP*> proneAnimations[3];
    std::vector<ALLEGRO_BITMAP*> attackAnimations[3];

    float animTimer = 0;
    int animFrame = 0;

    bool attacking = false;
    float attackTimer = 0;
    float attackDuration = 0.4f;
    bool attackKeyPressed = false;
    bool attackDashed = false;

    Engine::Point velocity;
    bool onGround = false;
    bool skipLandingThisFrame = false;
    bool proning = false;
    bool onRope = false;

    //test key debounce
    bool prevKeyZ = false;
    bool prevKeyC = false;
    bool prevKeyA = false;
    bool prevKeyS = false;
    bool prevKeyH = false;
    bool prevKeyM = false;
    bool prevKeyE = false;

    //invincible
    bool invincible = false;
    float invincibleTimer = 0.0f;
    const float invincibleDuration = 1.0f; // 一秒無敵

    // Skill 
    bool skillActive = false;
    bool skillUsedInAir = false;
    float skillScale = 1.0f;
    float skillCooldown = 0.0f;
    const float skillCooldownTime = 3.0f; // 3secs

    void LoadAnimation();

public:
    
    Player(int x, int y, int speed, int level, int hp, int mp, int atk, int def);
    ~Player();
    void Update(float deltaTime) override;
    void Draw() const override;
    void SetWeapon(WeaponType weapon); // switch weapon
    //EXP & level
    void GainExp(int amount); 
    void LevelUp();           

    //for UI
    int GetLevel() const;
    int GetExp() const;
    int GetExpToLevelUp() const;

    //for saving data
    int GetSpeed(){return speed;}
    int GetHP(){return hp;}
    int GetMP(){return mp;}
    int GetAtk(){return attack;}
    int GetDef(){return defense;}

    //pickups
    int coin = 0;          // coin amount
    int redPotion = 0;     // redPotion amount
    int bluePotion = 0;    // bluePotion amount

    
    void TakeDamage(int dmg); //-HP
    bool UseMP(int MPcost); //-MP
    void Heal(int amount); //+HP
    void RecoverMP(int amount); //+MP
    float CollisionRadius;

};

#endif  // PLAYER_HPP
