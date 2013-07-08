//
//#include <iostream>
//#include <algorithm>
//#include <deque>
//using namespace std;
//
//
//struct ST {
//    int state, step;
//};
//
//int vis[1000000000];
//strrev
//
//int main() {
//
//    return 0;
//}

#include<iostream>
#include<cstring>
#include<cassert>
#define DEST 46233    //The sequence num of "123456780",the destination
using namespace std;
struct Result{
    char status[10];
    short xPos;      //Current position of x
    char move[50];   //record the current searching record! Important
};
Result queue1[25000] = {0},*p1 = queue1,*q1 = queue1 + 1;
Result queue2[25000] = {{"123456780",8,"\0"}},*p2 = queue2,*q2 = queue2 + 1;

char Forward[50] = {0},Backward[50] = {0};
static short used[362881] = {false};    //to mark the searching sequence
//now: the position of q (q1 == queue1 + now1)
int count1 = 1,count2 = 1,now1 = 1,now2 = 1;

int SequenceNum(const Result* m){
    int big[9] = {0},sum = 0;
    for(int i = 0;i < 8;++i){
        for(int j = i + 1;j < 9;++j){
            if(m->status[i] > m->status[j])++big[8-i];
        }
    }
    int fac = 1;
    for(int i = 1;i < 9;++i){
        sum += big[i] * fac;
        fac *= i + 1;
    }
    return sum;
}

void BFS(){
    int step,pos,Snum;
    char temp;
    while(true){

        /* queue1*/

        assert(count1 < 24999);
        pos = p1->xPos;
        step = strlen(p1->move);
        //up
        if(pos > 2){
            strcpy(q1->status,p1->status);
            temp = q1->status[pos];
            q1->status[pos] = q1->status[pos - 3];
            q1->status[pos - 3] = temp;
            q1->xPos = pos - 3;
            Snum = SequenceNum(q1);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] <= 0){   
                strcpy(q1->move,p1->move);
                q1->move[step] = 'u';
                if(used[Snum] < 0){
                    strcpy(Forward,q1->move);
                    strcpy(Backward,(queue2+(-used[Snum]))->move);
                    return;
                }
                else{
                    used[Snum] = now1;   //mark a positive number
                    ++q1,++now1,++count1;
                    if(q1 == queue1 + 25000)q1 = queue1+1,now1 = 1;
                }
            }
        }

        //down
        if(pos < 6){
            strcpy(q1->status,p1->status);
            temp = q1->status[pos];
            q1->status[pos] = q1->status[pos + 3];
            q1->status[pos + 3] = temp;
            q1->xPos = pos + 3;
            Snum = SequenceNum(q1);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] <= 0){   
                strcpy(q1->move,p1->move);
                q1->move[step] = 'd';
                if(used[Snum] < 0){
                    strcpy(Forward,q1->move);
                    strcpy(Backward,(queue2+(-used[Snum]))->move);
                    return;
                }
                else{
                    used[Snum] = now1;   //mark a positive number
                    ++q1,++now1,++count1;
                    if(q1 == queue1 + 25000)q1 = queue1+1,now1 = 1;
                }
            }
        }

        //left
        if(pos%3 > 0){
            strcpy(q1->status,p1->status);
            temp = q1->status[pos];
            q1->status[pos] = q1->status[pos - 1];
            q1->status[pos - 1] = temp;
            q1->xPos = pos - 1;
            Snum = SequenceNum(q1);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] <= 0){   
                strcpy(q1->move,p1->move);
                q1->move[step] = 'l';
                if(used[Snum] < 0){
                    strcpy(Forward,q1->move);
                    strcpy(Backward,(queue2+(-used[Snum]))->move);
                    return;
                }
                else{
                    used[Snum] = now1;   //mark a positive number
                    ++q1,++now1,++count1;
                    if(q1 == queue1 + 25000)q1 = queue1+1,now1 = 1;
                }
            }
        }

        //right
        if(pos%3 < 2){
            strcpy(q1->status,p1->status);
            temp = q1->status[pos];
            q1->status[pos] = q1->status[pos + 1];
            q1->status[pos + 1] = temp;
            q1->xPos = pos + 1;
            Snum = SequenceNum(q1);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] <= 0){   
                strcpy(q1->move,p1->move);
                q1->move[step] = 'r';
                if(used[Snum] < 0){
                    strcpy(Forward,q1->move);
                    strcpy(Backward,(queue2+(-used[Snum]))->move);
                    return;
                }
                else{
                    used[Snum] = now1;   //mark a positive number
                    ++q1,++now1,++count1;
                    if(q1 == queue1 + 25000)q1 = queue1+1,now1 = 1;
                }
            }
        }
        //p1 is over
        if(++p1 == queue1 + 25000)p1 = queue1+1;
        --count1;

        /* queue2 */

        assert(count2 < 24999);
        pos = p2->xPos;
        step = strlen(p2->move);
        //up
        if(pos > 2){
            strcpy(q2->status,p2->status);
            temp = q2->status[pos];
            q2->status[pos] = q2->status[pos - 3];
            q2->status[pos - 3] = temp;
            q2->xPos = pos - 3;
            Snum = SequenceNum(q2);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] >= 0){   
                strcpy(q2->move,p2->move);
                q2->move[step] = 'd';  //searching backward,the move is the opposite
                if(used[Snum] > 0){
                    strcpy(Forward,(queue1 + used[Snum])->move);
                    strcpy(Backward,q2->move);
                    return;
                }
                else{
                    used[Snum] = -now2;   //mark a negative number
                    ++q2,++now2,++count2;
                    if(q2 == queue2 + 25000)q2 = queue2+1,now2 = 1;
                }
            }
        }

        //down
        if(pos < 6){
            strcpy(q2->status,p2->status);
            temp = q2->status[pos];
            q2->status[pos] = q2->status[pos + 3];
            q2->status[pos + 3] = temp;
            q2->xPos = pos + 3;
            Snum = SequenceNum(q2);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] >= 0){   
                strcpy(q2->move,p2->move);
                q2->move[step] = 'u';
                if(used[Snum] > 0){
                    strcpy(Forward,(queue1 + used[Snum])->move);
                    strcpy(Backward,q2->move);
                    return;
                }
                else{
                    used[Snum] = -now2;   //mark a negative number
                    ++q2,++now2,++count2;
                    if(q2 == queue2 + 25000)q2 = queue2+1,now2 = 1;
                }
            }
        }

        //left
        if(pos%3 > 0){
            strcpy(q2->status,p2->status);
            temp = q2->status[pos];
            q2->status[pos] = q2->status[pos - 1];
            q2->status[pos - 1] = temp;
            q2->xPos = pos - 1;
            Snum = SequenceNum(q2);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] >= 0){   
                strcpy(q2->move,p2->move);
                q2->move[step] = 'r';
                if(used[Snum] > 0){
                    strcpy(Forward,(queue1+used[Snum])->move); //bug1 detected:q1->queue1
                    strcpy(Backward,q2->move);
                    return;
                }
                else{
                    used[Snum] = -now2;   //mark a negative number
                    ++q2,++now2,++count2;
                    if(q2 == queue2 + 25000)q2 = queue2+1,now2 = 1;
                }
            }
        }

        //right
        if(pos%3 < 2){
            strcpy(q2->status,p2->status);
            temp = q2->status[pos];
            q2->status[pos] = q2->status[pos + 1];
            q2->status[pos + 1] = temp;
            q2->xPos = pos + 1;
            Snum = SequenceNum(q2);
            //queue1 is positive queue2 is negative 0 means unsearched
            if(used[Snum] >= 0){   
                strcpy(q2->move,p2->move);
                q2->move[step] = 'l';
                if(used[Snum] > 0){
                    strcpy(Forward,(queue1+used[Snum])->move);
                    strcpy(Backward,q2->move);
                    return;
                }
                else {
                    used[Snum] = -now2;   //bug2 detected: negative number
                    ++q2,++now2,++count2;
                    if(q2 == queue2 + 25000)q2 = queue2+1,now2 = 1;
                }
            }
        }
        //p1 is over
        if(++p2 == queue2 + 25000)p2 = queue2+1;
        --count2;
    }
}

int main(){
    /* Get the original board */
    for(int i = 0;i < 9;++i){
        cin>>p1->status[i];
        if(p1->status[i] == 'x'){
            p1->status[i] = '0';
            p1->xPos = i;
        }
    }
    int reversepair = 0;
    for(int i = 0;i < 8;++i){
        for(int j = i + 1;j < 9;++j){
            if(p1->status[i] == '0' || p1->status[j] == '0')continue;
            if(p1->status[i] < p1->status[j])++reversepair;
        }
    }
    if(reversepair%2){
        printf("unsolvable!\n");
        system("PAUSE");
        return 0;
    }
    if(strcmp(p1->status,"123456780") == 0){
        printf("0\n");
        return 0;
    }
    used[SequenceNum(p1)] = 30000;  //mark first
    used[DEST] = -30000;
    memset(p1->move,0,100*sizeof(char));
    /* Search and print result */
    BFS();
    char temp[50];
    int l = strlen(Backward);
    for (int i = 0; i < l; i++)
        temp[l-i-1] = Backward[i];
    temp[l] = 0;
    printf("%s%s\n",Forward,temp);
    cin.get();
    cin.get();
    return 0;
}