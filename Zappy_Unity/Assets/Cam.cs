using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cam : MonoBehaviour {
    public float a;
    public float incl;
    public float dist;
    public ReadLog Rdlog;
    public string dispText = "";

    // Use this for initialization
    void Start () {
        dist = 8f;
        a = 0;
        incl = 30;
        Rdlog = GameObject.Find("Directional Light").GetComponent<Map>().rlog;
    }

    // Update is called once per frame
    void Update () {
        Vector2 map_size = Rdlog.size;
        if (Input.GetKey(KeyCode.RightArrow))
        {
            a -= 1;
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            a += 1;
        }
        else if (Input.GetKey(KeyCode.UpArrow) && dist > 2)
        {
            dist -= 0.1f;
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            dist += 0.1f;
        }
        else if (Input.GetKey(KeyCode.Z) && incl < 80)
        {
            incl += 1;
        }
        else if (Input.GetKey(KeyCode.S) && incl > -40)
        {
            incl -= 1;
        }
        else if (Input.GetKey(KeyCode.Escape))
        {
            dispText = "";
        }
        Vector3 pos = this.transform.position;
        this.transform.localEulerAngles = new Vector3(incl, a, 0);
        this.transform.position = new Vector3(map_size.x / 2 + Mathf.Sin(-a * Mathf.PI / 180f) * dist, dist / 1.6f, map_size.y / 2 - Mathf.Cos(-a * Mathf.PI / 180f) * dist);
    }

    void OnGUI()
    {
        GUIContent cont = new GUIContent();
        cont.image = (Texture2D)Resources.Load("fontUi");
        cont.text = dispText;
        GUIStyle styl = new GUIStyle();
        styl.fontSize = 40;
        styl.normal.textColor = Color.red;
        GUI.Button(new Rect(160, 200, 100, 20), cont, styl);
    }
}