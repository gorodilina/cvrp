#include "head.h"

using namespace std;

int main()
{
    int N, V, c;
    cin >> N >> V >> c;
    vector <item> points (N);
    double mean=0;
    //считываем данные
    for (int i=0; i<N; i++)
    {
        cin >> points[i].weight >> points[i].x >> points[i].y;
        points[i].value=points[i].weight;
        points[i].id=i;
        mean+=points[i].x/N;
    }

    //выводим кластеры
    vector<vector<item>> clusters(2);
    k_means(clusters, points, mean);
    //vector<vector<item>> clusters=k_means(points, mean);
    double ANS=0;
    if (N<250)
    {
        for (int i=0; i<clusters.size(); i++)
        {
            ANS+=cvrp(clusters[i], V, c).first;
            V=cvrp(clusters[i], V, c).second;
        }
        cout <<endl<< "ANS="<< ANS;
    }
    else
    {
        ANS=cvrp(points, V, c).first;
        cout <<endl<< "ANS="<< ANS;
    }
    return 0;
}
