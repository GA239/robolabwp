using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//  MZPosition.cs
//  Maze
//
//  Класс реализующий двухмерный вектор для хранения позиций в игре.


namespace RoboLabWP.Model.Basic_Types
{
    public class MZPosition
    {
        double _x;
        double _y;

        public MZPosition(double x, double y)
        {
            _x = x;
            _y = y;
        }

        public double x()
        {
            return _x;
        }

        public double y()
        {
            return _y;
        }

        public void move(MZDirection direction)
        {
            switch (direction)
            {
                case MZDirection.LEFT:
                    _x--;
                    break;
                case MZDirection.UP:
                    _y++;
                    break;
                case MZDirection.RIGHT:
                    _x++;
                    break;
                case MZDirection.DOWN:
                    _y--;
                    break;
            }
        }

        public bool equals (MZPosition otherPosition)
        {
            if((_x == otherPosition._x) && (_y == otherPosition._y))
                return true;
            return false;
        }

        public MZPosition add(MZPosition pos2)
        {
            return new MZPosition(_x + pos2.x(), _y + pos2.y());
        }
    }
}
    