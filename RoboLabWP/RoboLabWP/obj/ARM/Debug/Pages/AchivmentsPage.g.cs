﻿#pragma checksum "C:\MANUAL_INFO\ANDR\robolabwp\RoboLabWP\RoboLabWP\Pages\AchivmentsPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "11E9897ADC7C042BE6D728D58627826A"
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
    
    
    public partial class AchivmentsPage : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.TextBlock Title;
        
        internal System.Windows.Controls.StackPanel TimerPanel;
        
        internal System.Windows.Controls.TextBlock MemoryTextBlock;
        
        internal System.Windows.Controls.TextBlock PeakMemoryTextBlock;
        
        internal System.Windows.Controls.Grid ContentPanel;
        
        internal System.Windows.Controls.Button Return;
        
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
            System.Windows.Application.LoadComponent(this, new System.Uri("/RoboLabWP;component/Pages/AchivmentsPage.xaml", System.UriKind.Relative));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.Title = ((System.Windows.Controls.TextBlock)(this.FindName("Title")));
            this.TimerPanel = ((System.Windows.Controls.StackPanel)(this.FindName("TimerPanel")));
            this.MemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("MemoryTextBlock")));
            this.PeakMemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("PeakMemoryTextBlock")));
            this.ContentPanel = ((System.Windows.Controls.Grid)(this.FindName("ContentPanel")));
            this.Return = ((System.Windows.Controls.Button)(this.FindName("Return")));
        }
    }
}

