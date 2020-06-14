/*
    DP 를 활용한 그래프 최단 경로 찾기

    그래프의 최단 경로를 찾는 방법은 아주 다양한 알고리즘이 존재하지만,
    여기서는 아주 기본적인 DP 를 이용한 최단 경로 탐색을 수행해 본다

    코드를 작성하기에 앞서서 DP 의 핵심 개념인 
    작은 문제를 겹쳐서 풀지 않는다를 해결하기 위해서 
    다음과 같은 개념들을 살펴봐야한다

    먼저 그래프의 인접 행렬을 표현하기 위한 이차원 배열
    W[i][j] 는 vi 에서 vj 로 가는 이음선이 존재하는지 여부를 나타낸다.
    그래프의 최단 경로 길이를 표현하는 이차원 배열
    D(k)[i][j] 를 이용한다 (vi 에서 vj 로 가는데 걸리는 최소 가중치 길이를 의미함)
    (k 는 v1, v2, .. vk 의 정점이 존재한다는 의미임)
    즉 D(0) 은 W[i][j] 를 의미함
    왜냐? 공집합에서의 두 정점간 이동거리 값을 의미하기 때문임

    이 문제에 대한 답을 구하기 위해서는
    이차원 배열 D 를 구할 수 있어야한다.
    D 를 공식으로 나타내면 이렇게 표현된다.
    D(k)[i][j] = min(D(k-1)[i][j], D(k-1)[i][k] + D(k-1)[k][j]); 로 표현된다.

    Vk 를 거치지 않는 경우가 D(k-1)[i][j] 이고,
    Vk 를 거치고 계산하는 최단 경우가 D(k-1)[i][k] + D(k-1)[k][j] 이다.

    이 계산을 도와주는 알고리즘 중 하나가 Floyd-Warshall 알고리즘 이다.

    플로이드 - 와샬 알고리즘의 핵심은 
    '거쳐가는 정점' 을 기준으로 최단거리를 어떻게 구하느냐 이다.
    모든 정점에서 모든 정점으로의 최단경로를 구하고 싶을 때 사용하는데,
    어떤 정점에서 다른 정점으로 갈때 최소 거리가 얼마나 되느냐 를 따지는건데,
    도중에 거쳐가는 중간 노드가 있는 경우, 최소 비용이 갱신되면, 그 중간 노드를 거쳐가자
    가 핵심 개념인 알고리즘임

    Floyd 알고리즘에 대한 pseudo code 는 아래와 같다
    void floyd (int n, const number W[][], number D[][]) {
        int i, j, k;
        D = W; // 초기에 D 는 W 와 같다
        for (k = 1; k <= n; k++) {
            for (i = 1; i <= n; i++) {
                for (j = 1; j <= n; j++) {
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                }
            }
        }
    }
    
    플로이드 와샬 알고리즘의 시간 복잡도는
    O(N^3) 이다.
*/

#include <stdio.h>
#define number 4
#define INF 1000000

// 인접 행렬을 나타내는 a[][]
int a[4][4] = {
    {0, 5, INF, 8},
    {7, 0, 9, INF},
    {2, INF, 0, 4},
    {INF, INF, 3, 0}};

void floydWarshall()
{
    // d 는 두 노드간 최단 거리를 나타내는 이차원배열임
    int d[number][number];

    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            d[i][j] = a[i][j];
        }
    }
    // 위의 이중 포문은 이차원배열 d 를 초기화 하기 위함임
    // D(0) = W 임.

    // 플로이드 와샬 알고리즘은 일반적으로 3중 포문을 이용해서 값을 구함
    for (int k = 0; k < number; k++)
    {
        for (int i = 0; i < number; i++)
        {
            for (int j = 0; j < number; j++)
            {
                // k 는 거쳐가는 노드, i 는 시작노드, j 는 도착 노드임
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    // min(D(k-1)[i][j], D(k-1)[i][k] + D(k-1)[k][j]) 를 나타낸 조건문임
                }
            }
        }
    }

    // 최소 비용 출력을 위한 이중 포문
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            printf("%3d ", d[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    floydWarshall();
    return 0;
}