using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RoboLabWP.Model.Basic_Types;

//
//  MZGame.cs
//  Maze
//
//  Класс данных текущей игры, у которого никогда не бывает одновременно больше одного экземпляра.
//  Создание нового экземпляра с помощью метода start: влечет разрушение старого.
//  Хранит указатель на лабиринт и игровые данные, которые изменяются во время прохождения уровня. 

namespace RoboLabWP.Model.Game
{
    public class MZGame
    {
        private static MZGame instance;

        public MZMaze _maze;
        public MZPosition _currentPosition;
        public MZVisitsMatrix _visitsMatrix;

        int _stepsCount;
        int _minimalSteps;

        bool _isPaused;
        bool _isEnded;

        private MZGame()
        {
            _maze = new MZMaze();
            
            _stepsCount = 0;
            _minimalSteps = _maze.minimalSteps();
            
            _currentPosition = _maze.startingPosition();
            _visitsMatrix = new MZVisitsMatrix(_maze.width(), _maze.height());
            
            visitPosition(_currentPosition);
            _isEnded = false;
            _isPaused = false;
        }

        public static MZGame getInstance()
        {
            if(instance == null)
                {
                    instance = new MZGame();
                }
                return instance;
        }

        public static MZGame Start()
        {
            return instance = new MZGame();
        }

        MZMotion  updateWithFrame(int frame)
        {
            List<MZFlow> flowList = _maze.flowList();
            MZMotion result = null;

            for (int i = 0; i < flowList.Count(); i++)
            {
                result = flowList[i].moveInFlowWithPositionandFrame(_currentPosition,frame);
            }
            return result;
        }

        public MZMoveResultCode makeStepTo(MZDirection direction)
        {
            if (_isPaused)
                return MZMoveResultCode.GAME_PAUSED;

            /*
            List<MZFlow> flowList = _maze.flowList();
            for (int i = 0; i < flowList.Count(); i++)
            {
                if (flowList[i].isInFlow(_currentPosition))
                {
                    if ((direction == flowList[i].direction()) || (direction == (flowList[i].direction() + 2) % 2))
                    {
                        return MZMoveResultCode.MOTION_IMPOSSIBLE;	
                    }
                }
            }*/

            if (!_maze.cells().cellAtPosition(_currentPosition).hasWallAtDirection(direction))
            {
                _currentPosition.move(direction);
                _stepsCount++;
                visitPosition(_currentPosition);
                if ((_maze.winningPosition().x() == _currentPosition.x()) && (_maze.winningPosition().y() == _currentPosition.y()))
                {
                    _isEnded = true;
                    return MZMoveResultCode.GAME_ENDED;
                }
                else
                    return MZMoveResultCode.MOTION_PERFORMED;
            }
               return MZMoveResultCode.MOTION_IMPOSSIBLE;	
        }



        public void visitPosition(MZPosition position)
        {
            _visitsMatrix.setLastVisit(_stepsCount, position);
            MZCellMatrix cellMatrix = _maze.cells();
            MZPosition iteratorPosition = new MZPosition(position.x(), position.y());
            
            while (iteratorPosition.x() > 0)
            {
                if (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.LEFT))
                    break;
                iteratorPosition.move(MZDirection.LEFT);
                _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
            }

            iteratorPosition = new MZPosition(position.x(), position.y());

            while (iteratorPosition.y() > 0)
            {
                if (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.DOWN))
                    break;
                iteratorPosition.move(MZDirection.DOWN);
                _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
            }

            iteratorPosition = new MZPosition(position.x(), position.y());

            while (iteratorPosition.x() < _maze.width() - 1)
            {
                if (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.RIGHT))
                    break;
                iteratorPosition.move(MZDirection.RIGHT);
                _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
            }
            iteratorPosition = new MZPosition(position.x(), position.y());

            while (iteratorPosition.y() < _maze.height() - 1)
            {
                if (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.UP))
                    break;
                iteratorPosition.move(MZDirection.UP);
                _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
            }

            if((!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.LEFT)) && (!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.DOWN)))
            {
                iteratorPosition = new MZPosition(position.x(), position.y());
                iteratorPosition.move(MZDirection.LEFT);
                iteratorPosition.move(MZDirection.DOWN);

                while (iteratorPosition.x() >= 0)
                {
                    if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.RIGHT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.UP))) 
                        break;
                    MZPosition tempPosition = iteratorPosition;
                    while (iteratorPosition.y() >= 0)
                    {
                        if((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.RIGHT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.UP)))
                        {
                            break;
                        }
                        _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
                        iteratorPosition.move(MZDirection.DOWN);
                    }
                    iteratorPosition = tempPosition;
                    iteratorPosition.move(MZDirection.LEFT);
                }
            }

            if ((!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.LEFT)) && (!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.UP)))
            {
                iteratorPosition = new MZPosition(position.x(), position.y());
                iteratorPosition.move(MZDirection.LEFT);
                iteratorPosition.move(MZDirection.UP);

                while (iteratorPosition.x() >= 0)
                {
                    if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.RIGHT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.DOWN)))
                        break;
                    MZPosition tempPosition = iteratorPosition;
                    while (iteratorPosition.y() < _maze.height())
                    {
                        if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.RIGHT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.DOWN)))
                        {
                            break;
                        }
                        _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
                        iteratorPosition.move(MZDirection.UP);
                    }
                    iteratorPosition = tempPosition;
                    iteratorPosition.move(MZDirection.LEFT);
                }
            }

            if ((!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.RIGHT)) && (!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.DOWN)))
            {
                iteratorPosition = new MZPosition(position.x(), position.y());
                iteratorPosition.move(MZDirection.RIGHT);
                iteratorPosition.move(MZDirection.DOWN);

                while (iteratorPosition.x() < _maze.width())
                {
                    if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.LEFT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.UP)))
                        break;
                    MZPosition tempPosition = iteratorPosition;
                    while (iteratorPosition.y() >= 0)
                    {
                        if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.LEFT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.UP)))
                        {
                            break;
                        }
                        _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
                        iteratorPosition.move(MZDirection.DOWN);
                    }
                    iteratorPosition = tempPosition;
                    iteratorPosition.move(MZDirection.RIGHT);
                }
            }

            if ((!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.RIGHT)) && (!cellMatrix.cellAtPosition(position).hasWallAtDirection(MZDirection.UP)))
            {
                iteratorPosition = new MZPosition(position.x(), position.y());
                iteratorPosition.move(MZDirection.RIGHT);
                iteratorPosition.move(MZDirection.UP);

                while (iteratorPosition.x() < _maze.width())
                {
                    if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.LEFT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.DOWN)))
                        break;
                    MZPosition tempPosition = iteratorPosition;
                    while (iteratorPosition.y() < _maze.height())
                    {
                        if ((cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.LEFT)) || (cellMatrix.cellAtPosition(iteratorPosition).hasWallAtDirection(MZDirection.DOWN)))
                        {
                            break;
                        }
                        _visitsMatrix.setLastVisit(_stepsCount, iteratorPosition);
                        iteratorPosition.move(MZDirection.UP);
                    }
                    iteratorPosition = tempPosition;
                    iteratorPosition.move(MZDirection.RIGHT);
                }
            }
        }

        public void pause()
        {
            _isPaused = true;
        }
        public void resume()
        {
            _isPaused = false;
        }
        public bool isPaused()
        {
            return _isPaused;
        }
        public bool isEnded()
        {
            return _isEnded;
        }
        public int stepsCount()
        {
            return _stepsCount;
        }
        public int minimalSteps()
        {
            return _minimalSteps;
        }
    }
}
