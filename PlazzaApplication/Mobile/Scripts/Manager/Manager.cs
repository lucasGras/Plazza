using System.Collections;
using System.Collections.Generic;
using System.Net;
using Kitchens;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class Manager : MonoBehaviour
{
    public KitchenList kitchens;
    public GameObject kitchenPrefab;
    [HideInInspector] public bool updated = false;

    private Vector3 _worldZero = new Vector3(-78, -20, 125);
    private List<GameObject> _kitchenInstance = new List<GameObject>();
    private int logLine = 0;

    private void Update()
    {
        if (!updated)
            return;
        ProcessRefresh();
    }

    private void RefreshKitchenText(Kitchen kitchen, GameObject instanciatedKitchen)
    {
        bool hasQueue = (kitchen.available_cooks < kitchen.max_cooks / 2);
        var textObj = instanciatedKitchen.transform.Find("kitchen_debug");
        var total = kitchen.doe + kitchen.ham + kitchen.eggplant
                    + kitchen.goatcheese + kitchen.gruyere + kitchen.mushrooms
                    + kitchen.steak + kitchen.tomato + kitchen.chieflove;
        string newKitchenText = total + " ingredients - ";

        if (hasQueue)
            newKitchenText += ((kitchen.max_cooks / 2) - kitchen.available_cooks).ToString();
        else
            newKitchenText += "No waiting pizzas";
        textObj.GetComponent<TextMeshPro>().text = newKitchenText;
    }

    private void DestroyInstances()
    {
        if (_kitchenInstance.Count != 0)
        {
            foreach (var instance in _kitchenInstance)
            {
                Destroy(instance);
            }
        }
    }

    private void RefreshCooksColors(Kitchen kitchen, int x, Transform child)
    {
        if (x < kitchen.available_cooks)
        {
            child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.green;
        }
        else if (x < kitchen.max_cooks / 2)
        {
            child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.red;
        }
        else
        {
            child.gameObject.SetActive(false);
        }
    }

    private void RefreshInstances()
    {
        var lines = (kitchens.kitchens.Count > 25) ? kitchens.kitchens.Count / 25 : 1;

        for (var i = 0; i < lines; i++)
        {
            for (var y = 0; y < kitchens.kitchens.Count % 25; y++)
            {
                var pos = new Vector3(_worldZero.x + (y * 7), _worldZero.y, _worldZero.z - (10 * (lines - 1)));
                var obj = Object.Instantiate(kitchenPrefab, pos, Quaternion.Euler(new Vector3(90, 0, 0)));
                var childs = obj.transform.Find("Chefs");
                var x = 0;

                RefreshKitchenText(kitchens.kitchens[i], obj);
                foreach (Transform child in childs)
                {
                    RefreshCooksColors(kitchens.kitchens[i], x, child);
                    x++;
                }

                _kitchenInstance.Add(obj);
            }
        }
    }
    
    private void ProcessRefresh()
    {
        var localScale = kitchenPrefab.transform.localScale;

        DestroyInstances();
        if (kitchens.kitchens.Count == 0)
            return;
        RefreshInstances();

        updated = false;
    }
}
