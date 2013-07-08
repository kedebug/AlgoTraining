#include<iostream>
using namespace std;
const int Max = 363000; 


 



struct{
    char op;
    int num, id, pre;
}que[Max];
int head, tail;
int fac[9] = {1,1,2,6,24,120,720,5040,40320};
int Pow[9] = {100000000,10000000,1000000,100000,10000,1000,100,10,1};
bool vis[Max];

 

int hash(int num){      //  全排列的hash函数。
    int i, j, n[10];
    for(i = 0; i < 9; i ++){
        n[i] = num % 10;
        num /= 10;
    }
    int c, key = 0;
    for(i = 1; i < 9; i ++){
        for(c = 0, j = 0; j < i; j ++)
            if(n[j] < n[i]) c ++;
        key += c * fac[i];
    }
    return key;
}

 

void ope(int num, int a, int b, char op){      //  操作：第a个数和第b个数交换。
    int n1, n2;
    n1 = num / Pow[a] % 10;
    n2 = num / Pow[b] % 10;
    num = num - (n1-n2)*Pow[a] + (n1-n2)*Pow[b];
    int key = hash(num);
    if(!vis[key]){
        vis[key] = true;
        que[tail].op = op;
        que[tail].num = num;
        que[tail].pre = head;
        que[tail ++].id = b;
    }
}

 

void output(int k){
    if(que[k].op != 0){
        output(que[k].pre);
        cout << que[k].op;
    }
}

 

int main(){
    int i, num, id, t;
    char c;
    for(num = i = 0; i < 9; i ++){
        cin >> c;
        if(c == 'x'){
            t = 9;
            id = i;
        }else t = c - '0';
        num = 10 * num + t;
    }
    bool flag = false;
    head = 0, tail = 1;
    que[0].id = id;
    que[0].num = num;
    while(tail > head && !flag){
        int cnt = tail - head;
        while(cnt --){
            num = que[head].num;
            if(num == 123456789){
                flag = true;  break;
            }
            id = que[head].id;
            if(id % 3 != 2) ope(num, id, id + 1, 'r');
            if(id % 3 != 0) ope(num, id, id - 1, 'l');
            if(id > 2) ope(num, id, id - 3, 'u');
            if(id < 6) ope(num, id, id + 3, 'd');
            head ++;
        }
    }
    if(flag) output(head);
    else cout << "unsolvable";
    cout << endl;
    return 0;
}
