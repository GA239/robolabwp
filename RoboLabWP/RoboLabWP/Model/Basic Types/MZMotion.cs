using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RoboLabWP.Model.Basic_Types
{
    public class MZMotion
    {
        public double _speed;
        public MZDirection _direction;
        int _timesUsed;

        public MZMotion(double speed, MZDirection direction)
        {
            _speed = speed;
            _direction = direction;
            _timesUsed = 0;
        }

        void use()
        {
            _timesUsed++;
        }

        int timesUsed()
        {
            return _timesUsed;
        }
    }
}
