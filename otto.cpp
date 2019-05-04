
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
double GetDistance (int x1, int y1, int x2, int y2) {
    return sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
}

std::vector<int> MinimumTime(std::vector<std::pair<int, int>> waypt, std::vector<int> penality, std::vector<int> visited , std::vector<int> valid) {
    int total_penality = 0;
    double min_t = 0.0;
    for(auto p: penality){
        total_penality += p;
    }
    int start_x = 0;
    int start_y = 0;
    int goal_x = 100;
    int goal_y = 100;

    double distance = GetDistance(start_x, start_y, goal_x, goal_y);
    min_t = distance/2 + total_penality; //speed = 2m/s
    double prev_time = 0;
    double time_pt;
    double time_next_pt;
    double time_goal;

    for(int i=0; i< waypt.size(); i++) {
       // cout<<"Inside for";
        if(visited[i]==1 && valid[i]!=1) {
            continue;
        }
        if(visited[i]==1 && valid[i]==1) {
            if(i==0){
                prev_time +=  (GetDistance(start_x, start_y, waypt[i].first, waypt[i].second)/2) + 10;
            }
            else if(i == waypt.size()-1) {
                prev_time += GetDistance(waypt[i-1].first, waypt[i-1].second, goal_x, goal_y)/2;
            }
            else{
                prev_time += (GetDistance(waypt[i-1].first, waypt[i-1].second, waypt[i].first, waypt[i].second)/2) + 10;
            }
        }
        else {
            visited[i] = 1;

            if(i==0) {
                time_pt = (GetDistance(start_x, start_y, waypt[i].first, waypt[i].second)/2) + 10;
                time_next_pt = GetDistance(waypt[i].first, waypt[i].second, goal_x, goal_y)/2;
                time_goal = GetDistance(start_x, start_y, goal_x, goal_y)/2;
            }
            else{
                time_pt = prev_time + (GetDistance(waypt[i-1].first, waypt[i-1].second, waypt[i].first, waypt[i].second)/2) + 10;
                time_next_pt = GetDistance(waypt[i].first, waypt[i].second, goal_x, goal_y)/2;
                time_goal = prev_time + GetDistance(waypt[i-1].first, waypt[i-1].second, goal_x, goal_y)/2;
            }

            if(time_pt + time_next_pt < time_goal + penality[i]) {
                valid[i] = 1;
                MinimumTime(waypt, penality, visited , valid);
            }
        }
    }
    return valid;
}

int main()
{
    int num_waypt;
    std::vector<double> time_final;
    std::cin>>num_waypt;
    while (num_waypt !=0 ) {
        std::vector<std::pair<int, int>> waypt;
        std::vector<int> penality;

        for(int i=0; i<num_waypt; i++) {
            int x=0;
            int y=0;
            int p=0;

            for (int j = 0; j < 3; j++) {
                if(j==0){
                   cin>>x;
                }
                if(j==1){
                   cin>>y;
                }
                if(j==2){
                   cin>>p;
                }
            }
            waypt.push_back(std::make_pair(x,y));
            penality.push_back(p);
        }

        double min_time=0;
        std::vector<int> visited (penality.size(), 0);
        std::vector<int> valid(penality.size(), 0);
        double final_penality = 0;

        valid = MinimumTime(waypt, penality, visited, valid);

        std::vector<std::pair<int, int>> waypt_final;
        waypt_final.push_back(std::make_pair(0,0));
        for (int i = 0; i < valid.size(); ++i)
        {
            if(valid[i] == 1) {
                waypt_final.push_back(waypt[i]);
            }
            else {
                final_penality += penality[i];
            }
        }
        waypt_final.push_back(std::make_pair(100,100));
        for (int j=0; j < waypt_final.size()-1 ;j++) {
            min_time += GetDistance(waypt_final[j].first, waypt_final[j].second, waypt_final[j+1].first, waypt_final[j+1].second)/2 + 10;
        }
        min_time += final_penality;
        time_final.push_back(min_time);
        std::cin >> num_waypt;
    }
    for (auto k : time_final)
    cout << k << endl;


    return 0;
}


