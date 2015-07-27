using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RoboLabWP.Model.Basic_Types;

using System.Windows.Resources;
using System.Windows;

//
//  MZMaze.cs
//  Maze
//
//  Класс лабиринта. Хранит данные о его структуре. Не изменяется на протяжении жизни объекта.

namespace RoboLabWP.Model.Game
{
    public class MZMaze
    {
        int _width;
        int _height;
        int _minimalStepsRequired;
        
        MZPosition _winningPosition;
        MZPosition _startingPosition;
        MZCellMatrix _cellMatrix;
        List<MZFlow> _flowList;

        public MZMaze()
        {

            int cuurent_mod = (Application.Current as App).UserGameData.current_module;
            string path = (Application.Current as App).UserGameData.GameSettings.what_module(cuurent_mod);
            path = string.Concat(path,".mzp");
            //string path = "kal.mzp";            
            Uri uri = new Uri(path, UriKind.Relative);
            
            StreamResourceInfo sri = Application.GetResourceStream(uri);
            byte[] data = new byte[sri.Stream.Length];
            sri.Stream.Read(data, 0, data.Length);
            
            //int level = 1;
            int level = (Application.Current as App).UserGameData.levelnumber;
            
            int n = data[0];
            int baseOffset = 1 + n * 2 + data[1 + (level - 1) * 2] * 256 + data[2 + (level - 1) * 2]; 

            _width = data[baseOffset];
            _height = data[baseOffset + 1];
            _minimalStepsRequired = data[baseOffset + 2] * 256 + data[baseOffset + 3];
            _cellMatrix = new MZCellMatrix(_width, _height);

            for (int i = 0; i < _width; i++)
            {
                for (int j = 0; j < _height; j++)
                {
                    MZPosition thisPosition = new MZPosition(i, j);
                    MZCell thisCell = _cellMatrix.cellAtPosition(thisPosition);
                    MZByte thisCellData = new MZByte(data[baseOffset + i * _height + j + 4]);
                    MZByte walls = new MZByte((byte)(thisCellData.value() & MZMacro.LOW4BIT));
                    bool isWin = (thisCellData.value() & MZMacro.BIT5) != 0;
                    bool isStart = (thisCellData.value() & MZMacro.BIT6) != 0;
                    bool isEmpty = (thisCellData.value() & MZMacro.BIT7) != 0;
                    thisCell.isEmpty = isEmpty;
                    thisCell.setWallsValue(walls);
                    if (isWin)
                        _winningPosition = thisPosition;
                    if (isStart)
                        _startingPosition = thisPosition;
                }
            }
            _flowList = new List<MZFlow>();

            /*
            if(userGameData currentModuleName] isEqualToString: @"Reciever"] && level == 2)
            {
               [_flowList addObject:[[MZFlow alloc] initWithPosition: [[MZPosition alloc] initWithX:4 andY:8] direction: RIGHT length:6 andSpeed: 1.0/15.0]];
            }*/
            //cuurent_mod == 4 - Reciever
            if ((cuurent_mod == 4) && (level == 2))
            {
                MZPosition pos = new MZPosition(4, 8);
                MZFlow flow = new MZFlow(pos, MZDirection.RIGHT,6,1.0/15.0);
                _flowList.Add(flow);
            }
        }
        public MZCellMatrix cells()
        {
            return _cellMatrix;
        }

        public MZPosition startingPosition()
        {
            return _startingPosition;
        }

        public MZPosition winningPosition()
        {
            return _winningPosition;
        }

        public int width()
        {
            return _width;
        }

        public int height()
        {
            return _height;
        }

        public int minimalSteps()
        {
            return _minimalStepsRequired;
        }
        public List<MZFlow> flowList()
        {
            return _flowList;
        }
    }
}
