#include<cstdio>
#include<queue>
#include<string>
#include<cstring>
#include<unordered_set>

using namespace std;

int N,M;//顶点数和边数
vector<int> Adj[1005];//邻接表
int score[1005][1005];//score[a][b]代表a测试点获得的最低得分可以有资格考b考试
int voucher[1005][1005];//voucher[a][b]代表a测试点获得score[a][b]及以上分数可以得到考b的代金券
int inDegree[1005];// 每一个顶点的入度
bool inQueue[1005];// 标记已经入队的节点
unordered_set<int> zeroDegree;// 图中所有入度为0的顶点,这里指原图中入度为0的顶点 

// 拓扑排序判断是否有环存在 
bool topologicalOrder(){
    queue<int> q;
    int num = 0;
    // 入队所有入度为0的顶点
    for(int i=0;i<N;++i){
        if(inDegree[i]==0){
            inQueue[i] = true;
            q.push(i);
        }
    }
    while (!q.empty()){
        int t = q.front();
        q.pop();
        ++num;//统计入队的结点个数 
        // 将t的临界点的入度全部减一
        for(int vertex:Adj[t]){
            --inDegree[vertex];
            // 将入度为0且没有入队的节点入队
            if(inDegree[vertex]==0){
                q.push(vertex);
            }
        }
    }
    return num==N;// true表示没有环 
}

int dis[1005];// 每一个节点到起点的最短距离(分数)
int money[1005];// 每一个节点到起点获得到最大代金券
bool visited[1005];// 标记每一个节点是否访问
int pre[1005];// 每一个节点的前驱节点

void Dijsktra(int start){
    fill(dis,dis+1005,0x3ffffff);
    dis[start] = 0;
    money[start] = 0;
    for(int i=0;i<N+1;++i){// N+1个顶点 
        // 找出距离起点最短的未访问节点
        int min_dis = 0x3fffff;
        int min_index = -1;
        for(int j=0;j<N+1;++j){
            if(!visited[j]&&dis[j]<min_dis){
                min_dis = dis[j];
                min_index = j;
            }
        }
        if(min_index==-1) return;
        visited[min_index] = true;
        // 优化路径
        for(int j=0;j<Adj[min_index].size();++j){
            int v = Adj[min_index][j];
            if(!visited[v]){
                if(dis[v]>dis[min_index]+score[min_index][v]){
                    // 当前路径更短
                    pre[v] = min_index;
                    dis[v] = dis[min_index]+score[min_index][v];
                    money[v] = money[min_index] + voucher[min_index][v];
                } else if(dis[v]==dis[min_index]+score[min_index][v]&&
                        money[v]<money[min_index]+voucher[min_index][v]){
                    // 需要考试的分数一样，但是获得的代金券更多
                    pre[v] = min_index;
                    money[v] = money[min_index] + voucher[min_index][v];
                }
            }
        }
    }
}

void DFS(int end){
    if(pre[end]==N){
        // 到达起点 
        printf("%d",end);
        return;
    }
    DFS(pre[end]);
    printf("->%d",end);
}

void consistent(int query[],int K){
    Dijsktra(N);// 获得每一个结点的最短距离和路径 
    for(int i=0;i<K;++i){
        if(zeroDegree.find(query[i])!=zeroDegree.end()){
            // 当前考试没有前置条件
            printf("You may take test %d directly.",query[i]);
        }else{
            DFS(query[i]);
        }
        if(i<K-1) printf("\n");
    }
}

void notConsistent(int query[],int K){
    for(int i=0;i<K;++i){
        if(zeroDegree.find(query[i])!=zeroDegree.end()){
            // 当前考试没有前置条件
            printf("You may take test %d directly.",query[i]);
        }else{
            printf("Error.");
        }
        if(i<K-1) printf("\n");
    }
}

int main(){
    scanf("%d %d",&N,&M);
    for (int i = 0; i < M; ++i) {
        int a,b;
        scanf("%d %d",&a,&b);
        scanf("%d %d",&score[a][b],&voucher[a][b]);
        ++inDegree[b];
        Adj[a].push_back(b);
    }
    // 添加一个入度为0的顶点,顶点编号为N,与所有入度为0的顶点连接一条边，这样N就是唯一的入度为0的顶点了 
    for(int i=0;i<N;++i){
        if(inDegree[i]==0){
            Adj[N].push_back(i);
            zeroDegree.insert(i);
        }
    }
    int K;
    scanf("%d",&K);
    int query[K];
    for(int i=0;i<K;++i){
        scanf("%d",&query[i]);
    }
    bool isOk = topologicalOrder();
    if(isOk){
        printf("Okay.\n");
        consistent(query,K); 
    } else {
        printf("Impossible.\n");
        notConsistent(query,K); 
    }
    return 0;
}