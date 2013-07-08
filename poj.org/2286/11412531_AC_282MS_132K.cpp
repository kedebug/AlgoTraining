#include<stdio.h>
int ff[8][7]={0,2,6,11,15,20,22,
            1,3,8,12,17,21,23,
            10,9,8,7,6,5,4,
            19,18,17,16,15,14,13,
            23,21,17,12,8,3,1,
            22,20,15,11,6,2,0,
            13,14,15,16,17,18,19,
            4,5,6,7,8,9,10};
int aim[8]={6,7,8,11,12,15,16,17};
int rev[8]={5,4,7,6,1,0,3,2};
int map[25],ans[20],DEPTH;
int least(){
    int i,count[3]={0,0,0},ans=0;
    for(i=0;i<8;++i)++count[map[aim[i]]-1];
    for(i=0;i<3;++i)if(ans<count[i])ans=count[i];
    return 8-ans;
}
void change(int dir){
    int i,temp=map[ff[dir][0]];
    for(i=0;i<6;++i)
        map[ff[dir][i]]=map[ff[dir][i+1]];
    map[ff[dir][6]]=temp;
}
int dfs(int depth){
    int i,temp;
    for(i=0;i<8;++i){
        change(i);
        if((temp=least())==0){
            ans[depth]=i;
            return depth+1;
        }
        if(depth+temp<DEPTH){
            ans[depth]=i;
            if(dfs(depth+1))return depth+1;
        }
        change(rev[i]);
    }
    return 0;
}
int main(){
    int i;
    while(scanf("%d",&map[0]),map[0]){
        for(i=1;i<24;++i)scanf("%d",&map[i]);
        if(least()==0){
            puts("No moves needed");
            printf("%d\n",map[6]);
            continue;
        }
        for(DEPTH=1;!dfs(0);++DEPTH);
        for(i=0;i<DEPTH;++i)printf("%c",ans[i]+'A');printf("\n");
        printf("%d\n",map[6]);
    }
    return 0;
}