#include <stdio.h>
#define MAX 50

int main() {
    int pages[MAX], frame[MAX];
    int n, f, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++) frame[i] = -1;

    for(int i=0;i<n;i++){
        int hit = 0;
        for(int j=0;j<f;j++){
            if(frame[j]==pages[i]){
                hit=1;
                break;
            }
        }

        if(!hit){
            int pos = 0,farthest = 0;
            for(int j=0;j<f;j++){
                int k;
                for(k=i+1;k<n;k++)
                    if(frame[j]==pages[k])break;
                if(k>farthest){farthest = k; pos = j;}
                if(k == n){
                    pos = j;
                    break;
                }
            }
            frame[pos] = pages[i];
            faults++;
        }
    }
}