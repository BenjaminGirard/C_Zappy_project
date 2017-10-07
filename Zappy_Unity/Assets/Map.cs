using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Map : MonoBehaviour {

    public Dam dam;
    public ReadLog rlog;

    // Use this for initialization
    void Start () {
        GameObject damObject = new GameObject("Dam");
        damObject.transform.parent = transform;
        dam = damObject.AddComponent<Dam>();
        dam.tilePrefab = (GameObject)Resources.Load("Cube");
        GameObject rlogObject = new GameObject("ReadLog");
        rlogObject.transform.parent = transform;
        rlog = rlogObject.AddComponent<ReadLog>();
        rlog.dam = dam;
        rlog.prefabs.Add((GameObject)Resources.Load("Robot"));
        rlog.prefabs.Add((GameObject)Resources.Load("Battery"));
        rlog.prefabs.Add((GameObject)Resources.Load("Linemate"));
        rlog.prefabs.Add((GameObject)Resources.Load("Deraumere"));
        rlog.prefabs.Add((GameObject)Resources.Load("Sibur"));
        rlog.prefabs.Add((GameObject)Resources.Load("Mendiane"));
        rlog.prefabs.Add((GameObject)Resources.Load("Phiras"));
        rlog.prefabs.Add((GameObject)Resources.Load("Thystame"));
    }

    // Update is called once per frame
    void Update () {
		
	}
}
