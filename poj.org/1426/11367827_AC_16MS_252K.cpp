#include<iostream>
using namespace std;
const int Max = 201;
 
struct node{
    int num;
    int rem;
    node *pre;
};   //  队列中没个结点的结构。
 
void print(node n){
    if(n.pre == NULL)
        cout << n.num;
    else{
         print(*n.pre);
         cout << n.num;
    }
}    //  递归构造出答案。
 
int main(){
    node queue[Max];
    bool remain[Max];
    int n;
    while(cin >> n && n != 0){
        memset(remain, false, sizeof(remain));
        remain[1] = true;
        queue[1].num = 1;
        queue[1].rem = 1;
        queue[1].pre = NULL; 
        int head = 1, tail = 2;   //  队列第一个结点，队列初始化。

        bool flag = false;    //  找到答案的标志。
        node ans;    // 目标结点。
        while(!flag){
            int count = tail - head;
            while(count --){
                node now;
                for(int i = 0; i <= 1; i ++){
                    now.num = i;
                    now.rem = (queue[head].rem * 10 + i) % n;
                    now.pre = &queue[head];
                    if(now.rem == 0){
                        ans = now;
                        flag = true;
                    }
                    else if(!remain[now.rem]){
                        remain[now.rem] = true;
                        queue[tail++] = now;    // 注意要入列，一开始忘了wa了很久。
                    }
                }
                head ++;
            }
        }
        print(ans);
        cout << endl;
    }
    return 0;
}