using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class CollisionManager : MonoBehaviour {

    public AudioSource sample;


    GameObject wall;

    private void Start()
    {
        //mapper = GetComponent<MapAudioParam>();
    }

    void OnCollisionEnter(Collision collision)
    {
        wall = collision.gameObject;

        if (wall.tag == "NoteOn")
        {
            sample.Play();
        }
    }
}
