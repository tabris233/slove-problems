#include <bits/stdc++.h>

using namespace std;

const int N = 300000+7;

/**********

author: tabris
time: 2018-01-29 13:17:08
discription: 双栈实现一个队列.

先存到栈1里面
就是再有一个pop()/front的时候将栈1的元素移到栈2 这时候就是先进先出了
**********/

template<class T>
class Queue{
private:
    stack<T>s1,s2;
public:
    void pop(){
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        if(s2.empty()){
            puts("Queue is empty!!!");
            return ;
        }
        s2.pop();
    }
    void push(T x){
        printf("Queue push %d\n",x);
        s1.push(x);
    }
    T front(){
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        if(s2.empty()){
            puts("Queue is empty!!!");
            return -1;
        }
        return s2.top();
    }
    int size(){
        return s1.size()+s2.size();
    }
    bool empty(){
        return s1.size()+s2.size() == 0;
    }

};

int main(){
    Queue <int > q;
    char op[11];
    int x;
    while(scanf("%s",op)){
        if(op[0]=='p'){
            if(op[1] == 'o'){
                q.pop();
            }
            else {
                scanf("%d",&x);
                q.push(x);
            }
        }
        else if(op[0] == 'f'){
            printf("q.front() = %d\n",q.front());
        }
        else if(op[0] == 's'){
            printf("q.size() = %d\n",q.size());
        }
        else if(op[0] == 'e'){
            if(q.empty()) puts("q is empty!");
            else          puts("q is not empty!");
        }
    }
    return 0;
}
