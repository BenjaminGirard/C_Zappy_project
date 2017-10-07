using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour {

    public Vector2 coordinates;
    public Color color;
    public Tile diagonal1;
    public List<int> res = new List<int> { 0, 0, 0, 0, 0, 0 };
    // Use this for initialization

    void Start ()
    {
    }
	
	// Update is called once per frame
	void Update ()
    {
	}

    void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(0))
        {
            GameObject cam = GameObject.Find("Main Camera");
            cam.GetComponent<Cam>().dispText = "Linemate : " + res[0] + "\n" + "Deraumere : " + res[1] + "\n" + "Mendiane : " + res[2] + "\n" + "Phiras : " + res[3] + "\n" + "Sibur : " + res[4] + "\n" + "Thystame : " + res[5] + "\n";
        }
    }
}