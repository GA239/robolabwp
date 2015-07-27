using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
// Файл, содержащий различные определения.
namespace RoboLabWP.Model.Basic_Types
{
    public enum MZDirection
    {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };

    public enum MZMoveResultCode
    {
        MOTION_IMPOSSIBLE,
        MOTION_PERFORMED,
        GAME_ENDED,
        GAME_PAUSED
    };

    public class MZMacro
    {
        public static int LAST_STEPS_VISIBLE = 6;
        public static double MOVE_SPEED = 0.2;
        public static double ALPHA_SPEED = 0.05;
        public static int CELL_SIZE_IN_PIXELS = 100;
        public static int ANIMATION_LENGTH_IN_FRAMES = 5;
        public static int LOW4BIT = 15;
        public static int BIT7 = 64;
        public static int BIT6 = 32;
        public static int BIT5 = 16;    
    }

    public enum MZLanguage
    {
        Russian,
        English,
        ErrorLanguage
    };
}
