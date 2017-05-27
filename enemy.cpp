//
//  enemy.cpp
//  Moosh
//
//  Created by Lilly Fiorino on 5/26/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#include "enemy.hpp"
#include "map.hpp"

void enemy::setLocation(int i, int j){
    location[i] = j;
}
int enemy::getLocation(int i){
    return location[i];
}
int enemy::getMapLocation(int i){
    return mapLocation[i];
}
void enemy::setMapLocation(int i, int j){
    mapLocation[i] = j;
}
void enemy::moveForward(map &map){
    if (map.isPermeable(getLocation(0) - 1, getLocation(1))){
        setLocation(0, getLocation(0) - 1); // Move Forward
    }

}
void enemy::moveBackward(map &map){
    if (map.isPermeable(getLocation(0) + 1, getLocation(1))){
        setLocation(0, getLocation(0) + 1); // Move Backward
    }
}
void enemy::moveLeft(map &map){
    if (map.isPermeable(getLocation(0), getLocation(1) - 1)){
        setLocation(1, getLocation(1) - 1); // Move Left
    }
}
void enemy::moveRight(map &map){
    if (map.isPermeable(getLocation(0), getLocation(1) + 1)){
        setLocation(1, getLocation(1) + 1); // Move Right
    }

}
// AI
void enemy::setTimeInterval(int i)
{
    timeInterval = i;
}
int enemy::getTimeInterval()
{
    return timeInterval;
}
int enemy::getAIstate(){
    return AIstate;
}
void enemy::setAIstate(int i){
    AIstate = i;
}
int enemy::attackForward(){
    return 0;
}
int enemy::attackBackward(){
    return 0;
}
int enemy::attackLeft(){
    return 0;
}
int enemy::attackRight(){
    return 0;
}
