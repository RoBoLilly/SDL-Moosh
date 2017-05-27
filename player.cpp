//
//  player.cpp
//  Moosh
//
//  Created by Lilly Fiorino on 5/25/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#include "player.hpp"
#include "map.hpp"

void player::setLocation(int i, int coord){
    location[i] = coord;
}
int player::getLocation(int i){
    return location[i];
}
void player::setInventory(int i, int j){
    inventory[i] = j;
}
int player::getInventory(int i){
    return inventory[i];
}
void player::setInventorySize(int i){
    inventorySize = i;
}
int player::getInventorySize(){
    return inventorySize;
}
void player::setInvertControls(int i){
    invertControls = i;
}
int player::getInvertControls(){
    return invertControls;
}
void player::moveForward(map &map){
    if(!getInvertControls()){
        if (map.isPermeable(getLocation(0) - 1, getLocation(1))){
            setLocation(0, getLocation(0) - 1); // Move Forward
        }
    }else{
        if (map.isPermeable(getLocation(0) + 1, getLocation(1))){
            setLocation(0, getLocation(0) + 1); // Move Backward
        }
    }
}
void player::moveBackward(map &map){
    if(!getInvertControls()){
        if (map.isPermeable(getLocation(0) + 1, getLocation(1))){
            setLocation(0, getLocation(0) + 1); // Move Backward
        }
    }else{
        if (map.isPermeable(getLocation(0) - 1, getLocation(1))){
            setLocation(0, getLocation(0) - 1); // Move Forward
        }
    }
}
void player::moveLeft(map &map){
    if(!getInvertControls()){
        if (map.isPermeable(getLocation(0), getLocation(1) - 1)){
            setLocation(1, getLocation(1) - 1);
        }
    }else{
        if (map.isPermeable(getLocation(0), getLocation(1) + 1)){
            setLocation(1, getLocation(1) + 1);
        }
    }
}
void player::moveRight(map &map){
    if(!getInvertControls()){
        if (map.isPermeable(getLocation(0), getLocation(1) + 1)){
            setLocation(1, getLocation(1) + 1);
        }
    }else{
        if (map.isPermeable(getLocation(0), getLocation(1) - 1)){
            setLocation(1, getLocation(1) - 1);
        }
    }
}
int player::gridValueUnderneath(map &map)
{
    return map.gridValue(getLocation(0), getLocation(1));
}
bool player::addKey()
{
    bool success = true;
    if(getInventorySize() < 25)
    {
        setInventory(getInventorySize(), 1);
        setInventorySize(getInventorySize()+1);
    }else{
        success = false;
    }
    return success;
}
bool player::removeKey()
{
    bool success = true;
    if(getInventorySize() > 0){
        setInventory(getInventorySize()-1, 0);
        setInventorySize(getInventorySize()-1);
    }else{
        success = false;
    }
    return success;
}
bool player::pickUpKey(map &map)
{
    bool success = false;
    if (map.gridValue(getLocation(0), getLocation(1)) == 2) // Pickup Key and add to inventory
    {
        map.setGridValue(getLocation(0), getLocation(1), 1);
        addKey();
        success = true;
    }
    return success;
}
bool player::useKey(map &map)
{
    bool success = false;
    if(getInventory(0)==1 && checkAroundFor(map, 3) != 0){ // Unlock door and remove key from inventory
        switch (checkAroundFor(map, 3)) {
            case 2:
                map.setGridValue(getLocation(0) + 1, getLocation(1), 4);
                break;
            case 3:
                map.setGridValue(getLocation(0) - 1, getLocation(1), 4);
                break;
            case 4:
                map.setGridValue(getLocation(0), getLocation(1) + 1, 4);
                break;
            case 5:
                map.setGridValue(getLocation(0), getLocation(1) - 1, 4);
                break;
        }
        removeKey();
        success = true;
    }
    if(getInventory(0)==1 && // Unlock Big Door and remove 3 keys from inventory
       getInventory(1)==1 &&
       getInventory(2)==1 && checkAroundFor(map, 7) != 0){
        switch (checkAroundFor(map, 7)) {
            case 2:
                map.setGridValue(getLocation(0) + 1, getLocation(1), 4);
                break;
            case 3:
                map.setGridValue(getLocation(0) - 1, getLocation(1), 4);
                break;
            case 4:
                map.setGridValue(getLocation(0), getLocation(1) + 1, 4);
                break;
            case 5:
                map.setGridValue(getLocation(0), getLocation(1) - 1, 4);
                break;
        }
        removeKey();
        removeKey();
        removeKey();
        success = true;
    }
    return success;
}

int player::checkAroundFor(map &map, int i)
{
    if(map.gridValue(getLocation(0), getLocation(1)) == i){return 1;}
    else if (map.gridValue(getLocation(0) + 1, getLocation(1)) == i){return 2;}
    else if (map.gridValue(getLocation(0) - 1, getLocation(1)) == i){return 3;}
    else if (map.gridValue(getLocation(0), getLocation(1) + 1) == i){return 4;}
    else if (map.gridValue(getLocation(0), getLocation(1) - 1) == i){return 5;}
    else{
        return 0;
    }
}


