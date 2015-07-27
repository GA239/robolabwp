using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RoboLabWP.Model.Basic_Types;



namespace RoboLabWP.Model.Game
{
    public class MZFlow
    {
        MZDirection _direction;
        MZPosition _position;
        int _length;
        double _speed;
        bool _isInUse;
        int _frameUpdated;
        double _shift;

        public MZFlow(MZPosition pos, MZDirection dir, int length, double speed)
        {
            _position = pos;
            _direction = dir;
            _length = length;
            _speed = speed;
            _isInUse = false;
        }

        public MZDirection direction()
        {
            return _direction;
        }

        public MZPosition position()
        {
            return _position;
        }

        public int length()
        {
            return _length;
        }

        public double speed()
        {
            return _speed;
        }

        public double shift()
        {
            return _shift;
        }

        public bool isInFlow(MZPosition position)
        {
            switch (_direction)
            {
                case MZDirection.UP:
                    if(_position.x() != position.x())
                        return false;
                    else
                    {
                        if(_position.y() <= position.y() && position.y() < _position.y() + _length - 1)
                            return true;
                        else
                            return false;
                    }
                case MZDirection.RIGHT:
                    if(_position.y() != position.y())
                        return false;
                    else
                    {
                        if(_position.x() <= position.x() && position.x() < _position.x() + _length - 1)
                            return true;
                        else
                            return false;
                    }
                case MZDirection.DOWN:
                    if(_position.x() != position.x())
                        return false;
                    else
                    {
                        if(_position.y() >= position.y() && position.y() > _position.y() - _length + 1)
                            return true;
                        else
                            return false;
                    }
                case MZDirection.LEFT:
                    if(_position.y() != position.y())
                        return false;
                    else
                    {
                        if(_position.x() >= position.x() && position.x() > _position.x() - _length + 1)
                            return true;
                        else
                            return false;
                    }
                default:
                    return false;
            }
        }

        public MZMotion moveInFlowWithPositionandFrame(MZPosition position, int frame)
        {
            if(!isInFlow(position))
            {
                _isInUse = false;
                _shift = 0;
                return null;
            }
            if(!_isInUse)
            {
                _isInUse = false;
                _frameUpdated = frame;
                position.move(_direction);
                 _shift = 0;
                return new  MZMotion(_speed, _direction);
            }
            else
            {
                if(frame - _frameUpdated >= 1.0 / _speed)
                {
                    _frameUpdated = frame;
                    position.move(_direction);
                    return new MZMotion(_speed, _direction);
                }
                _shift = (double)(frame - _frameUpdated) * _speed;
            }
            return null;
        }
    }
}
