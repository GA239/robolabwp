using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RoboLabWP.Model.Basic_Types;

namespace RoboLabWP.Languages
{
    public class Controller
    {
        public string BackButton;
        public string SelectButton;
        
        //MainPage
        public string MainPageTitle;
        public string MainPageStartButton;
        public string MainPageSettingsButton;
        public string MainPageHowtoPlayButton;
        public string MainPageАchievementsButton;
        
        //AchievementsPage
        public string AchievementsPageTitle;

        //SettingsPage
        public string SettingsPageTitle;
        public string SettingsPageInverse;
        public string SettingsPageLanguage;
        public string SettingsPageEnglishLanguage;
        public string SettingsPageRussianLanguage;

        //SelectModulePage
        public string SelectModulePageTitle;

        //SelectLevelPage
        public string SelectLevelPageTitle;

        //GamePage
        public string GamePagePauseButton;
        public string GamePageLevels;
        public string GamePageSteps;

        public Controller(MZLanguage language)
        {
            if (language == MZLanguage.Russian)
            {
                RussianInit();
            }
            if (language == MZLanguage.English)
            {
                EnglishInit();
            }
        }

        private void RussianInit()
        {
            BackButton = "Назад";
            SelectButton = "Выбрать";

            //MainPage
            MainPageTitle = "Robo-Lab";
            MainPageStartButton = "Старт";
            MainPageSettingsButton = "Настройки";
            MainPageHowtoPlayButton = "Помощь";
            MainPageАchievementsButton = "Достижения";

            //AchievementsPage
            AchievementsPageTitle = "Достижения";

            //SettingsPage
            SettingsPageTitle = "Настройки";
            SettingsPageInverse = "Обратное\nУправление:";
            SettingsPageLanguage = "Язык:";
            SettingsPageEnglishLanguage = "Английский";
            SettingsPageRussianLanguage = "Русский";

            //SelectModulePage
            SelectModulePageTitle = "Выберите Модуль";

            //SelectLevelPage
            SelectLevelPageTitle = "Выберите Уровень";

            //GamePage
            GamePagePauseButton = "Пауза";
            GamePageLevels = "уровни:";
            GamePageSteps = "шаги:";

        }
        private void EnglishInit()
        {
            BackButton = "Return";
            SelectButton = "Select";
        
            //MainPage
            MainPageTitle = "Robo-Lab";
            MainPageStartButton = "Start";
            MainPageSettingsButton = "Settings";
            MainPageHowtoPlayButton = "How to Play";
            MainPageАchievementsButton = "Аchievements";

            //AchievementsPage
            AchievementsPageTitle = "Achievements";

            //SettingsPage
            SettingsPageTitle = "Settings";
            SettingsPageInverse = "Reverse\nControls:";
            SettingsPageLanguage = "Language:";
            SettingsPageEnglishLanguage = "English";
            SettingsPageRussianLanguage = "Russian";

            //SelectModulePage
            SelectModulePageTitle = "Select Module";

            //SelectLevelPage
            SelectLevelPageTitle = "Select Level";

            //GamePage
            GamePagePauseButton = "Pause";
            GamePageLevels = "levels:";
            GamePageSteps = "steps:";
        }
    }
}
