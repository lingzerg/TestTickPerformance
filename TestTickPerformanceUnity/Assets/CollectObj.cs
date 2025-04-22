using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollectObj : MonoBehaviour
{
    public void MyUpdate()
    {
        transform.position = new Vector3(
            Random.Range(0.0f, 5000.0f),
            Random.Range(0.0f, 5000.0f),
            Random.Range(0.0f, 5000.0f)
        );
    }
}
