﻿#pragma checksum "C:\MANUAL_INFO\ANDR\robolabwp\RoboLabWP\RoboLabWP\Pages\MainPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "F5D89E96AA67D4F13883979FD7E417CA"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using Microsoft.Phone.Controls;
using System;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Automation.Peers;
using System.Windows.Automation.Provider;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Resources;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace RoboLabWP {
    
    
    public partial class MainPage : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.StackPanel TimerPanel;
        
        internal System.Windows.Controls.TextBlock MemoryTextBlock;
        
        internal System.Windows.Controls.TextBlock PeakMemoryTextBlock;
        
        internal System.Windows.Controls.StackPanel TitlePanel;
        
        internal System.Windows.Controls.TextBlock PageTitle;
        
        internal System.Windows.Controls.Grid ContentPanel;
        
        internal System.Windows.Controls.Button SettingsButton;
        
        internal System.Windows.Controls.Button StartButton;
        
        internal System.Windows.Controls.Button HowtoPlayButton;
        
        internal System.Windows.Controls.Button AchievementsButton;
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Windows.Application.LoadComponent(this, new System.Uri("/RoboLabWP;component/Pages/MainPage.xaml", System.UriKind.Relative));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.TimerPanel = ((System.Windows.Controls.StackPanel)(this.FindName("TimerPanel")));
            this.MemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("MemoryTextBlock")));
            this.PeakMemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("PeakMemoryTextBlock")));
            this.TitlePanel = ((System.Windows.Controls.StackPanel)(this.FindName("TitlePanel")));
            this.PageTitle = ((System.Windows.Controls.TextBlock)(this.FindName("PageTitle")));
            this.ContentPanel = ((System.Windows.Controls.Grid)(this.FindName("ContentPanel")));
            this.SettingsButton = ((System.Windows.Controls.Button)(this.FindName("SettingsButton")));
            this.StartButton = ((System.Windows.Controls.Button)(this.FindName("StartButton")));
            this.HowtoPlayButton = ((System.Windows.Controls.Button)(this.FindName("HowtoPlayButton")));
            this.AchievementsButton = ((System.Windows.Controls.Button)(this.FindName("AchievementsButton")));
        }
    }
}

