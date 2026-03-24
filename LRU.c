#include<stdio.h>
#include<stdlib.h>
#define MAX 50

int main(){
    int f,p;
    int pages[MAX],frame[MAX],time[MAX];
    int faults = 0,counter = 0;
    printf("Enter number of pages: ");
    scanf("%d",&p);
    for(int i=0;i<p;i++)scanf("%d",&pages[i]);
    printf("Enter the number of frames: ");
    scanf("%d",&f);

    for(int i=0;i<f;i++){
        frame[i]=-1;
        time[i]=0;
    }

    for(int i=0;i<p;i++){
        int hit = -1;
        counter++;
        for(int j = 0;j<f;j++){
            if(frame[j]== pages[i]){
                hit = j;
                break;
            }
        }
        if(hit!=-1){
            time[hit]=counter;
        }else{
            int pos = 0;
            for(int j=1;j<f;j++){
                if(time[j]<time[pos])pos=j;
            frame[pos] = pages[i];
            time[pos] = counter;
            faults++;
            }
        }

    }
}