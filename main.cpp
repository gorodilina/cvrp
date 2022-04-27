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
                //int m=max(w[j+1][i], w[j+1-it[i].weight][i]+it[i].value);
                //w[j+1][i+1]=m;
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

int main()
{
    int N, V, c;
    //Path My_path;
    cin >> N >> V >> c;
    vector <item> points (N);
    //считываем данные
    for (int i=0; i<N; i++)
    {
        cin >> points[i].weight >> points[i].x >> points[i].y;
        points[i].value=points[i].weight;
        points[i].id=i;
    }
    //каждый грузовик воображаем рюкзаком, каждую потребность - предметом, вес равен ценности
    vector<vector<item>>usedused(V);
    //usedused[0]=knapsack(points, c);
    vector<item>p=points;
    int size=0;
    for (int i=0; i<V; i++)
    {
        //if (size!=N)
        //{
            usedused[i]=knapsack(p, c);
            for (int j=0; j<usedused[i].size(); j++)
                {
                    for (int k=0; k<p.size(); k++)
                    {
                        if (usedused[i][j].id==p[k].id)
                            p.erase(p.begin()+k);
                    }
                }
            //size+=usedused[i].size();
       // }
    }

    //show_mat(usedused);

    //cout<<usedused.size();
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
        //cur.show();
        //cout << cur.length() << endl;
    }
    cout<< ans;
    return 0;
}
