#include "head.h"

using namespace std;


struct item
{
    double weight, value, x, y, id;
};

void show_mat(vector<vector<item>> &M)
{
    int N=M.size();
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M[i].size(); j++)
        {
            cout<< M[i][j].id<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

vector<item> knapsack (vector<item>& it, int K)
{
    int N=it.size();
    vector<vector<int>> w(K+1, vector<int>(N+1));
    vector <vector<vector<item>>> used(K+1, vector<vector<item>>(N+1));
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<K; j++)
        {
            if (it[i].weight<=j+1)
            {
                if (w[j+1][i]>=w[j+1-it[i].weight][i]+it[i].value)
                {
                    w[j+1][i+1]=w[j+1][i];
                    used[j+1][i+1]=used[j+1][i];
                }
                else
                {
                    w[j+1][i+1]=w[j+1-it[i].weight][i]+it[i].value;
                    used[j+1][i+1]=used[j+1-it[i].weight][i];
                    used[j+1][i+1].push_back(it[i]/*.value*/);
                }
            }
            else
            {
                w[j+1][i+1]=w[j+1][i];
                used[j+1][i+1]=used[j+1][i];
            }
        }
    }
    return used[K][N];
}


vector<vector<item>> k_means(vector <item>& points, double mean)
{
    int N=points.size();
    vector<vector<item>> clusters(2);
    for (int i=0; i<N; i++)
    {
        if (points[i].x>mean)
            clusters[0].push_back(points[i]);
        else
            clusters[1].push_back(points[i]);
    }
    clusters[0].push_back(points[0]);
    clusters[1].push_back(points[0]);
    return clusters;
}


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
    vector<vector<item>> clusters=k_means(points, mean);
    for (int i=0; i<clusters.size(); i++)
    {
        for (int j=0; j<clusters[i].size(); j++)
             cout <<clusters[i][j].id<< " ";
        cout << endl;
    }
    double ANS=0;
    if (N<250)
    {

    for (int i=0; i<clusters.size(); i++)
    {
    //каждый грузовик воображаем рюкзаком, каждую потребность - предметом, вес равен ценности
    vector<vector<item>>usedused;//наборы городов для каждого грузовика
    vector<item>p=clusters[i];
    for (int i=0; i<V; i++)
    {
            usedused.push_back(knapsack(p, c));
            for (int j=0; j<usedused[i].size(); j++)
                {
                    for (int k=0; k<p.size(); k++)
                    {
                        if (usedused[i][j].id==p[k].id)
                            p.erase(p.begin()+k);
                    }
                }
            if (p.size()==0)
                break;
    }
    V=V-usedused.size();
    cout << "used used"<<endl;
    show_mat(usedused);
    double ans=0;

    for (int i=0; i<usedused.size(); i++)
    {
        Path cur;
        for (int j=0; j<usedused[i].size(); j++)
        {
             pt newone = {usedused[i][j].id, usedused[i][j].x, usedused[i][j].y};
   	         cur.add_node(newone);
        }
        cur.local_search_2();
        ans+=cur.length();
        //cout << cur.length() << endl;
        cur.show();
        //cout << cur.length() << endl;
    }
    ANS+=ans;
    }
    cout <<endl<< "ANS="<< ANS;
    }
    else
    {
    vector<vector<item>>usedused;
    vector<item>p=points;
    for (int i=0; i<V; i++)
    {
            usedused.push_back(knapsack(p, c));
            //cout << "vehicles left="<<V+1-usedused.size()<<endl;
            for (int j=0; j<usedused[i].size(); j++)
                {
                    for (int k=0; k<p.size(); k++)
                    {
                        if (usedused[i][j].id==p[k].id)
                            p.erase(p.begin()+k);
                    }
                }
            if (p.size()==0)
                break;
    }
    double ans=0;

    for (int i=0; i<usedused.size(); i++)
    {
        Path cur;
        for (int j=0; j<usedused[i].size(); j++)
        {
             pt newone = {usedused[i][j].id, usedused[i][j].x, usedused[i][j].y};
   	         cur.add_node(newone);
        }
        cur.local_search_2();
        ans+=cur.length();
        cur.show();
    }
    ANS+=ans;

    cout <<endl<< "ANS="<< ANS;
    }
    return 0;
}
