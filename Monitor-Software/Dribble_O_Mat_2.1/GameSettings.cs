using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dribble_O_Mat_2._1
{
    public class GameSettings
    {
        public static int GameMode = 2;
        public int RoundTimeSeconds { get; set; } = 30;
        public int Sensitivity { get; set; } = 180;

        public string GameModeText()
        {
            string text = "";
            switch (GameMode)
            {
                case 0:
                    text = "READY";
                    break;
                case 1:
                    text = "GO!";
                    break;
                case 2:
                    text = "FINISH";
                    break;
                default:
                    text = "FINISH";
                    break;
            }
            return text;
        }
    }
}
