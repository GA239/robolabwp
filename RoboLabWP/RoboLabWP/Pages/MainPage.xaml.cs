//#define DISPLAY_MEMORY

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

using RoboLabWP.Model.Basic_Types;
using RoboLabWP.Languages;


namespace RoboLabWP
{
    public partial class MainPage : PhoneApplicationPage
    {
        private DispatcherTimer m_timer;

        public MainPage()
        {
            InitializeComponent();
            //extraInitialize();
            this.Loaded += new RoutedEventHandler(CancelNavigationPage_Loaded);
            this.Unloaded += new RoutedEventHandler(CancelNavigationPage_Unloaded);

            TimerPanel.Visibility = System.Windows.Visibility.Collapsed;
#if DISPLAY_MEMORY
                StartTimer();
            TimerPanel.Visibility = System.Windows.Visibility.Visible;
#endif
        }

        void CancelNavigationPage_Loaded(object sender, RoutedEventArgs e)
        {
            extraInitialize();
        }

        void CancelNavigationPage_Unloaded(object sender, RoutedEventArgs e)
        {

        }


        private void Button_Settings_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Pages/SettingsPage.xaml", UriKind.Relative));
        }
        private void Button_HowToPlay_Click(object sender, RoutedEventArgs e)
        {
            //NavigationService.Navigate(new Uri("/Pages/HowToPlayPage.xaml", UriKind.Relative));
        }
        private void Button_ModuleSelect_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Pages/GamePage.xaml", UriKind.Relative));
            //NavigationService.Navigate(new Uri("/Pages/ModuleSelectPage.xaml", UriKind.Relative));
        }
        private void Button_Achievements_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Pages/AchivmentsPage.xaml", UriKind.Relative));
        }

        private void extraInitialize()
        {
            PageTitle.Text = (Application.Current as App).UserGameData.StringContent.MainPageTitle;
            PageTitle.TextAlignment = TextAlignment.Center;

            StartButton.Content = (Application.Current as App).UserGameData.StringContent.MainPageStartButton;
            SettingsButton.Content = (Application.Current as App).UserGameData.StringContent.MainPageSettingsButton;
            HowtoPlayButton.Content = (Application.Current as App).UserGameData.StringContent.MainPageHowtoPlayButton;
            AchievementsButton.Content = (Application.Current as App).UserGameData.StringContent.MainPageАchievementsButton;
        }

        /* Timer */
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
        /* Timer */
    }
}