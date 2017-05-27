//
//  map.hpp
//  Moosh
//
//  Created by Lilly Fiorino on 5/25/17.
//  Copyright © 2017 SDL_Moosh. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#include <stdio.h>
#include <vector>

class map {
private:
    int grid[12][12];
    int loadedMap[2];
    std::vector<bool> permeableList;
public:
    map();
    struct Map3D;
    int gridValue(int i, int j);
    void setGridValueNoSave(int i, int j, int k);
    void setGridValue(int i, int j, int k);
    void setLoadedGrid(int i, int j);
    int getLoadedGrid(int i);
    void loadGrid(int loadGrid[][12]);
    void loadForwardGrid();
    void loadBackwardGrid();
    void loadLeftGrid();
    void loadRightGrid();
    int isPermeable(int i, int j);
};

#endif /* map_hpp */
