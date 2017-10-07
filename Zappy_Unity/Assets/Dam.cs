using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Dam : MonoBehaviour {
    public Vector2 size = new Vector2(0, 0);
    public GameObject tilePrefab;
    public Texture tex;
    public Renderer rend;
    public List<GameObject> tiles;
    public bool is_display = false;

    // Use this for initialization
    void Start () {
        tiles = new List<GameObject>();
	}
	
	// Update is called once per frame
	void Update () {
        if (!is_display && size.x != 0 && size.y != 0)
        {
            is_display = true;
            int id = 0;
            for (int i = 1; i <= size.x; i++)
            {
                for (int j = 1; j <= size.y; j++)
                {
                    if (id >= tiles.Count)
                    {
                        tiles.Add((GameObject)Instantiate(tilePrefab));
                        Tile tile = tiles[tiles.Count - 1].AddComponent<Tile>();
                        tiles[tiles.Count - 1].transform.parent = transform;
                        tiles[tiles.Count - 1].name = "Tile" + id;
                        tile.coordinates = new Vector2(i, j);
                        tiles[tiles.Count - 1].transform.position = new Vector3(i, 0, j);
                        if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                        {
                            tex = (Texture)Resources.Load("tronTile");
                        }
                        else
                        {
                            tex = (Texture)Resources.Load("tronWire");
                        }
                        MeshRenderer tileObjectMeshRenderer = tiles[tiles.Count - 1].GetComponent<MeshRenderer>();
                        Material tileObjectMaterial = new Material(Shader.Find("Standard"));
                        tileObjectMaterial.mainTexture = tex;
                        tileObjectMeshRenderer.material = tileObjectMaterial;
                    }
                    id++;
                }
            }
            int save = id;
            while (id < tiles.Count)
            {
                Destroy(tiles[id]);
                if (id == tiles.Count - 1)
                {
                    tiles.RemoveRange(save, id - save + 1);
                }
                id += 1;
            }
        }
    }
}
