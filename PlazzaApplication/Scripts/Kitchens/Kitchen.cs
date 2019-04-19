using System;
using UnityEngine;

namespace Kitchens
{
    [Serializable]
    public class Kitchen
    {
        public int available_cooks;
        public int max_cooks;
        public int waiting_pizza;
        public int id;
        public int doe;
        public int eggplant;
        public int goatcheese;
        public int gruyere;
        public int ham;
        public int mushrooms;
        public int steak;
        public int tomato;
        public int chieflove;

        public static Kitchen FromJson(string json)
        {
            return JsonUtility.FromJson<Kitchen>(json);
        }
    }
}
