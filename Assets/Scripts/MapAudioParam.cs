using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class MapAudioParam : MonoBehaviour {
    public AudioMixer masterMixer;
    //public AudioSource source;

    /*public void PlaySound() 
    {
        source.Play();
    }*/

    void SetDelay() {
        float value = transform.position.z * 50.0f;
        masterMixer.SetFloat("DelayParam", value);
    }

    private void Update()
    {
        SetDelay();
    }
}
