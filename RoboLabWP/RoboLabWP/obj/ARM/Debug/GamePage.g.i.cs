﻿#pragma checksum "C:\Users\AG\documents\visual studio 2012\Projects\RoboLabWP\RoboLabWP\RoboLabWP\GamePage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "2A261254FEBD7D2B912844C4E49CEF18"
//------------------------------------------------------------------------------
// <auto-generated>
//     Этот код создан программой.
//     Исполняемая версия:4.0.30319.34209
//
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторной генерации кода.
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
    
    
    public partial class GamePage : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.DrawingSurfaceBackgroundGrid DrawingSurfaceBackground;
        
        internal System.Windows.Controls.TextBlock MemoryTextBlock;
        
        internal System.Windows.Controls.TextBlock PeakMemoryTextBlock;
        
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
            System.Windows.Application.LoadComponent(this, new System.Uri("/RoboLabWP;component/GamePage.xaml", System.UriKind.Relative));
            this.DrawingSurfaceBackground = ((System.Windows.Controls.DrawingSurfaceBackgroundGrid)(this.FindName("DrawingSurfaceBackground")));
            this.MemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("MemoryTextBlock")));
            this.PeakMemoryTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("PeakMemoryTextBlock")));
        }
    }
}

