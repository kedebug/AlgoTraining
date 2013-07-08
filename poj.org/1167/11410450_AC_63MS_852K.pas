(*
  * 策略二：http://hi.baidu.com/lin791263068/blog/item/7c349de8f5204221279791d3.html
  *
  * 关于head 和 tail ：
  *    因为有一些车辆是同时到站的，而这里是按照时刻来进行深搜的，
  *    同一时刻可以发出很多车辆。
  *    head表示这趟线路上有一辆车的条数
  *    (注：即以该时刻的一辆车为该线路的第一辆车，此时还不知道该线路
  *    是否只有这一辆车，需按后面的搜索而定，故需tail)，
  *    tail表示确定为一条线路的条数（即后续的搜索为原来的head[i]后加了一辆车，
  *    这是该线路就有两辆车，符合条件）。
  *    最终答案要求每趟线路上至少有两辆车，最后通过head，tail 来检验一下是否满足条件。
  *
  *)
 var
   head,tail,num:array[0..59] of longint;
   ans,tot:longint;
 function check:boolean;
 var
   i:longint;
 begin
   for i:=0 to 59 do
   if head[i]>tail[i] then exit(false);
   exit(true);
 end;
 procedure dfs(s:longint);
 var
   i,now,gc:longint;
 begin
   while (s<60) and (num[s]=0) do inc(s);
   if s=60 then
   begin
     if check and (tot<ans) then
     ans:=tot;
   end
   else
   begin
     for i:=0 to s-1 do
     if head[i]>tail[i] then (*设为第二辆车*)
     begin
       gc:=s-i; now:=s+gc;
       while (now<60) and (num[now]>0) do inc(now,gc);
       if now>59 then
       begin
         now:=s; inc(tail[i]);
         while now<60 do
         begin
           dec(num[now]);
           inc(now,gc);
         end;
         dfs(s);
         now:=s; dec(tail[i]);
         while now<60 do
         begin
           inc(num[now]);
           inc(now,gc);
         end;
       end;
     end;
     if tot+1<ans then   (*设为第一辆车*)
     begin
       inc(tot); inc(head[s]); dec(num[s]);
       dfs(s);
       dec(tot); dec(head[s]); inc(num[s]);
     end;
   end;
 end;
 procedure init;
 var
   i,n,a:longint;
 begin
   readln(n);
   for i:=1 to n do
   begin
     read(a);
     inc(num[a]);
   end;
   ans:=maxlongint;
   tot:=0;
   dfs(0);
   writeln(ans);
 end;
 begin
   init;
 end.