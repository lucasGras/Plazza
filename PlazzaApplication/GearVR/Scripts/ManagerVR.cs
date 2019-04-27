using System.Collections;
using System.Collections.Generic;
using System.Net;
using Kitchens;
using TMPro;
using UnityEngine;

public class ManagerVR : MonoBehaviour
{
    public GameObject kitchenObj;
    public Kitchen kitchen;
    public Kitchen previousKitchen;
    [HideInInspector] public bool updated = false;

    private Vector3 _worldZero = new Vector3(-78, -20, 125);
    private List<GameObject> _kitchenInstance = new List<GameObject>();

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

    private void RefreshKitchenTextForce(GameObject kitchen, string txt)
    {
        kitchen.transform.Find("kitchen_debug").GetComponent<TextMeshPro>().text = txt;
    }

    private void RefreshCooksColors(Kitchen kitchen, int x, Transform child)
    {
        if (x <= (kitchen.available_cooks - (kitchen.max_cooks / 2)) - 1)
        {
            child.gameObject.SetActive(true);
            child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.green;
        }
        else if (x < kitchen.max_cooks / 2)
        {
            child.gameObject.SetActive(true);
            child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.red;
        }
        else
        {
            child.gameObject.SetActive(false);
        }
    }
    
    private void ProcessRefresh()
    {
        if (kitchen == null)
        {
            RefreshKitchenTextForce(kitchenObj, "Closed");
            return;
        }

        RefreshKitchenText(kitchen, kitchenObj);
        
        var childs = kitchenObj.transform.Find("Chefs");
        var x = 0;

        foreach (Transform child in childs)
        {
            RefreshCooksColors(kitchen, x, child);
            x++;
        }
        
        updated = false;
        previousKitchen = kitchen;
    }
}
