using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.IO.IsolatedStorage;

using RoboLabWP.Model.Basic_Types;

namespace RoboLabWP
    
{
    public partial class SettingsPage : PhoneApplicationPage
    {
        IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

        public SettingsPage()
        {
            InitializeComponent();
            InitializeSettings();
            extraInitialize();
            
        }

        private void InitializeSettings()
        {
            toggleSwitch1.IsChecked = (Application.Current as App).UserGameData.GameSettings.invariant_montion_mod;
            Pivott.SelectedIndex = CurrentLanguage((Application.Current as App).UserGameData.GameSettings.language);
        }

        private int CurrentLanguage(MZLanguage currentlanguage)
        {
            if(currentlanguage == MZLanguage.English)
            {
                return 0;
            }
            if(currentlanguage == MZLanguage.Russian)
            {
                return 1;
            }
            return -1;
        }

        private void extraInitialize()
        {
            Title.Text = (Application.Current as App).UserGameData.StringContent.SettingsPageTitle;
            Title.TextAlignment = TextAlignment.Center;
            Return.Content = (Application.Current as App).UserGameData.StringContent.BackButton;
            toggleSwitch1.Content = (Application.Current as App).UserGameData.StringContent.SettingsPageInverse;
            TextBlock.Text = (Application.Current as App).UserGameData.StringContent.SettingsPageLanguage;
            Eng.Text = (Application.Current as App).UserGameData.StringContent.SettingsPageEnglishLanguage;
            Rus.Text = (Application.Current as App).UserGameData.StringContent.SettingsPageRussianLanguage;
        }

        private void Button_Return_Click(object sender, RoutedEventArgs e)
        {
            if (Pivott.SelectedIndex == 0)
            {
                (Application.Current as App).UserGameData.GameSettings.language = MZLanguage.English;
            }
            if (Pivott.SelectedIndex == 1)
            {
                (Application.Current as App).UserGameData.GameSettings.language = MZLanguage.Russian;
            }
            (Application.Current as App).UserGameData.updateLanguage();
            NavigationService.GoBack();
        }

        private void toggleSwitch1_Click_1(object sender, RoutedEventArgs e)
        {
            (Application.Current as App).UserGameData.GameSettings.invariant_montion_mod = (bool)toggleSwitch1.IsChecked;
        }

    }
}