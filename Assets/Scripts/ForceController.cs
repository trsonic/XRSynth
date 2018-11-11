using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ForceController : MonoBehaviour {

    Rigidbody rb;
    public float thrust;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void OnMouseDown() {
        rb.AddForce(0, thrust, thrust, ForceMode.Impulse);
    }
}
