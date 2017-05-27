//
//  enemy.hpp
//  Moosh
//
//  Created by Lilly Fiorino on 5/26/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
#include "map.hpp"

class enemy {
private:
    int location[2];
    int mapLocation[2];
    int AIstate;
    int timeInterval;
public:
    int getLocation(int i);
    void setLocation(int i, int j);
    int getMapLocation(int i);
    void setMapLocation(int i, int j);
    int getAIstate();
    void setAIstate(int i);
    void setTimeInterval(int i);
    int getTimeInterval();
    void moveForward(map &map);
    void moveBackward(map &map);
    void moveLeft(map &map);
    void moveRight(map &map);
    int attackForward();
    int attackBackward();
    int attackLeft();
    int attackRight();
    
};

class boss: public enemy{
    
};

#endif /* enemy_hpp */
