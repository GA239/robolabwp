#define DISPLAY_MEMORY

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

using Windows.Graphics.Display;
using System.Windows.Threading;
using Microsoft.Phone.Info;

namespace RoboLabWP
{
    public partial class MainPage : PhoneApplicationPage
    {
        // Конструктор
        private DispatcherTimer m_timer;

        public MainPage()
        {
            InitializeComponent();
#if DISPLAY_MEMORY
            StartTimer();
#endif
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("Pages/GamePage.xaml", UriKind.Relative));
        }

        private void StartTimer()
        {
            m_timer = new DispatcherTimer();
            m_timer.Interval = new TimeSpan(0, 0, 1);
            m_timer.Tick += new EventHandler(TimerTick);
            m_timer.Start();
        }

        private void TimerTick(object sender, EventArgs e)
        {
            try
            {
                // These are TextBlock controls that are created in the page’s XAML file.  
                float value = DeviceStatus.ApplicationCurrentMemoryUsage / (1024.0f * 1024.0f);
                MemoryTextBlock.Text = value.ToString();
                value = DeviceStatus.ApplicationPeakMemoryUsage / (1024.0f * 1024.0f);
                PeakMemoryTextBlock.Text = value.ToString();
            }
            catch (Exception ex)
            {
                MemoryTextBlock.Text = ex.Message;
            }
        }
    }
}