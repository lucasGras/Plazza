using System.Collections;
using System.Collections.Generic;
using System.Net;
using Kitchens;
using TMPro;
using UnityEngine;

public class Manager : MonoBehaviour
{
    public KitchenList kitchens;
    public GameObject kitchenPrefab;
    [HideInInspector] public bool updated = false;

    private Vector3 _worldZero = new Vector3(-78, -20, 125);
    private List<GameObject> _kitchenInstance = new List<GameObject>();

    void Update()
    {
        Cursor.visible = true;
        if (!updated)
            return;
        ProcessRefresh();
    }

    void ProcessRefresh()
    {
        var localScale = kitchenPrefab.transform.localScale;

        if (_kitchenInstance.Count != 0)
        {
            foreach (var instance in _kitchenInstance)
            {
                Destroy(instance);
            }
        }
        for (var i = 0; i < kitchens.kitchens.Count; i++)
        {
            var pos = new Vector3(_worldZero.x + (i * 7), _worldZero.y, _worldZero.z - ((i % 70) * 10));
            var obj = Object.Instantiate(kitchenPrefab, pos, Quaternion.Euler(new Vector3(90, 0, 0)));
            var childs = obj.transform.Find("Chefs");
            var kitchenDebug = obj.transform.Find("kitchen_debug");
            var x = 0;
            var total = kitchens.kitchens[i].doe + kitchens.kitchens[i].ham + kitchens.kitchens[i].eggplant
                        + kitchens.kitchens[i].goatcheese + kitchens.kitchens[i].gruyere + kitchens.kitchens[i].mushrooms
                        + kitchens.kitchens[i].steak + kitchens.kitchens[i].tomato + kitchens.kitchens[i].chieflove;

            kitchenDebug.GetComponent<TextMeshPro>().text = total.ToString() + " - ingredients "
                + (kitchens.kitchens[i].waiting_pizza < 0 ? "No" : kitchens.kitchens[i].waiting_pizza.ToString()) + " pizzas in queue";
            foreach (Transform child in childs)
            {
                if (x < kitchens.kitchens[i].available_cooks)
                {
                    child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.green;
                }
                else if (x < kitchens.kitchens[i].max_cooks)
                {
                    child.transform.GetChild(0).GetComponent<MeshRenderer>().materials[0].color = Color.red;
                }
                else
                {
                    child.gameObject.SetActive(false);
                }
                x++;
            }
            _kitchenInstance.Add(obj);
        }
        updated = false;
    }
}
