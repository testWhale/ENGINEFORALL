#pragma once
#include "cprocessing.h"


typedef struct {
    float posX, posY;
    float radius;        
    int   health;       
    int   maxHealth;     
} Entity;


void Hearts_Init(int max_hearts);          
void Hearts_Update(float dt);              
void Hearts_Draw(void);                   
void Hearts_TakeDamage(void);              
int  Hearts_Get(void);                     


void DrawHealthBarAbove(const Entity* e, float barWidth, float barHeight, float yOffset);


int DealTouchDamageIfColliding(Entity* player, Entity* enemy,
    int enemyDamagePerHit,
    float cooldownSeconds,
    float dt);

int CirclesOverlap(const Entity* a, const Entity* b);

ffff