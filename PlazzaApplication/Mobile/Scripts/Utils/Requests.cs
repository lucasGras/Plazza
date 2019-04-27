using System.Collections;
using System.Collections.Generic;
using Kitchens;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.UI;

public class Requests : MonoBehaviour
{
    public GameObject connectionState;
    public GameObject requestState;
    private string urlToRequest = "https://lucas.adrien2431.ovh";

    void Start()
    {
        if (Application.internetReachability == NetworkReachability.NotReachable)
        {
            return;
        }
        StartCoroutine(SendBatch());
    }

    public void SendNewOrder()
    {
        string order = GameObject.Find("inputText").GetComponent<Text>().text;
        string json = "[\"" + order + "\"]";

        StartCoroutine(SendRequest(json));
    }

    private void SendKitchenListToManager(string json)
    {
        if (json.Length != 0)
        {
            var list = KitchenList.FromJson(json);

            GameObject.Find("MANAGER").GetComponent<Manager>().kitchens = list;
            GameObject.Find("MANAGER").GetComponent<Manager>().updated = true;
        }
    }
    
    private IEnumerator SendBatch()
    {
        while (true)
        {
            using (UnityWebRequest webRequest = UnityWebRequest.Get(urlToRequest + "/status/shared"))
            {
                yield return webRequest.SendWebRequest();

                if (webRequest.isNetworkError) {
                    connectionState.GetComponent<Image>().color = Color.red;
                }
                else {
                    connectionState.GetComponent<Image>().color = Color.green;
                    SendKitchenListToManager(webRequest.downloadHandler.text);
                }
            }
            yield return new WaitForSeconds(1.5f);
        }
    }

    private IEnumerator SendRequest(string json)
    {
        string url = urlToRequest + "/refresh/orders?json=" + json;

        using (UnityWebRequest webRequest = UnityWebRequest.Get(url))
        {
            yield return webRequest.SendWebRequest();

            if (webRequest.isNetworkError) {
                requestState.GetComponent<Image>().color = Color.red;
            }
            else {
                requestState.GetComponent<Image>().color = Color.green;
            }
        }
    }
}
