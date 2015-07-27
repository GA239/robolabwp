using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using System.Windows.Resources;
using System.Windows.Media.Imaging;
using System.Windows;

using System.IO.IsolatedStorage;
using System.IO;
using RoboLabWP.Languages;


namespace RoboLabWP.Model.UserData
{
    public class MZUserGameData
    {
        int modules_number = 6;
        public Image[] images;
        public Image[] locks;
        public Image head;
        public Settings GameSettings;
        public Controller StringContent;
        
        public int current_module = 0;

        public int levelnumber = 1;
        public bool want_to_continue = false;

        public int current_steps = 0;
        public int min_steps = 0;

        public bool restart = false;

        public MZUserGameData()
        {
            GameSettings = new Settings();
            updateLanguage();
            //update();
        }

        public void update()
        {
            int closed_number = size_closed(GameSettings.modules);
            int mod_count = modules_number - closed_number;
            locks = new Image[closed_number];
            images = new Image[mod_count];
            head = loadimage("image/robt0.png");

            for (int i = 0; i < closed_number; i++ )
            {
                locks[i] = loadimage("image/lock.png");
            }
            for (int i = 0; i < mod_count; i++)
            {
                images[i] = loadModule(i);
            }
        }

        public void updateLanguage()
        {
            StringContent = new Controller(GameSettings.language);         
        }

        Image loadModule(int i)
        {
            if (i == 0)
            {
                return loadimage("image/Sound processor.png");
            }
            if (i == 1)
            {
                return loadimage("image/Speech processor.png");
            }
            if (i == 2)
            {
                return loadimage("image/Memory.png");
            }
            if (i == 3)
            {
                return loadimage("image/CPU.png");
            }
            if (i == 4)
            {
                return loadimage("image/Reciever.png");
            }
            if (i == 5)
            {
                return loadimage("image/Optical module.png");
            }
            MessageBox.Show("Error reading modules images");
            return loadimage("image/robt0.png");
        }

        Image loadimage(string str)
        {
            Image img = new Image();

            Uri uri = new Uri(str, UriKind.Relative);
            StreamResourceInfo resourceInfo = Application.GetResourceStream(uri);
            BitmapImage bmp = new BitmapImage();
            bmp.SetSource(resourceInfo.Stream);
            img.Source = bmp;

            return img;
        }

        int size_closed(bool[] b)
        {
            int sum = 0;
            for (int i = 0; i < b.Length; i++)
            {
                if (!b[i])
                {
                    sum++;
                }
                else
                {
                    current_module = i;
                }
            }
            return sum;
        }
    }
}
