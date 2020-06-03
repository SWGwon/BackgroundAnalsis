#include "background.h"

using namespace std;

bool tSort(Hit Hit1, Hit Hit2)
{
    return(Hit1.GetT() < Hit2.GetT());
}

//a, b are vector
double GetAngle(float a[], float b[])
{
    float norm_a[3];
    float norm_b[3];
    
    //normalize
    norm_a[0] = a[0]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));
    norm_a[1] = a[1]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));
    norm_a[2] = a[2]/(pow(pow(a[0],2)+pow(a[1],2)+pow(a[2],2),0.5));

    norm_b[0] = b[0]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));
    norm_b[1] = b[1]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));
    norm_b[2] = b[2]/(pow(pow(b[0],2)+pow(b[1],2)+pow(b[2],2),0.5));

    //get angle
    double angle = TMath::ACos(norm_a[0]*norm_b[0]+ norm_a[1]*norm_b[1]+norm_a[2]*norm_b[2])/TMath::Pi();
    if(angle >= 0 && angle <= 1)
        return angle;
    else
        return -1000;
}

//a, b are vector
double GetDistance(float a[], Hit hit)
{
    return pow(pow(a[0]-hit.GetX(),2)+pow(a[1]-hit.GetY(),2)+pow(a[2]-hit.GetZ(),2),0.5);
}
