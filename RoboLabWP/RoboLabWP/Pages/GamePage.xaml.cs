#define DISPLAY_MEMORY

using System;
using System.Windows;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using RoboLabWPComp;

using Windows.Graphics.Display;
using System.Windows.Threading;
using Microsoft.Phone.Info;

using RoboLabWP.Model.Game;

namespace RoboLabWP
{
    public partial class GamePage : PhoneApplicationPage
    {
        private Direct3DInterop m_d3dInterop = null;
        private DispatcherTimer m_timer;
        public MZGame Game;

        public GamePage()
        {
            //Game = MZGame.getInstance();
            InitializeComponent();
            DrawingSurfaceBackground_Loaded();
            //NavigationService.Navigating += new NavigatingCancelEventHandler(NavigationService_Navigatingg);

            this.Loaded += new RoutedEventHandler(CancelNavigationPage_Loaded);
            this.Unloaded += new RoutedEventHandler(CancelNavigationPage_Unloaded);

            TimerPanel.Visibility = System.Windows.Visibility.Collapsed;
#if DISPLAY_MEMORY
            StartTimer();
            TimerPanel.Visibility = System.Windows.Visibility.Visible;
#endif
        }

        /*
        private void DrawingSurface_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_d3dInterop == null)
            {
                m_d3dInterop = new Direct3DInterop();

                
                // Задание границ окна в аппаратно-независимых пикселях (DIP)
                m_d3dInterop.WindowBounds = new Windows.Foundation.Size(
                    (float)DrawingSurface.ActualWidth,
                    (float)DrawingSurface.ActualHeight
                    );
                
                // Задание собственного разрешения в пикселях
                m_d3dInterop.NativeResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(DrawingSurface.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(DrawingSurface.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Задание для разрешения отрисовки значения полного собственного разрешения
                m_d3dInterop.RenderResolution = m_d3dInterop.NativeResolution;

                // Присоединение собственного компонента к DrawingSurface
                DrawingSurface.SetContentProvider(m_d3dInterop.CreateContentProvider());
                DrawingSurface.SetManipulationHandler(m_d3dInterop);
            }
        }
        */
        private void DrawingSurfaceBackground_Loaded()
        {
            
            if (m_d3dInterop == null)
            {
                m_d3dInterop = new Direct3DInterop();

                // Set native resolution in pixels
                m_d3dInterop.NativeResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(Application.Current.Host.Content.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(Application.Current.Host.Content.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Set render resolution to the full native resolution
                m_d3dInterop.RenderResolution = m_d3dInterop.NativeResolution;


                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurfaceBackground.SetBackgroundContentProvider(m_d3dInterop.CreateBackgroundContentProvider());
                DrawingSurfaceBackground.SetBackgroundManipulationHandler(m_d3dInterop);
                m_d3dInterop.WindowOrientation = DisplayOrientations.Portrait;
            }
        }

        void CancelNavigationPage_Loaded(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigating += new NavigatingCancelEventHandler(NavigationService_Navigatingg);
        }
        void CancelNavigationPage_Unloaded(object sender, RoutedEventArgs e)
        {         
            NavigationService.Navigating -= (NavigationService_Navigatingg);
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

        void NavigationService_Navigatingg(object sender, NavigatingCancelEventArgs e)
        {
            if (e.NavigationMode == NavigationMode.Back)
            {
                m_d3dInterop.clean();
                NavigationService.Navigating -= (NavigationService_Navigatingg);
            }
        }
    }
}