using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


//
//  MZByte.cs
//  Maze
//
//  Тип представляющий собой переопределение unsigned char. Нужен для представления байта.

namespace RoboLabWP.Model.Basic_Types
{
    public class MZByte
    {
        private byte _value;
        
        public MZByte(byte value)
        {
            _value = value;
        }

        public byte value()
        {
             return _value;
        }
    }
}
