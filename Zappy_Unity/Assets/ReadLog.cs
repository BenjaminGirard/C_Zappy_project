using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;
using System;

public class ReadLog : MonoBehaviour {
//    public AnimationClip walkClip;
    public delegate void Action(string[] words);
    public Vector2 size = new Vector2(0, 0);
    public List<GameObject> prefabs = new List<GameObject>();
    public Dam dam;
    public string path = "Assets/mapInfo.txt";
    public List<GameObject> elem;
    public List<Action> exec;
    public List<string> com;
    public int id = 0;

    // Use this for initialization
    void Start () {
        exec = new List<Action>();
        com = new List<string>();
        elem = new List<GameObject>();
        exec.Add(map_size);
        exec.Add(add);
        exec.Add(move);
        exec.Add(delete);
        exec.Add(take);
        exec.Add(drop);
        com.Add("map_size");
        com.Add("add");
        com.Add("move");
        com.Add("delete");
        com.Add("take");
        com.Add("drop");
    }

    // Update is called once per frame
    void Update () {
        string result;

        StreamReader reader = new StreamReader(path, Encoding.Default);

        if (reader.ReadLine() == "#")
        {
            while ((result = reader.ReadLine()) != "##")
            {
                if (result != null && result != "")
                {
                    string[] words = result.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                    int i = 0;
                    while (i < exec.Count)
                    {
                        if (words[0] == com[i])
                        {
                            exec[i](words);
                        }
                        i += 1;
                    }
                }
            }
            reader.Close();
            System.IO.File.WriteAllText(path, "@@");
        }
        else
        {
            System.Timers.Timer aTimer = new System.Timers.Timer(2000);
            aTimer.Enabled = true;
            reader.Close();
        }
    }

    void map_size(string[] words)
    {
        int x = int.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture);
        int y = int.Parse(words[2], System.Globalization.CultureInfo.InvariantCulture);
        size.x = x;
        size.y = y;
        dam.size = size;
    }

    void take(string[] words)
    {
        int i = 0;
        while (i < elem.Count && elem[i].name != words[2])
        {
            i += 1;
        }
        if (i != elem.Count)
        {
            elem[i].GetComponent<Move>().res[int.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture) - 2] += 1;
        }
    }

    void drop(string[] words)
    {
        int i = 0;
        while (i < elem.Count && elem[i].name != words[2])
        {
            i += 1;
        }
        if (i != elem.Count)
        {
            elem[i].GetComponent<Move>().res[int.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture) - 2] -= 1;
        }
    }

    void add(string[] words)
    {
        int type = int.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture);
        float nbx = float.Parse(words[2], System.Globalization.CultureInfo.InvariantCulture) + 1;
        float nbz = float.Parse(words[3], System.Globalization.CultureInfo.InvariantCulture) + 1;
        int j = 0;
        if (type == 0)
        {
            j = elem.Count;
        }
        while (j < elem.Count && (Mathf.Round(elem[j].transform.position.x) != nbx || Mathf.Round(elem[j].transform.position.z) != nbz || elem[j].GetComponent<Ressource>().type != type))
        {
            j += 1;
        }
        if (j == elem.Count)
        {
            elem.Add(Instantiate(prefabs[type], new Vector3(nbx, 1.6f, nbz), Quaternion.identity) as GameObject);
            elem[elem.Count - 1].transform.parent = transform;
            if (type == 0)
            {
                elem[elem.Count - 1].name = words[4];
            }
            else
            {
                elem[elem.Count - 1].name = words[4] + id;
                id += 1;
            }
            if (type == 0)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.2f, 0.2f, 0.2f);
                Move mv = elem[elem.Count - 1].AddComponent<Move>();
                mv.dam = dam;
                Rigidbody body = elem[elem.Count - 1].AddComponent<Rigidbody>();
                BoxCollider box = elem[elem.Count - 1].AddComponent<BoxCollider>();
                body.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ;
                Vector3 vect = box.size;
                vect.y = 5;
                box.size = vect;
                /*                elem[elem.Count - 1].AddComponent<Animation>();
                               Animation anim = elem[elem.Count - 1].GetComponent<Animation>();
                                AnimationClip clip = (AnimationClip)Resources.Load("Walk");
                                anim.AddClip(clip, "Walk");*/
            }
            else if (type == 1)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.05f, 0.05f, 0.05f);
                elem[elem.Count - 1].transform.position += new Vector3(0, -1, 0);
            }
            else if (type == 2)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.05f, 0.05f, 0.05f);
                elem[elem.Count - 1].transform.position += new Vector3(-0.2f, -1, 0);
            }
            else if (type == 3)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.05f, 0.05f, 0.05f);
                elem[elem.Count - 1].transform.position += new Vector3(0.2f, -1, 0);
                elem[elem.Count - 1].transform.Rotate(Vector3.right * 90);
            }
            else if (type == 4)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.01f, 0.01f, 0.01f);
                elem[elem.Count - 1].transform.position += new Vector3(-0.1f, -1, -0.2f);
            }
            else if (type == 5)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.01f, 0.01f, 0.01f);
                elem[elem.Count - 1].transform.position += new Vector3(0.1f, -1, -0.2f);
            }
            else if (type == 6)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.01f, 0.01f, 0.01f);
                elem[elem.Count - 1].transform.position += new Vector3(0.1f, -1, 0.2f);
            }
            else if (type == 7)
            {
                elem[elem.Count - 1].transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);
                elem[elem.Count - 1].transform.position += new Vector3(-0.1f, -1, 0.2f);
            }
            Ressource res = elem[elem.Count - 1].AddComponent<Ressource>();
            res.type = type;
/*            if (type > 1)
            {
                                j = 0;
                                while (j < dam.tiles.Count && (Mathf.Round() != Mathf.Round(dam.tiles[j].transform.position.x)
                                    || Mathf.Round(nbz) != Mathf.Round(dam.tiles[j].transform.position.z)))
                                {
                                    Console.Write((Mathf.Round(dam.tiles[j].transform.position.x)).ToString() + " ");
                                    Console.Write((Mathf.Round(dam.tiles[j].transform.position.z)).ToString());
                                    Console.WriteLine();
                                    j += 1;
                                }
                j = (int)(nbz * size.x + nbx + 0.5f);
                GameObject.Find("Main Camera").GetComponent<Cam>().dispText = (dam.tiles.Count).ToString();
                dam.tiles[j].GetComponent<Tile>().res[type - 2] += 1;
            }*/
        }
        else
        {
            elem[j].GetComponent<Ressource>().nb += 1;
        }
    }

    void move(string[] words)
    {
        float nbx = float.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture) + 1;
        float nbz = float.Parse(words[2], System.Globalization.CultureInfo.InvariantCulture) + 1;
        int j = 0;
        while (j < elem.Count && elem[j].name != words[3])
        {
            j += 1;
        }
        if (j != elem.Count)
        {
            Vector3 to_go = elem[j].GetComponent<Move>().to_go;
            float dist = Mathf.Sqrt(Mathf.Pow(to_go.x - nbx, 2) + Mathf.Pow(to_go.z - nbz, 2));
            if (dist > 2 && nbx != to_go.x)
            {
                if (nbx == 1)
                {
                    nbx += dam.size.x + 1;
                }
                else
                {
                    nbx -= (dam.size.x + 1);
                }
            }
            else if (dist > 2 && nbz != to_go.y)
            {
                if (nbz == 1)
                {
                    nbz += dam.size.y + 1;
                }
                else
                {
                    nbz -= (dam.size.y + 1);
                }
            }
            elem[j].GetComponent<Move>().to_go = new Vector3(nbx, 1, nbz);
//            elem[j].transform.position = new Vector3(nbx, 1, nbz);
  /*          if (elem[j].GetComponent<Animation>().IsPlaying("Walk") == false)
            {
                elem[j].GetComponent<Animation>().Play("Walk");
            }*/
        }
    }

    void delete(string[] words)
    {
        if (int.Parse(words[1], System.Globalization.CultureInfo.InvariantCulture) == 0)
        {
            int j = 0;
            while (j < elem.Count && elem[j].name != words[2])
            {
                j += 1;
            }
            if (j != elem.Count)
            {
                Destroy(elem[j]);
                elem.RemoveAt(j);
            }
        }
        else
        {
            int type = int.Parse(words[2], System.Globalization.CultureInfo.InvariantCulture);
            float nbx = float.Parse(words[3], System.Globalization.CultureInfo.InvariantCulture) + 1;
            float nbz = float.Parse(words[4], System.Globalization.CultureInfo.InvariantCulture) + 1;
            int j = 0;
            while (j < elem.Count && (Mathf.Round(elem[j].transform.position.x) != nbx || Mathf.Round(elem[j].transform.position.z) != nbz || elem[j].GetComponent<Ressource>().type != type))
            {
                j += 1;
            }
            if (j != elem.Count)
            {
                elem[j].GetComponent<Ressource>().nb -= 1;
                if (elem[j].GetComponent<Ressource>().nb == 0)
                {
                    Destroy(elem[j]);
                    elem.RemoveAt(j);
                }
            }
/*            if (type > 1)
            {
                j = 0;
                while (j < elem.Count && (nbx != dam.tiles[j].transform.position.x
                    || nbz != dam.tiles[j].transform.position.z))
                {
                    j += 1;
                }
                dam.tiles[j].GetComponent<Tile>().res[type - 2] -= 1;
            }*/
        }
    }
}