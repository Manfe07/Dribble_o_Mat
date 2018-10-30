using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace Dribble_O_Mat_2._1
{
    public class SerialSettings
    {
        public List<string> SerialPorts { get; private set; }
        public string SerialPort { get; set; }
        public int Baud { get; set; } = 250000;

        public SerialSettings()
        {
            LoadSerialPorts();
        }

        public void LoadSerialPorts()
        {
            SerialPorts = System.IO.Ports.SerialPort.GetPortNames().ToList();
        }
    }
}
