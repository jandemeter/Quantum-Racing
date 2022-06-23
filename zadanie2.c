#include <stdio.h>
#include <unistd.h>
#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora
void srnd(int seed) { SEED = seed; }

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}


//hod kockami
int kr1(){
    int r1 = rnd(1,6);
    return r1;
}

int kr2(){
    int r2 = rnd(1,6);
    return r2;
}


int max(int a, int b){
    if (a > b){
        return a;
    }
    else if (a < b){
        return b;
    }
    else{
        return a;
    }
}

int main(){

    int s,t,n,enter,exit;
    scanf("%d""%d""%d",&s,&t,&n);
    if (s<=0 || n<10 || n>100 || (t*2)>(n/2)) {
        return 1;
    }

    srnd(s);


    int visits[n];
    for(int i=0;i<n;i++) {
        visits[i] = 0;
    }
    int tunel[t][2];
    if (t>0) {

        //chybove situacie 
        for (int i = 0; i < t; i++) {
            scanf("%d %d", &enter, &exit);
            if (enter == exit || enter < 1 || exit < 1 || enter > n - 1 || exit >= n - 1) {
                return 2;
            }
            tunel[i][0] = enter;
            tunel[i][1] = exit;
        }
        for(int i = 0; i < t; i++){
            for(int j = 0; j <t;j++){
                if((tunel[i][0]==tunel[j][0]) && (i!=j)){
                    return 2;
                }
            }
        }
        for(int i = 0; i < t; i++){
            for(int j = 0; j <t;j++){
                if(tunel[i][0]==tunel[j][1]){
                    return 2;
                }
            }
        }

        //vypise prvotne tunely
        printf("TUNNELS:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < t; j++) {
                if((tunel[j][0])==i)
                    printf(" [%d,%d]", tunel[j][0], tunel[j][1]);
            }
        }
    }
    else{
        printf("TUNNELS:");
    }
    int player1 = -1;
    int player2 = -1;
    int round = 0;
    int special_case;
    int c = tunel[t-1][1];

    //cyklus dokym niekto neprejde cielom 
    //prv sa skontoroluju specialne pripady, potom sa hrac pohne, a vypise sa dany tah
    //kod je napisane osobitne pre hraca1 a pre hraca2
    while(1==1){

        tunel[t-1][1] = c;
        special_case = 0;
        int r11 = kr1();
        int r12 = kr2();
        int player1before = player1;
        if(player1 == -1 && (r11+r12)>7){
            player1 =  (r11+r12)-7;
        }
        else if(player1>0 && player2>0 && player1>player2 && r11==1 && r12==1){
            int help = player1;
            player1 = player2;
            player2 = help;
            special_case++;
            visits[player2]++;
        }
        else if(player1>0 && player2>0 && player1<player2 && r11==6 && r12==6){
            int help = player1;
            player1 = player2;
            player2 = help;
            special_case++;
            visits[player2]++;
        }
        else if (player1>0){
            player1 = player1 + max(r11,r12);
        }
        if(t>0 && player1>0){
            for(int i=0;i<t;i++){
                if((tunel[i][0]) == player1){
                    player1 = tunel[i][1];
                    special_case = special_case + 5;
                }
            }
        }



        if(player1==player2 && player1>0 && player2>0){
            player2 = -1;
            special_case = special_case + 3;
        }

        visits[player1]++;
        round++;
        printf("\n[%d,1]",round);
        printf(" [%d]",player1before);
        printf(" [%d,%d]",r11,r12);
        printf(" [%d]",player1);
        if (special_case == 1){
            printf(" S");
        }
        if (special_case == 3){
            printf(" E");
        }
        if (special_case == 5){
            printf(" T");
        }
        if (special_case == 8){
            printf(" T E");
        }
        if(player1>=n){
            printf("\nWINNER: 1");
            break;
        }


        int special_case = 0;
        int player2before = player2;
        int r21 = kr1();
        int r22 = kr2();
        if(player2 == -1 && (r21+r22)>7){
            player2 =  (r21+r22)-7;
        }
        else if(player1>0 && player2>0 && player1<player2 && r21==1 && r22==1){
            int help = player1;
            player1 = player2;
            player2 = help;
            special_case++;
            visits[player1]++;
        }
        else if(player1>0 && player2>0 && player1>player2 && r21==6 && r22==6){
            int help = player1;
            player1 = player2;
            player2 = help;
            special_case++;
            visits[player1]++;
        }
        else if (player2>0){
            player2 = player2 + max(r21,r22);
        }
        if(t>0 && player2>0){
            for(int i=0;i<t;i++){
                if((tunel[i][0]) == player2){
                    player2 = tunel[i][1];
                    special_case = special_case + 5;
                }
            }
        }


        if((player2==player1 && player1>0 && player2>0)){
            player1 = -1;
            special_case = special_case + 3;
        }

        visits[player2]++;
        round++;
        printf("\n[%d,2]",round);
        printf(" [%d]",player2before);
        printf(" [%d,%d]",r21,r22);
        printf(" [%d]",player2);
        if (special_case == 1){
            printf(" S");
        }
        if (special_case == 3){
            printf(" E");
        }
        if (special_case == 5){
            printf(" T");
        }
        if (special_case == 8){
            printf(" T E");
        }


        if(player2>=n){
            printf("\nWINNER: 2");
            break;
        }

    }
    //nakoniec vypis toho kolkokrat bolo navstevene policko na hracej ploche 
    printf("\nVISITS:");
    for(int i=0; i<n; i++){
        printf(" %d",visits[i]);
    }

    
    return 0;
}

