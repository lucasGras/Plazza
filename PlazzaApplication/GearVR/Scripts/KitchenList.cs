using System;
using System.Collections.Generic;
using UnityEngine;

namespace Kitchens
{
    [Serializable]
    public class KitchenList
    {
        public List<Kitchen> kitchens;

        public static KitchenList FromJson(string json)
        {
            return JsonUtility.FromJson<KitchenList>(json);
        }
    }
}