using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour {
    public Vector3 to_go;
    public Dam dam;
    public List<int> res = new List<int> { 0, 0, 0, 0, 0, 0 };

    // Use this for initialization
    void Start () {
        to_go = this.transform.position;
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 pos = transform.position;
        if (pos.y < -5)
        {
            if (pos.x > dam.size.x)
            {
                pos.x -= dam.size.x;
                to_go.x -= (dam.size.x + 1);
            }
            else if (pos.x < 0)
            {
                pos.x += dam.size.x;
                to_go.x += (dam.size.x + 1);
            }
            else if (pos.z > dam.size.y)
            {
                pos.z -= dam.size.y;
                to_go.z -= (dam.size.y + 1);
            }
            else if (pos.z < 0)
            {
                pos.z += dam.size.y;
                to_go.z += (dam.size.y + 1);
            }
            pos.y = 5;
            transform.position = pos;
        }
        float dist = Mathf.Sqrt(Mathf.Pow(to_go.x - pos.x, 2) + Mathf.Pow(to_go.z - pos.z, 2));
        if (dist > 0.2f)
        {
            Vector3 move = new Vector3(0, 0, 0);
            move.x = ((to_go.x - pos.x) / dist);
            move.z = ((to_go.z - pos.z) / dist);
            float a = Mathf.Acos(move.z) * 180 / Mathf.PI;
            if (Mathf.Asin(move.x) < 0)
            {
                a = -a;
            }
            transform.localEulerAngles = new Vector3(0, a, 0);
            move.x *= 0.01f;
            move.z *= 0.01f;
            transform.position += move;
            Animation anim;
            anim = GetComponent<Animation>();
            if (!anim.IsPlaying("Walk"))
            {
                anim.Play("Walk");
            }
        }
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
