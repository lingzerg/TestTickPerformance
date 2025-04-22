using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UpdataObj : MonoBehaviour
{
    void Update()
    {
        transform.position = new Vector3(
            Random.Range(0.0f, 500.0f),
            Random.Range(0.0f, 500.0f),
            Random.Range(0.0f, 500.0f)
        );
    }
}
