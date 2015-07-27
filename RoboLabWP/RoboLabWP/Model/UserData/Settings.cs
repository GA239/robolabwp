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
using RoboLabWP.Model.Basic_Types;


namespace RoboLabWP.Model.UserData
{
    public class Settings
    {
        public MZLanguage language;
        public bool invariant_montion_mod;
        public bool[] modules;

        public bool[] Sound_processor;
        public bool[] Speech_processor;
        public bool[] Memory;
        public bool[] CPU;
        public bool[] Reciever;
        public bool[] Optical_module;

        public Settings()
        {

            int modules_number = 6;
            language_check();
            inverse_check();
            modules_check();
            
            modules = new bool[modules_number];
            load_modules();
            levels_check();
            level_vectors_create();
            
            LoadSettings(false);
        }

        void language_check()
        {
            if (IsolatedStorageFile.GetUserStoreForApplication().FileExists("Language.txt") == false)
            {
                using (var file = IsolatedStorageFile.GetUserStoreForApplication().CreateFile("Language.txt"))
                {
                    using (var fileWriter = new StreamWriter(file))
                    {
                        String d = "English";
                        fileWriter.Write(d);
                    }
                }
            }
        }

        void inverse_check()
        {
            if (System.IO.IsolatedStorage.IsolatedStorageSettings.ApplicationSettings.Contains("Inverse") != true)
            {
                System.IO.IsolatedStorage.IsolatedStorageSettings.ApplicationSettings.Add("Inverse", true);
            }
        }

        void modules_check()
        {
            if (IsolatedStorageFile.GetUserStoreForApplication().FileExists("CurrentModules.txt") == false)
            {
                using (var file = IsolatedStorageFile.GetUserStoreForApplication().CreateFile("CurrentModules.txt"))
                {
                    using (var fileWriter = new StreamWriter(file))
                    {
                        String d = "100000";
                        fileWriter.Write(d);
                    }
                }
            }
        }

        void levels_check()
        {
            string current_mod_name;
            for (int i = 0; i < modules.Length; i++ )
            {
                current_mod_name = what_module(i);
                if (IsolatedStorageFile.GetUserStoreForApplication().FileExists(current_mod_name) == false)
                {
                    using (var file = IsolatedStorageFile.GetUserStoreForApplication().CreateFile(current_mod_name))
                    {
                        using (var fileWriter = new StreamWriter(file))
                        {
                            int levels_number = 60;
                            char[] g = new char[levels_number];
                            g[0] = '1';
                            for (int j = 1; j < levels_number; j++)
                            {
                                g[j] = '0';
                            }
                            fileWriter.Write(g);
                        }
                    }
                }
            }           
        }

        void level_vectors_create()
        {
            for (int i = 0; i < modules.Length; i++)
            {
                if (modules[i])
                {
                    if (!create_vector(i))
                        MessageBox.Show("Error reading module's levels");
                }
            }
        }

        public void LoadSettings(bool modules_load)
        {
            if (modules_load)
            {
                load_modules();
            }
            levels_load();
            invariant_montion_mod = (bool)IsolatedStorageSettings.ApplicationSettings["Inverse"];
            load_language();
        }

        public void SaveSettings()
        {
            IsolatedStorageSettings.ApplicationSettings["Inverse"] = invariant_montion_mod;
            IsolatedStorageSettings.ApplicationSettings.Save();
            save_language();
            save_modules();
            save_levels();
        }

        void save_modules()
        {
            using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile("CurrentModules.txt", FileMode.OpenOrCreate))
            {
                using (var filewriter = new StreamWriter(file))
                {
                    filewriter.Flush();
                    char[] g = char_to_bool(modules);
                    filewriter.Write(g);
                }
            }
        }

        void save_language()
        {
            using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile("Language.txt", FileMode.OpenOrCreate))
            {
                using (var filewriter = new StreamWriter(file))
                {
                    filewriter.Flush();
                    string a = MZlang_to_string(language);
                    filewriter.Write(a);
                }
            }
        }

        string MZlang_to_string(MZLanguage Language)
        {
            if(Language == MZLanguage.English)
            {
                return "English";
            }
            if (Language == MZLanguage.Russian)
            {
                return "Russian";
            }
            return "Error";
        }

        void save_levels()
        {
            for (int i = 0; i < modules.Length; i++)
            {
                if (modules[i])
                {
                    using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile(what_module(i), FileMode.OpenOrCreate))
                    {
                        using (var filewriter = new StreamWriter(file))
                        {
                            filewriter.Flush();
                            bool[] level = what_module_vector(i);
                            char[] g = char_to_bool(level);
                            filewriter.Write(g);
                        }
                    }
                }
            }
        }

        char[] char_to_bool(bool[] a)
        {
            char[] c = new char[a.Length];

            for (int i = 0; i < a.Length; i++ )
            {
                if (a[i])
                {
                    c[i] = '1';
                }
                else
                {
                    c[i] = '0';
                }
            }
            return c;
        }

        void load_modules()
        {
            using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile("CurrentModules.txt", FileMode.Open))
            {
                using (var fileReader = new StreamReader(file))
                {
                    modules = string_to_bool(fileReader.ReadToEnd());
                }
            }
        }

        void load_language()
        {
            using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile("Language.txt", FileMode.Open))
            {
                using (var fileReader = new StreamReader(file))
                {
                    language = WhatLanguage(fileReader.ReadToEnd());
                }
            }
        }

        MZLanguage WhatLanguage(string S)
        {
            if(S == "Russian")
            {
                return MZLanguage.Russian;
            }
            if (S == "English")
            {
                return MZLanguage.English;
            }
            return MZLanguage.ErrorLanguage;
        }

        void levels_load()
        {
            for (int i = 0; i < modules.Length; i++)
            {
                if (modules[i])
                {
                    using (var file = IsolatedStorageFile.GetUserStoreForApplication().OpenFile(what_module(i), FileMode.Open))
                    {
                        using (var fileReader = new StreamReader(file))
                        {
                            bool[] level;
                            level = string_to_bool(fileReader.ReadToEnd());
                            set_value_to_vector(level,i);
                        }
                    }
                }
            }
        }

        bool create_vector(int i)
        {
            int level_number = 60;
            if (i == 0)
            {
                Sound_processor = new bool[level_number];
                return true;
            }
            if (i == 1)
            {
                Speech_processor = new bool[level_number];
                return true;
            }
            if (i == 2)
            {
                Memory = new bool[level_number];
                return true;
            }
            if (i == 3)
            {
                CPU = new bool[level_number];
                return true;
            }
            if (i == 4)
            {
                Reciever = new bool[level_number];
                return true;
            }
            if (i == 5)
            {
                Optical_module = new bool[level_number];
                return true;
            }
            return false;
        }

        void copy(bool[] a, bool[] b)
        {
            for (int i = 0; i < a.Length; i++)
            {
                a[i] = b[i];
            }
        }

        public bool[] string_to_bool(string S)
        {
            int n = S.Length;
            bool[] b = new bool[n];

            for (int i = 0; i < n; i++)
            {
                if (S[i] == '1')
                {
                    b[i] = true;
                }
                if (S[i] == '0')
                {
                    b[i] = false;
                }
                if ((S[i] != '1') && (S[i] != '0'))
                {
                    MessageBox.Show("Error reading modules");
                }
            }
            return b;
        }

        public string what_module(int i)
        {
            if (i == 0)
            {
                return "Sound processor";
            }
            if (i == 1)
            {
                return "Speech processor";
            }
            if (i == 2)
            {
                return "Memory";
            }
            if (i == 3)
            {
                return "CPU";
            }
            if (i == 4)
            {
                return "Reciever";
            }
            if (i == 5)
            {
                return "Optical module";
            }
            MessageBox.Show("Error reading modules images");
            return "lool";
        }

        public bool[] what_module_vector(int i)
        {
            if (i == 0)
            {
                return Sound_processor;
            }
            if (i == 1)
            {
                return Speech_processor;
            }
            if (i == 2)
            {
                return Memory;
            }
            if (i == 3)
            {
                return CPU;
            }
            if (i == 4)
            {
                return Reciever;
            }
            if (i == 5)
            {
                return Optical_module;
            }
            MessageBox.Show("Error reading level");
            return modules;
        }

        public void set_value_to_vector(bool[] a, int i)
        {
            if (i == 0)
            {
                copy(Sound_processor,a);
            }
            if (i == 1)
            {
                copy(Speech_processor, a);
            }
            if (i == 2)
            {
                copy(Memory,a);
            }
            if (i == 3)
            {
                copy(CPU, a);              
            }
            if (i == 4)
            {
                copy(Reciever, a);              
            }
            if (i == 5)
            {
                copy(Optical_module,a);
            }
        }
    }
}
