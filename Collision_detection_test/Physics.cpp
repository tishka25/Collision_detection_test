//
//  Physics.cpp
//  Collision_detection_test
//
//  Created by Teodor Stanishev on 2.05.18.
//  Copyright © 2018 Teodor Stanishev. All rights reserved.
//
#ifndef PHYSICS_CPP
#define PHYSICS_CPP
#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.cpp"
#include "ResourcePath.hpp"
#include <vector>
#include <math.h>

extern int WIDTH;
extern int HEIGHT;


auto doCirclesOverlap=[](Vector2f pos1,float r1,Vector2f pos2,float r2){
    return (fabs((pos1.x-pos2.x)*(pos1.x-pos2.x) + (pos1.y-pos2.y)*(pos1.y-pos2.y))<=(r1*r2)*4);
};

auto isPointInCircle=[](Vector2f pos1,float r1,Vector2f pointer){
    return fabs((pos1.x-pointer.x) * (pos1.x-pointer.x) + (pos1.y-pointer.y) * (pos1.y-pointer.y)) < (r1*r1);
};



class Physics{
private:
    vector<Ball *>balls;
    vector<pair<Ball*,Ball*>>vecCollidingPairs;
    
    void updatePosition(){
        //Update ball position
        
        for(auto &ball : balls){
            //Add drag
            ball->drag.x=-ball->velocity.x*0.08f;
            ball->drag.y=-ball->velocity.y*0.08f;
            
            ball->velocity.x+=ball->drag.x;
            ball->velocity.y+=ball->drag.y;
            ball->position.x+=ball->velocity.x/15;
            ball->position.y+=ball->velocity.y/15;
            
            
            //If a ball goes out of screen , respawn it
                if(ball->position.x<0)
                    ball->position.x+=(float)WIDTH;
                else if (ball->position.x>=WIDTH)
                    ball->position.x-=WIDTH;
                else if(ball->position.y<0)
                    ball->position.y+=HEIGHT;
                else if(ball->position.y>=HEIGHT)
                    ball->position.y-=HEIGHT;
        }
    }
    
    
    void staticCollisions(){
        //Static collisions
        for(auto &ball : balls){
            for(auto &target : balls){
                if(ball->id!=target->id){
                    if(doCirclesOverlap(target->position,target->getRaduis(),ball->position,ball->getRaduis())){
                        //Collision has accured
                        vecCollidingPairs.push_back({ball,target});
                        float fDistance=sqrtf((ball->position.x-target->position.x) * (ball->position.x-target->position.x) + (ball->position.y-target->position.y) * (ball->position.y-target->position.y));
                        
                        float fOverlap=0.5f * (fDistance-ball->raduis-target->raduis);
                        
                        ball->position.x-=fOverlap*(ball->position.x-target->position.x)/fDistance;
                        ball->position.y-=fOverlap*(ball->position.y-target->position.y)/fDistance;

                        target->position.x-=fOverlap*(target->position.x-ball->position.x)/fDistance;
                        target->position.y-=fOverlap*(target->position.y-ball->position.y)/fDistance;
                        
//                        if(fOverlap<=0.5f){
//                            ball->color+=target->color;
//                        }
                        
                    }
                }
            }
        }
    }

    void draw(){
        for(auto ball : balls){
            ball->update();
        }
    }
    
    
public:
    Physics();
    Physics(vector<Ball *>balls){
        this->balls=balls;
    }
    
    void addBall(Ball *ball){
        balls.push_back(ball);
    }
//    void addBall(vector<Ball *>balls){
//        this->balls=balls;
//    }
//    
    vector<Ball *> getBalls(){
        return balls;
    }
    
    Ball* getBallFromIndex(int i){
        for(int j =0;j<balls.size();j++){
            if(j==i){
                return balls[j];
            }
        }
        return 0;
    }
    void handle(){
        updatePosition();
        staticCollisions();
        draw();
    }
    

    
};




#endif
