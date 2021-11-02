#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

    /*
    /=<
    (   /===&             _
    )   (        &        )
    (   )        )        (
    )   (        (        )
    )   )        )        &
    \===/        ^
    */

int main(){

    //interface display
    int horizontal_size=20,vertical_size=10;//set your map size
    char interface[vertical_size+3][horizontal_size+4];
    char display[vertical_size+3][horizontal_size+4];
    for(int i=0;i<vertical_size+3;i++){
        for(int j=0;j<horizontal_size+3;j++){
            interface[i][j]=' ';
        }
        interface[i][horizontal_size+3]='\n';
    }
    for(int i=0;i<horizontal_size+2;i++){
        interface[0][i]='-';
        interface[vertical_size+2][i]='-';
    }
    for(int i=1;i<vertical_size+2;i++){
        interface[i][0]='|';
        interface[i][horizontal_size+2]='|';
    }

    //create the coordinates array
    int length=5,snake[vertical_size+1][horizontal_size+1];
    for(int i=0;i<=vertical_size;i++){
        for(int j=0;j<=horizontal_size;j++){
            snake[i][j]=0;
        }
    }

    //spawn snake
    char direction='d';
    int head[2]={vertical_size/2,horizontal_size/2};
    for(int i=0;i<length;i++){
        snake[vertical_size/2][horizontal_size/2-i]=length-i;
    }
    
    int eaten=1;
    int applex=0,appley=0;
    while(1){
        
        //spawn apple
        srand((unsigned) clock());
        if(eaten==1){    
            do{
            applex=rand()%horizontal_size,appley=rand()%vertical_size;
            }while(snake[appley][applex]!=0);
            eaten=0;
        }

        //input direction
        int ms=300; //how much time the snake is going to wait for your input
        char input;
        int start=clock()*1000/CLOCKS_PER_SEC,end=start+ms;
        while(1){
            start=clock()*1000/CLOCKS_PER_SEC;
            if(kbhit()){
                input=getch();
            }
            if(start>end){
                break;
            }
        }

        //change direction, use wasd, press ESC to exit program
        switch(input){  
            case 'd': {
                if(direction!='a')direction='d';
                break;
            }
            case 'a': {
                if(direction!='d')direction='a';
                break;
            }
            case 'w': {
                if(direction!='s')direction='w';
                break;
            }
            case 's': {
                if(direction!='w')direction='s';
                break;
            }
            case 27: {
                return 0;
            }
        }

        //go direction
        switch(direction){
            case 'd': {
                head[1]+=1;
                if(head[1]==horizontal_size+1){
                    head[1]=0;
                }
                break;
            }
            case 's': {
                head[0]+=1;
                if(head[0]==vertical_size+1){
                    head[0]=0;
                }
                break;
            }
            case 'a': {
                head[1]-=1;
                if(head[1]==-1){
                    head[1]=horizontal_size;
                }
                break;
            }
            case 'w': {
                head[0]-=1;
                if(head[0]==-1){
                    head[0]=vertical_size;
                }
                break;
            }
        }

        //check conditions of location
        for(int i=0;i<=vertical_size;i++){
            for(int j=0;j<=horizontal_size;j++){
                if(head[0]==appley && head[1]==applex){
                    length++;
                    i=vertical_size+1;
                    eaten=1;
                    break;
                }
                if(snake[head[0]][head[1]]!=0){
                    puts("You lost!");
                    return 0;
                }
                else if(snake[i][j]!=0)
                    snake[i][j]-=1;
            }
        }
        snake[head[0]][head[1]]=length;

        //display snake location
        for(int i=0;i<vertical_size;i++){
            strcpy(display[i],interface[i]);
        }
        for(int i=0;i<=horizontal_size;i++){
            for(int j=0;j<=vertical_size;j++){
                if(snake[j][i]!=0){
                    display[j+1][i+1]='.';
                }
            }
        }
        display[appley+1][applex+1]='@';
        display[head[0]+1][head[1]+1]='&';
        
        
        system("cls");
        printf("\n%s",display[0]);
    }

    return 0;
}