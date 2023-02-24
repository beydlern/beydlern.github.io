using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Scorer : MonoBehaviour
{
    int bumpCount = 0;

    private void OnCollisionEnter(Collision other) {
        if (other.collider.tag == "Untouched") 
        {
            bumpCount++;
            Debug.Log("Bumped: " + bumpCount);
        }
    }
}
