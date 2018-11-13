using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;

namespace Dribble_O_Mat_2._1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static readonly DependencyProperty BumperListenerProperty = DependencyProperty.Register("BumperListener", typeof(BumperListener), typeof(MainWindow), new UIPropertyMetadata(null));

        public BumperListener BumperListener
        {
            get { return (BumperListener)this.GetValue(BumperListenerProperty); }
            set { this.SetValue(BumperListenerProperty, value); }
        }       

        public MainWindow()
        {
            BumperListener = new BumperListener(this);
            InitializeComponent();
            WindowState = WindowState.Maximized;
            WindowStyle = WindowStyle.None;
            this.Topmost = true;
        }
        
        private void button_Click(object sender, RoutedEventArgs e)
        {
            BumperListener.Countdown();                        
        }

        private void button_exit_Click(object sender, RoutedEventArgs e)
        {
            BumperListener.SerialDisconnect();
            Application.Current.Shutdown();
        }

        private void SerialConnectButton_Click(object sender, RoutedEventArgs e)
        {
            BumperListener.SerialConnect();
        }

        private void SerialDisconnectButton_Click(object sender, RoutedEventArgs e)
        {
            BumperListener.SerialDisconnect();
        }        
    }
}
