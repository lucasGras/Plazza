using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.Characters.FirstPerson;

public class VRInputs : MonoBehaviour
{
    void Update()
    {
        OVRInput.Update();
        if (Input.GetKeyDown(0))
        {
            this.gameObject.transform.Translate(Vector3.forward * 0.2f);
        }
    }
}
