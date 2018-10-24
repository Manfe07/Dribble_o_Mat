using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Dribble_O_Mat_2._1
{
    public class Settings : DependencyObject
    {
        public static readonly DependencyProperty HighscoreProperty = DependencyProperty.Register("Highscore", typeof(int), typeof(Settings), new UIPropertyMetadata(0));

        public int Highscore
        {
            get { return (int)this.GetValue(HighscoreProperty); }
            set { this.SetValue(HighscoreProperty, value); }
        }


        public static readonly DependencyProperty Time_DurationProperty = DependencyProperty.Register("Time_Duration", typeof(TimeSpan), typeof(Settings), new UIPropertyMetadata(new TimeSpan(0,0,30)));

        public TimeSpan Time_Duration
        {
            get { return (TimeSpan)this.GetValue(Time_DurationProperty); }
            set { this.SetValue(Time_DurationProperty, value); }
        }


        public static readonly DependencyProperty Time_FinishProperty = DependencyProperty.Register("Time_Finish", typeof(DateTime), typeof(Settings), new UIPropertyMetadata(DateTime.MinValue));

        public DateTime Time_Finish
        {
            get { return (DateTime)this.GetValue(Time_FinishProperty); }
            set { this.SetValue(Time_FinishProperty, value); }
        }


        public static readonly DependencyProperty Time_RemainingProperty = DependencyProperty.Register("Time_Remaining", typeof(TimeSpan), typeof(Settings), new UIPropertyMetadata(new TimeSpan(0, 0, 0)));

        public TimeSpan Time_Remaining
        {
            get { return (TimeSpan)this.GetValue(Time_RemainingProperty); }
            set { this.SetValue(Time_RemainingProperty, value); }
        }


        public static readonly DependencyProperty RunningProperty = DependencyProperty.Register("Running", typeof(bool), typeof(Settings), new UIPropertyMetadata(false));
            
        public Boolean Running
        {
            get { return (Boolean)this.GetValue(RunningProperty); }
            set { this.SetValue(RunningProperty, value); }
        }
    }
}
