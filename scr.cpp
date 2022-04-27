#include "head.h"

using namespace std;

double dist( pt a, pt b ){
    return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) );
}

Path::Path(){
    num_of_nodes = 0;
    last_improvement_status = false;
}

void Path::add_node( pt &new_node ){
    if( num_of_nodes > 1 ){
        path.push_back( path[0] );
        deque<pt>::iterator it = path.begin(),
                            here = it+1;
        double best_len = dist( *it, new_node ) + dist( new_node, *(it+1) );
        it++;

        for(int i=0; i<num_of_nodes-1; i++){
            double tmp = dist( *it, new_node ) + dist( new_node, *(it+1) );
            if( tmp < best_len ){
                best_len = tmp;
                here = it+1;
            }
            it++;
        }

        path.emplace( here, new_node );
        path.pop_back();
    }
    else
        path.push_back( new_node );

    num_of_nodes++;
}

void Path::try_to_improve_2(int v1, int v2){

    if(v1>v2) swap(v1,v2);

    double init_dist =
          dist( path[v1], path[v1+1] )
        + dist( path[v2], path[v2+1] );

    // improval attempt
    double new_dist = dist( path[v1], path[v2] ) + dist( path[v1+1], path[v2+1] );
    if( init_dist > new_dist ){
        deque<pt>::iterator it1 = next( path.begin(), v1+1 );
        deque<pt>::iterator it2 = next( it1, v2-v1 );
        reverse( it1, it2 );
        last_improvement_status = true;
    }
}

double Path::length(){
    double len = 0;
    for(int i=0; i<num_of_nodes; i++)
        len += dist( path[i], path[(i+1)%num_of_nodes] );

    return len;
}

void Path::local_search_2(){
    path.push_back( path[0] );
    for(int i=0; i<num_of_nodes-2; i++)
        for(int j=i+2; j<num_of_nodes; j++){

            try_to_improve_2(i,j);

            if(last_improvement_status){
                last_improvement_status = false;
                j = i+2;
            }
        }
    path.pop_back();
}

void Path::show_a(){
    for(auto p: path)
        cout<<p.id<<": ( "<<p.x<<", "<<p.y<<" )\n";
}

void Path::show(){
    for(auto p: path)
        cout<<p.id<<" ";
}
