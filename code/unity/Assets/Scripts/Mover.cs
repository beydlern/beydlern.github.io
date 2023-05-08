using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mover : MonoBehaviour
{
    float xValue;
    float zValue;
    [SerializeField] float moveSpeed = 5f;

    // Start is called before the first frame update
    void Start()
    {
        PrintInstruction();
        transform.Translate(0f,0.25f,0f);
    }

    // Update is called once per frame
    void Update()
    {
        MovePlayer();
    }

    void PrintInstruction() 
    {
        Debug.Log("Welcome to The Game.");
    }

    void MovePlayer()
    {
        xValue = Input.GetAxis("Horizontal") * Time.deltaTime * moveSpeed;
        zValue = Input.GetAxis("Vertical") * Time.deltaTime * moveSpeed;
        transform.Translate(xValue, 0f, zValue);
    }
}
