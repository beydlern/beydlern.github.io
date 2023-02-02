using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Dropper : MonoBehaviour
{
    
    bool dropSentinel = true;
    [SerializeField] float timeToWait = 5f;
    MeshRenderer meshrenderer;
    Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        meshrenderer = GetComponent<MeshRenderer>();
        rigidbody = GetComponent<Rigidbody>();

        meshrenderer.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        Drop();
    }

    void Drop()
    {
        if (Time.time > timeToWait && dropSentinel)
        {
            Debug.Log("Dropping Object!");
            meshrenderer.enabled = true;
            rigidbody.useGravity = true;
            dropSentinel = false;
        }
    }
}
