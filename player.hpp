//
//  player.hpp
//  Moosh
//
//  Created by Lilly Fiorino on 5/25/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "map.hpp"

class player {
private:
    int location[2];
    int inventory[24];
    int inventorySize;
    int invertControls;
public:
    void setLocation(int i, int coord);
    int getLocation(int i);
    void moveForward(map &map);
    void moveBackward(map &map);
    void moveLeft(map &map);
    void moveRight(map &map);
    int gridValueUnderneath(map &map);
    void setInventory(int i, int j);
    int getInventory(int i);
    void setInventorySize(int i);
    int getInventorySize();
    void setInvertControls(int i);
    int getInvertControls();
    bool addKey();
    bool removeKey();
    bool pickUpKey(map &map);
    bool useKey(map &map);
    int checkAroundFor(map &map, int i);
    
    
};

#endif /* player_hpp */
