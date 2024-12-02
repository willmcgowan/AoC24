#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::vector<std::vector<int>> InputToVector(std::string path){
    std::vector<std::vector<int>> vec(2);
    std::ifstream read_file(path);
    std::string str;
    while (std::getline (read_file, str)) {
        int num1 = std::stoi(str.substr(0,5));
        int num2 = std::stoi(str.substr(8,5));
        vec[0].push_back(num1);
        vec[1].push_back(num2);
    }
    read_file.close();
    return vec;
}
int Solve1(std::vector<std::vector<int>> vec){
    std::sort(vec[0].begin(),vec[0].end());
    std::sort(vec[1].begin(),vec[1].end());
    int sum = 0;
    for(int i =0;i<vec[0].size();++i){
        sum+=std::abs(vec[0][i]-vec[1][i]);
    }
    return sum;
}
int Solve2(std::vector<std::vector<int>> vec){
    std::unordered_map<int,int> umap;
    for(int i =0;i<vec[0].size();++i){
        if(umap.count(vec[0][i])==0){
            umap.insert({vec[0][i],0});
        }
    }
    int similarity_score = 0;
    for(int i=0;i<vec[1].size();++i){
        if(umap.count(vec[1][i])!=0){
            similarity_score+=vec[1][i];
        }
    }
    return similarity_score;
}
