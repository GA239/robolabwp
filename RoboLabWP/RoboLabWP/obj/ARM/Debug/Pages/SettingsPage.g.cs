﻿#pragma checksum "C:\Users\AG\documents\visual studio 2012\Projects\RoboLabWP\RoboLabWP\RoboLabWP\Pages\SettingsPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "BD14E61CD40E50CA15A9F6EB4DFD7D6D"
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
    
    
    public partial class SettingsPage : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.TextBlock Title;
        
        internal Microsoft.Phone.Controls.ToggleSwitch toggleSwitch1;
        
        internal System.Windows.Controls.TextBlock TextBlock;
        
        internal Microsoft.Phone.Controls.Pivot Pivott;
        
        internal System.Windows.Controls.TextBlock Eng;
        
        internal System.Windows.Controls.TextBlock Rus;
        
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
            System.Windows.Application.LoadComponent(this, new System.Uri("/RoboLabWP;component/Pages/SettingsPage.xaml", System.UriKind.Relative));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.Title = ((System.Windows.Controls.TextBlock)(this.FindName("Title")));
            this.toggleSwitch1 = ((Microsoft.Phone.Controls.ToggleSwitch)(this.FindName("toggleSwitch1")));
            this.TextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("TextBlock")));
            this.Pivott = ((Microsoft.Phone.Controls.Pivot)(this.FindName("Pivott")));
            this.Eng = ((System.Windows.Controls.TextBlock)(this.FindName("Eng")));
            this.Rus = ((System.Windows.Controls.TextBlock)(this.FindName("Rus")));
            this.Return = ((System.Windows.Controls.Button)(this.FindName("Return")));
        }
    }
}

