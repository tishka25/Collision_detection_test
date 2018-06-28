//
//  Ball.hpp
//  Collision_detection_test
//
//  Created by Teodor Stanishev on 18.04.18.
//  Copyright © 2018 Teodor Stanishev. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace std;
using namespace sf;

//extern int id;


extern sf::RenderWindow window;

class Ball:public CircleShape{
public:
    Vector2f position;
    Vector2f velocity;
    Vector2f drag;
    float raduis;
    float mass=raduis*10.0f;
    int id;
    Color color;
    CircleShape modelCircle;
    Ball();
    Ball(Vector2f position,float raduis, int id,Color color){
        this->position=position;
        this->raduis=raduis;
        this->id=id;
        this->color=color;
        modelCircle.setRadius(raduis);
        modelCircle.setPosition(position);
        modelCircle.setOrigin(raduis, raduis);
        modelCircle.setFillColor(color);
    }
    
    void update(){
        modelCircle.setPosition(position);
        window.draw(modelCircle);
        position=getPosition();
    }
    void setRadius(float rad){
        modelCircle.setRadius(rad);
    }
    float getRaduis(){
        return modelCircle.getRadius();
    }
    Vector2f getPosition(){
        return modelCircle.getPosition();
    }
    void setPosition(Vector2f position){
        modelCircle.setPosition(position);
    }
    
};

#endif /* Ball_hpp */
