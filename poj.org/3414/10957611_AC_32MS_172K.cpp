#include <iostream>  
#include <cstdio>  
#include <string>  
#include <cstring>  
#include <algorithm>  
#include <vector>  
#include <queue>  
#include <stack>  
#include <set>  
  
#define M 105  
  
using namespace std;  
  
struct Node {  
    int x;  
    int y;  
    int step;  
      
    Node(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}  
};  
  
struct Path {  
    int method;  
    int pre;  
      
    Path(int _m, int _p) : method(_m), pre(_p) {}  
};  
int a, b, c;  
bool visited[M][M];  
queue<struct Node> que;  
vector<struct Path> vec;  
vector<int> path;  
  
int bfs()  
{  
    memset(visited, false, sizeof(visited));  
    vec.clear();  
    while(!que.empty())  
        que.pop();  
      
    que.push(Node(0, 0, 0));  
    visited[0][0] = true;  
    vec.push_back(Path(-1, -1));  
    int index = -1;  
    while(!que.empty()) {  
        index++;  
        struct Node tmp = que.front();  
        que.pop();  
        int tmpx, tmpy;  
          
        tmpx = a;  
        tmpy = tmp.y;  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(1, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
          
        tmpx = tmp.x;  
        tmpy = b;  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(2, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
          
        if(tmp.x  + tmp.y <= b && tmp.x > 0) {  
            tmpx = 0;  
            tmpy = tmp.x + tmp.y;  
        }  
        else if(tmp.x > 0){  
            tmpx = tmp.x + tmp.y - b;  
            tmpy = b;  
        }  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(3, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
          
        if(tmp.x + tmp.y <= a && tmp.y > 0) {  
            tmpx = tmp.x + tmp.y;  
            tmpy = 0;  
        }  
        else if(tmp.y > 0){  
            tmpx = a;  
            tmpy = tmp.x + tmp.y - a;  
        }  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(4, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
          
        tmpx = 0;  
        tmpy = tmp.y;  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(5, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
          
        tmpx = tmp.x;  
        tmpy = 0;  
        if(!visited[tmpx][tmpy]) {  
            vec.push_back(Path(6, index));  
            visited[tmpx][tmpy] = true;  
            if(tmpx == c || tmpy == c)  
                return tmp.step + 1;  
            else  
                que.push(Node(tmpx, tmpy, tmp.step + 1));  
        }  
    }  
      
    return -1;  
}  
  
int main()  
{  
    //freopen("data.in", "rb", stdin);  
    while(scanf("%d%d%d", &a, &b, &c) != EOF) {  
        int res = bfs();  
        if(res == -1)  
            printf("impossible\n");  
        else {  
            printf("%d\n", res);  
            path.clear();  
            int i = vec.size() - 1;  
            while(vec[i].pre != -1) {  
                path.push_back(vec[i].method);  
                i = vec[i].pre;  
            }  
            for(vector<int>::reverse_iterator it = path.rbegin(); it != path.rend(); it++) {  
                switch(*it) {  
                    case 1: printf("FILL(1)\n");  
                            break;  
                    case 2: printf("FILL(2)\n");  
                            break;  
                    case 3: printf("POUR(1,2)\n");  
                            break;  
                    case 4: printf("POUR(2,1)\n");  
                            break;  
                    case 5: printf("DROP(1)\n");  
                            break;  
                    case 6: printf("DROP(2)\n");  
                            break;  
                }  
            }  
        }  
    }  
      
    return 0;  
}  