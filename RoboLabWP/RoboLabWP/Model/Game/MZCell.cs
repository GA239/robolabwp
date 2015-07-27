using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RoboLabWP.Model.Basic_Types;
//
//  MZCell.cs
//  Maze
//
//  Класс, объект которого хранит данные о клетке лабиринта. Не изменяется после построения лабиринта.

namespace RoboLabWP.Model.Game
{
    public class MZCell
    {
        public bool isEmpty;
        MZByte _walls;

        public MZCell()
        {
            _walls = new MZByte(0);
        }

        public void setWallsValue(MZByte walls)
        {
            _walls = walls;
        }

        public bool hasWallAtDirection(MZDirection direction)
        {
            int result =  (int)(_walls.value()) & (1 << (int) direction);
            return (result != 0 ? true : false);
        }
    }
}
