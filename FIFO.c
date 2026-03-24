#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define MAX_FR 10
int main(){
    int p,f,faults=0;
    int pages[MAX],frames[MAX_FR];
    printf("Enter the number of pages: ");
    scanf("%d",&p);
    printf("Enter the page string: ");
    for(int i=0;i<p;i++){
        scanf("%d ",&pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d",&f);

    for(int i=0;i<f;i++)frames[i]=-1;
    
    int pointer = 0;
    for(int i=0;i<p;i++){
        int hit = 0;
        for(int j=0;j<f;j++){
                if(frames[j]==pages[i]){
                    hit = 1;
                    break;
                }
        }
        if(!hit){
            frames[pointer] = pages[i];
            pointer = (pointer+1)%f;
            faults++;
        }
    }
    
}
