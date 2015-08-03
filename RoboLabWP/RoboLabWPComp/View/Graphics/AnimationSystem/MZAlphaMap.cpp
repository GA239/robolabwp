#include "pch.h"
#include "MZAlphaMap.h"
#include <math.h>

MZAlphaMap::MZAlphaMap(void)
{
    MZGame *game = MZGame::getInstance();
	_width = game->_maze->width();
    _height = game->_maze->height(); 
    _map = (float ***)malloc(sizeof(float **) * _width);
    for(int i = 0; i < _width; i++)
    {
        _map[i] = (float **)malloc(sizeof(float *) * _height);
        for(int j = 0; j < _height; j++)
        {
            _map[i][j] = (float *)malloc(sizeof(float) * 4);
            for(int k = 0; k < 4; k++)
            {
                _map[i][j][k] = 0.0;
            }
        }
    }
	game->FreeInst();
}


MZAlphaMap::~MZAlphaMap(void)
{
	for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
			free(_map[i][j]);
        }
		free(_map[i]);
    }
	free(_map);
}

bool wallCheckXYD(int x, int y, MZDirection dir)
{
	MZPosition *pos = new MZPosition(x,y);
	MZGame* game = MZGame::getInstance();
	MZCellMatrix *cellMatrix = game->_maze->cells();
	bool result = cellMatrix->cellAtPosition(pos)->hasWallAtDirection(dir);
	delete(pos);
	game->FreeInst();
    return result;
}

void MZAlphaMap::setReal()
{
	MZGame* game = MZGame::getInstance();
    MZVisitsMatrix *visitsMatrix = game->_visitsMatrix;
    for(int x = 0; x < _width; x++)
    {
        for(int y = 0; y < _height; y++)
        {
            double topLeft = -1.0, bottomLeft = -1.0, topRight = -1.0, bottomRight = -1.0, top = -1.0, left = -1.0, right = -1.0, bottom = -1.0, center = -1.0;
            
            double topLeftCorner, topRightCorner,bottomLeftCorner, bottomRightCorner;
            
			center = visitsMatrix->visibilityAtXY(x,y);
             
            //check if top left cell affects current
            
            if(x - 1 >= 0 && y + 1 < _height && !((wallCheckXYD(x - 1, y + 1,RIGHT)
                                                   || wallCheckXYD(x, y, UP))
                                                  && (wallCheckXYD(x - 1, y + 1,DOWN)
                                                      || wallCheckXYD(x, y, LEFT))))
                topLeft = visitsMatrix->visibilityAtXY(x - 1, y + 1);

            //check if top right cell affects current
            
            if(x + 1 < _width && y + 1 < _height && !((wallCheckXYD(x + 1,y + 1,LEFT)
                                                       || wallCheckXYD(x,y,UP))
                                                      && (wallCheckXYD(x + 1,y + 1,DOWN)
                                                          || wallCheckXYD(x,y,RIGHT))))
                topRight = visitsMatrix->visibilityAtXY(x + 1,y + 1);
            
            //check if bottom right cell affects current
            
            if(x + 1 < _width && y - 1 >= 0 && !((wallCheckXYD(x + 1,y - 1,LEFT)
                                                  || wallCheckXYD(x ,y ,DOWN))
                                                 && (wallCheckXYD(x + 1, y - 1, UP)
                                                     || wallCheckXYD(x, y,RIGHT))))
                bottomRight = visitsMatrix->visibilityAtXY(x + 1,y - 1);
            
            //check if bottom left cell affects current

			if(x - 1 >= 0 && y - 1 >= 0 && !((wallCheckXYD(x - 1,y - 1,RIGHT)
                                                  || wallCheckXYD(x ,y ,DOWN))
                                                 && (wallCheckXYD(x - 1, y - 1, UP)
												 || wallCheckXYD(x, y,LEFT))))
                bottomRight = visitsMatrix->visibilityAtXY(x - 1,y - 1);
            
            
            //checkings for top left corner
            //check if top cell affects current
            
            if(y + 1 < _height && !(wallCheckXYD(x,y,UP)
                                    && (wallCheckXYD(x,y,LEFT)
                                        || (x - 1 >= 0 ? wallCheckXYD(x - 1,y,UP) : true)
                                        || wallCheckXYD(x,y + 1,LEFT))))
                top = visitsMatrix->visibilityAtXY(x,y + 1);
            
            //check if left cell affects current
            
            if(x - 1 >= 0  && !(wallCheckXYD(x,y,LEFT)
                                && (wallCheckXYD(x, y, UP)
								|| (y + 1 < _height ? wallCheckXYD(x, y + 1, LEFT) : true)
                                    || wallCheckXYD(x - 1, y, UP))))
                left = visitsMatrix->visibilityAtXY(x - 1, y);
            
            int countOfAffectingValues = 4;
            
            if(topLeft == -1.0)
                countOfAffectingValues--;
            if(top == -1.0)
                countOfAffectingValues--;
            if(left == -1.0)
                countOfAffectingValues--;
            
            topLeftCorner = (center + topLeft + top + left + 4 - countOfAffectingValues)/countOfAffectingValues;
            //topLeftCorner = MAX(MAX(center, topLeft),MAX(top,left));
            _map[x][y][TOP_LEFT]  = topLeftCorner;
            
            //checkings for top right corner
            //check if top cell affects current
            
            
            if(y + 1 < _height && !(wallCheckXYD(x,y,UP)
                                    && (wallCheckXYD(x, y, RIGHT)
                                        || (x + 1 < _width ?wallCheckXYD(x + 1, y, UP) : true)
                                        || wallCheckXYD(x, y + 1, RIGHT))))
                top = visitsMatrix->visibilityAtXY(x,y + 1);
            else
                top = -1;
            
            //check if right cell affects current
            
            if(x + 1 < _width && !(wallCheckXYD(x, y, RIGHT)
                                   && (wallCheckXYD(x, y, UP)
                                       || (y + 1 < _height ? wallCheckXYD(x, y + 1, RIGHT) : true)
                                       || wallCheckXYD(x + 1, y, UP))))
                right = visitsMatrix->visibilityAtXY(x + 1, y);
            
            
            countOfAffectingValues = 4;
            
            if(topRight == -1.0)
                countOfAffectingValues--;
            if(top == -1.0)
                countOfAffectingValues--;
            if(right == -1.0)
                countOfAffectingValues--;
            
            topRightCorner = (center + topRight + top + right + 4 - countOfAffectingValues)/countOfAffectingValues;
            //topRightCorner = MAX(MAX(center, topRight),MAX(top,right));
            _map[x][y][TOP_RIGHT] = topRightCorner;
            
            //checkings for bottom right corner
            //check if right cell affects current
            
            if(x + 1 < _width && !(wallCheckXYD(x, y, RIGHT)
                                   && (wallCheckXYD(x, y, DOWN)
                                       || (y - 1 >= 0 ?wallCheckXYD(x, y - 1, RIGHT) : true)
                                       || wallCheckXYD(x + 1, y, DOWN))))
                right = visitsMatrix->visibilityAtXY( x + 1, y);
            else
                right = -1;
            
            //check if bottom cell affects current
            
            if(y - 1 >= 0 && !(wallCheckXYD(x, y, DOWN)
                               && (wallCheckXYD(x, y, RIGHT)
                                   || (x + 1 < _width ?wallCheckXYD(x + 1, y, DOWN) : true)
                                   || wallCheckXYD(x, y - 1, RIGHT))))
                bottom = visitsMatrix->visibilityAtXY(x, y - 1);
            
            countOfAffectingValues = 4;
            
            if(bottomRight == -1.0)
                countOfAffectingValues--;
            if(bottom == -1.0)
                countOfAffectingValues--;
            if(right == -1.0)
                countOfAffectingValues--;
            
            bottomRightCorner = (center + bottomRight + bottom + right + 4 - countOfAffectingValues)/countOfAffectingValues;
            //bottomRightCorner = MAX(MAX(center, bottomRight),MAX(bottom,right));
            _map[x][y][BOTTOM_RIGHT] = bottomRightCorner;
            
            
            
            //checkings for bottom left corner
            //check if left cell affects current
            
            
            if(x - 1 >= 0  && !(wallCheckXYD(x, y, LEFT)
                                && (wallCheckXYD(x, y, DOWN)
                                    || (y - 1 >= 0 ?wallCheckXYD(x, y - 1, LEFT) : true)
                                    || wallCheckXYD(x - 1, y, DOWN))))
                left = visitsMatrix->visibilityAtXY(x - 1, y);
            else
                left = -1;
            
            //check if bottom cell affects current
            
            if(y - 1 >= 0 && !(wallCheckXYD(x, y, DOWN)
                               && (wallCheckXYD(x, y, LEFT)
                                   || (x - 1 >= 0 ? wallCheckXYD(x - 1, y, DOWN) :true )
                                   || wallCheckXYD(x, y - 1, LEFT))))
                bottom = visitsMatrix->visibilityAtXY(x, y - 1);
            else
                bottom = -1;
            
            countOfAffectingValues = 4;
            
            if(bottomLeft == -1.0)
                countOfAffectingValues--;
            if(bottom == -1.0)
                countOfAffectingValues--;
            if(left == -1.0)
                countOfAffectingValues--;
            
            bottomLeftCorner = (center + bottomLeft + bottom + left + 4 - countOfAffectingValues)/countOfAffectingValues;
            //bottomLeftCorner = MAX(MAX(center, bottomLeft),MAX(bottom,left));
            _map[x][y][BOTTOM_LEFT]  = bottomLeftCorner;
        }
    }
}
void MZAlphaMap::updateToMap(MZAlphaMap* realMap)
{
    for(int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            for(int k = 0; k < 4; k++)
            {
				if(abs(_map[i][j][k] - realMap->valueAtXYinCorner(i, j,(MZCellCorners)k)) < ALPHA_SPEED)
                {
                    _map[i][j][k] = realMap->valueAtXYinCorner(i, j,(MZCellCorners)k);
                }
                else
                {
                    if(_map[i][j][k] > realMap->valueAtXYinCorner(i, j,(MZCellCorners)k))
                        _map[i][j][k] -= ALPHA_SPEED;
                    else
                        _map[i][j][k] += ALPHA_SPEED;
                }
            }
        }
    }
}
float MZAlphaMap::valueAtXYinCorner(int x, int y, MZCellCorners corner)
{
    return _map[x][y][corner];
}
