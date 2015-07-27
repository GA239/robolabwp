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
using RoboLabWPComp;

using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
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