using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spinner : MonoBehaviour
{

    float xRotateSpeed = 0f;
    float yRotateSpeed = 200f;
    float zRotateSpeed = 0f;

    void Update()
    {
        Spin();
    }

    void Spin()
    {
        this.transform.Rotate(xRotateSpeed * Time.deltaTime, yRotateSpeed * Time.deltaTime, zRotateSpeed * Time.deltaTime);
    }
}
