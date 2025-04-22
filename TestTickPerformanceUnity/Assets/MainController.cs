using System;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using Random = UnityEngine.Random;

public class MainController : MonoBehaviour
{
    private List<GameObject> UpdataObjList = new List<GameObject>();
    private List<CollectObj> CollectObjList = new List<CollectObj>();

    public TextMeshProUGUI uitxt;

    public GameObject UpdataObj;
    public GameObject CollectObj;
    
    void Update()
    {
        uitxt.text = "Frame Time " + Time.deltaTime*1000 + "\n";
        uitxt.text += "Updata Obj Num = " + UpdataObjList.Count+ "\n";
        uitxt.text += "Collect Obj Num = " +CollectObjList.Count+ "\n";

        for (int i = 0; i < CollectObjList.Count; i++)
        {
            CollectObjList[i].MyUpdate();
        }
        
    }

    public void CreateUpdataObj()
    {
        Debug.Log("CreateUpdataObj");
        for (int i = 0; i < 1000; i++)
        {
            GameObject obj = Instantiate(UpdataObj);
            if (obj)
            {
                UpdataObjList.Add(obj);
            }
        }
    }
    
    public void CreateCollectObj()
    {
        Debug.Log("CreateCollectObj");
        for (int i = 0; i < 1000; i++)
        {
            CollectObj obj = Instantiate(CollectObj).GetComponent<CollectObj>();
            
            if (obj)
            {
                CollectObjList.Add(obj);
            }
        }
    }

    public void Clear()
    {
        foreach (var item in UpdataObjList)
        {
            DestroyImmediate(item);
        }
        UpdataObjList.Clear();
        foreach (var item in CollectObjList)
        {
            DestroyImmediate(item.gameObject);
        }
        
        CollectObjList.Clear();
    }
}
