using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

    public float Speed = 10.0f;
    public float SpeedH = 6.0f;
    public float SpeedV = 6.0f;

    private CharacterController _controller;
    private float yawn;
    private float pitch;

    void Start()
    {
        _controller = GetComponent<CharacterController>();
        yawn = 0.0f;
        pitch = 0.0f;
    }

    void Update()
    {

        yawn += SpeedH * Input.GetAxis("Mouse X");
        pitch -= SpeedV * Input.GetAxis("Mouse Y");

        transform.eulerAngles = new Vector3(pitch, yawn, 0.0f);

        Vector3 move;
        move = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));

        _controller.Move(move * Time.deltaTime * Speed);

    }

}
