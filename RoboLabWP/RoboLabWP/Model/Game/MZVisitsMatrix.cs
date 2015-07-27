using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RoboLabWP.Model.Basic_Types;
//
//  MZVisitsMatrix.cs
//  Maze
//
//  Класс, являющийся представлением двумерного массива значений времени последнего посещения клеток лабиринта юзером.
//  Под посещением понимается то, что клетка была видна с позции нанобота в лабиринте.

namespace RoboLabWP.Model.Game
{
    public class MZVisitsMatrix
    {
       
        private List<List<int>> _visits;
        private int _width, _height;

        public MZVisitsMatrix (int width, int height)
        {
            _width = width;
            _height = height;
            _visits = new List<List<int>>();
            for (int i = 0; i < _width; i++)
            {
                _visits.Add(new List<int>());
                for (int j = 0; j < _height; j++)
                {
                    _visits[i].Add(new int());
                    _visits[i][j] = -MZMacro.LAST_STEPS_VISIBLE;
                }
            }
        }

        public int lastVisitAtPoisiton(MZPosition position)
        {
            if (position.x() >= 0 && position.y() >= 0 && position.x() < _visits.Count() && position.y() < _visits[0].Count())
            {
                return _visits[(int)position.x()][(int)position.y()];
            }
            return -MZMacro.LAST_STEPS_VISIBLE;
        }

        public void setLastVisit(int step, MZPosition position)
        {
            if (position.x() >= 0 && position.y() >= 0 && position.x() < _visits.Count() && position.y() < _visits[0].Count())
            {
                _visits[(int)position.x()][(int)position.y()] = step;
            }
        }
        /*
        -(double)visibilityAtX:(int) x Y: (int) y
        {
            if(x >= 0 && y >=0 && x < _width && y < _height)
            {
                int lastVisit = [_visits[x][y] integerValue];
                return MAX((1.0 - (double)([[MZGame getInstance] stepsCount] - lastVisit)/(double)LAST_STEPS_VISIBLE),0.0);
            }
            NSLog(@"Cell out of range");
            return -LAST_STEPS_VISIBLE;
        }*/
        public double visibilityAtXY(int x, int y)
        {
            if(x >= 0 && y >=0 && x < _width && y < _height)
            {
                int lastVisit = _visits[x][y];
                //MZGame game = MZGame.getInstance();
                //return max((1.0 - (double)(game.stepsCount() - lastVisit)/(double)MZMacro.LAST_STEPS_VISIBLE),0.0);
                return max((1.0 - (double)(MZGame.getInstance().stepsCount() - lastVisit) / (double)MZMacro.LAST_STEPS_VISIBLE), 0.0);
            }
            return -MZMacro.LAST_STEPS_VISIBLE;
        }

        double max(double a, double b)
        {
            if (a >= b)
            {
                return a;
            }
            return b;
        }
    }
}
