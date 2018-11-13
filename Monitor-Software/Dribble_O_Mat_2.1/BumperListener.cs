using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Windows;

namespace Dribble_O_Mat_2._1
{
    public  class BumperListener : DependencyObject
    {
        public static readonly DependencyProperty CurrentBumpsProperty = DependencyProperty.Register("CurrentBumps", typeof(int), typeof(BumperListener), new UIPropertyMetadata(0));

        public int CurrentBumps
        {
            get { return (int)this.GetValue(CurrentBumpsProperty); }
            set { this.SetValue(CurrentBumpsProperty, value); }
        }

        public Settings Settings { get; set; }
        public SerialSettings SerialSettings { get; set; }
        public GameSettings GameSettings { get; set; }

        private System.IO.Ports.SerialPort _serialPort;
        private readonly MainWindow _mainWindow;

        public BumperListener(MainWindow mainWindow)
        {
            _mainWindow = mainWindow;
            SerialSettings = new SerialSettings();
            Settings = new Settings();
            GameSettings = new GameSettings();
        }

        public bool SerialIsConnected()
        {
            return _serialPort != null && _serialPort.IsOpen;
        }

        public void SerialConnect()
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.Close();
                _serialPort = null;
            }

            if (!string.IsNullOrEmpty(SerialSettings.SerialPort)) { 
             _serialPort = new SerialPort
             {
                 PortName = SerialSettings.SerialPort,
                 BaudRate = SerialSettings.Baud
             };

            _serialPort.Open();
                _mainWindow.SerialConnectButton.IsEnabled = false;
                _mainWindow.SerialDisconnectButton.IsEnabled = true;
                Task.Run(() => ListenSerialPort());
            }
        }

        public void SerialDisconnect()
        {
            if (_serialPort != null && _serialPort.IsOpen) _serialPort.Close();

            _mainWindow.SerialConnectButton.IsEnabled = true;
            _mainWindow.SerialDisconnectButton.IsEnabled = false;
        }

        Boolean status = false;
        Boolean taster = true;

        public void Start()
        {
            Debug.WriteLine($"Sensivity: {GameSettings.Sensitivity}");
            Debug.WriteLine($"Time per Round (Sec): {GameSettings.RoundTimeSeconds}");

            if (SerialIsConnected())
            {
                _serialPort.WriteLine("0");

                _serialPort.WriteLine(GameSettings.Sensitivity.ToString());
            }

            _mainWindow.button_Start.IsEnabled = false;            
            this.Settings.Time_Duration = new TimeSpan(0, 0, GameSettings.RoundTimeSeconds);
            this.Settings.Time_Finish = DateTime.Now + this.Settings.Time_Duration;            
            this.CurrentBumps = 0;
            //this.Settings.Running = true;
            status = true;
            this.Time_Calc();        
        }

        public void Countdown()
        {
            _mainWindow.button_Start.IsEnabled = false;

            taster = false;

            var countdown = new System.Timers.Timer(50);
            var finishTime = DateTime.Now + new TimeSpan(0,0,4);

            //may remove "var finished" ?
            //var finished = false;
            
            this.CurrentBumps = 0;

            countdown.Elapsed += (object sender, System.Timers.ElapsedEventArgs e) =>
            {
                var currentTime = DateTime.Now;
                var remaining = finishTime - currentTime;
                 
                App.Current.Dispatcher.BeginInvoke(new Action(() =>
                {
                    Debug.WriteLine(remaining);
                    if (remaining.Seconds > 1)
                        Settings.GameModeText = "READY";
                    else if (remaining.Seconds > 0)
                        Settings.GameModeText = "SET";
                    Debug.WriteLine(Settings.GameModeText);
                    //this.Settings.Time_Remaining = remaining;
                }));

                if (currentTime > finishTime)
                {
                    countdown.Stop();
                    App.Current.Dispatcher.BeginInvoke(new Action(() =>
                    {
                        this.Settings.GameModeText = "GO!";
                        Start();
                    }));
                }
            };               
            
            countdown.Start();
        }

        public void KeyInput(Object sender)
        {
            if(_mainWindow.button_Start.IsEnabled==true)
            {
                this.Countdown();
            }
        }

        public void Time_Calc()
        {
            var timer = new System.Timers.Timer(100);

            var finishTime = this.Settings.Time_Finish;

            timer.Elapsed += (object sender, System.Timers.ElapsedEventArgs e) =>
            {
                var currentTime = DateTime.Now;

                App.Current.Dispatcher.BeginInvoke(new Action(() =>
                {
                    var remaining = finishTime - currentTime;
                    Debug.WriteLine(remaining);
                    this.Settings.Time_Remaining = remaining;
                }));
                                
                if (currentTime > finishTime)
                {
                    this.Finish();
                    timer.Stop();
                }               
            };

            timer.Start();            
        }

        public void Finish()
        {
            App.Current.Dispatcher.BeginInvoke(new Action(() =>
            {
                this.Settings.Time_Remaining = new TimeSpan(0);
                _mainWindow.button_Start.IsEnabled = true;
                this.Settings.Running = false;
                status = false;
                taster = true;
                this.Settings.GameModeText = "FINISH";

                if (this.CurrentBumps > this.Settings.Highscore)
                {
                    this.Settings.Highscore = this.CurrentBumps;                       
                }
            }));
        }
                
        private void ListenSerialPort()
        {
            while(SerialIsConnected())
            {
                Boolean is_running = false;
                var line = _serialPort.ReadLine();
                Debug.WriteLine(line.Trim());
                App.Current.Dispatcher.BeginInvoke(new Action(() =>
                {
                    is_running = this.Settings.Running;
                }));
                if (status)
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        {
                            CurrentBumps = Convert.ToInt32(line.Trim());
                        }
                    });
                }
                else if(taster)
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        {
                            if (line.Trim() == "Start")
                            {
                                this.Countdown();
                            };
                        }
                    });
                }
                System.Threading.Thread.Sleep(100);
            }
        }
    }
}
