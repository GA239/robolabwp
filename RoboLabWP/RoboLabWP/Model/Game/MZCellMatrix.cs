using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RoboLabWP.Model.Basic_Types;
//
//  MZCellMatrix.cs
//  Maze
//
//  Класс, являющийся представлением двумерного массива объектов класса MZCell.

namespace RoboLabWP.Model.Game
{
    public class MZCellMatrix
    {
        private List<List<MZCell>> _cells;
         
        public MZCellMatrix(int width, int height)
        {
            _cells = new List<List<MZCell>>();
            for (int i = 0; i < width; i++)
            {
                _cells.Add(new List<MZCell>());
                for (int j = 0; j < height; j++)
                    _cells[i].Add(new MZCell());
            }
        }

        // вызврат клетки через позицию
        public MZCell cellAtPosition(MZPosition position)
        {
            if (position.x() >= 0 && position.y() >= 0 && position.x() < _cells.Count() && position.y() < _cells[0].Count())
            {
                return _cells[(int)position.x()][(int)position.y()];
            }
            return new MZCell();
        }
    }
}
