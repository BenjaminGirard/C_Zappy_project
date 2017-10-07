using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Sound : MonoBehaviour
{
    private AudioSource sound;
    private Object[] myMusic; // declare this as Object array
    private int i = 0;

    void Awake()
    {
        sound = GetComponent<AudioSource>();
        myMusic = Resources.LoadAll("Music", typeof(AudioClip));
        sound.clip = myMusic[0] as AudioClip;
    }

    void Start()
    {
        sound.Play();
    }

    // Update is called once per frame
    void Update()
    {
        if (!sound.isPlaying)
            playRandomMusic();
    }

    void playRandomMusic()
    {
        i = (i + 1) % myMusic.Length;
        sound.clip = myMusic[i] as AudioClip;
        sound.Play();
    }
}