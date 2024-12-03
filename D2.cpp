#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::vector<std::vector<int>> InputToVector(std::string path){
    std::vector<std::vector<int>> vec;
    std::ifstream read_file(path);
    std::string str;
    int line_count=0;
    while (std::getline (read_file, str)) {
        vec.push_back({});
        std::istringstream stream(str);
        int num;
        while(stream>>num){
            vec[line_count].push_back(num);
        }
        line_count++;
    }
    read_file.close();
    return vec;
}
std::vector<int> Solve1(std::vector<std::vector<int>> vec){
    std::vector<int> out(vec.size(),0);
    for(int i =0;i<vec.size();++i){
        //std::cout<<vec[i][0]<<std::endl;
        bool inc = (vec[i][1]>vec[i][0]);
        bool dec = (vec[i][1]<vec[i][0]);
        bool fail = !(std::abs(vec[i][0]-vec[i][1])>0&&std::abs(vec[i][0]-vec[i][1])<4);
        if(fail){
            continue;
        }
        bool broken = false;
        for(int j =1;j<vec[i].size()-1;++j){
            bool new_inc = vec[i][j+1]>vec[i][j];
            bool new_dec = vec[i][j+1]<vec[i][j];
            fail = !(std::abs(vec[i][j]-vec[i][j+1])>0&&std::abs(vec[i][j]-vec[i][j+1])<4);
            if(new_inc!=inc||new_dec!=dec){
                broken = true;
                break;
            }
            else if(fail){
                broken = true;
                break;
            }
        }
        if(!broken){
            out[i]=1;
        }
    }
    return out;
}
struct state{
    bool inc;
    bool dec;
    bool safe;
};
std::vector<int> Solve2(std::vector<std::vector<int>> vec){
    //a line is safe if for any n //
    //the sequence T[0:n] & T[n+1:end] is safe and//
    //T[n-1]->T[n+1] is safe//
    //this can be done in 0(length) time//
    //cringe edge cases//
    std::vector<int> out(vec.size(),0);
    //std::cout<<vec.size()<<std::endl;
    for(int i =0;i<vec.size();++i){
        std::vector<state> forward(vec[i].size());
        std::vector<state> backward(vec[i].size());
        for(int j =0;j<vec[i].size();++j){
            if(j==0){
                forward[j]={true,true,true};
            }
            else{
                bool diff = std::abs(vec[i][j]-vec[i][j-1])>0&&std::abs(vec[i][j]-vec[i][j-1])<4;
                bool inc = vec[i][j]>vec[i][j-1];
                bool dec = vec[i][j]<vec[i][j-1];
                if(diff==false){
                    forward[j]={inc,dec,false};
                }
                else if(j==1){
                    forward[1]={inc,dec,true};
                }
                else if(forward[j-1].safe==false){
                    forward[j]={inc,dec,false};
                }
                else if(forward[j-1].inc!=inc||forward[j-1].dec!=dec){
                    forward[j]={inc,dec,false};
                }
                else{
                    forward[j]={inc,dec,true};
                }
            }
        }
        for(int j=vec[i].size()-1;j>=0;--j){
            if(j==vec[i].size()-1){
                backward[j]={true,true,true};
            }
            else{
                bool diff = std::abs(vec[i][j]-vec[i][j+1])>0&&std::abs(vec[i][j]-vec[i][j+1])<4;
                bool inc = vec[i][j+1]>vec[i][j];
                bool dec = vec[i][j+1]<vec[i][j];
                if(diff==false){
                    backward[j]={inc,dec,false};
                }
                else if(j==vec[i].size()-2){
                    backward[j]={inc,dec,true};
                }
                else if(backward[j+1].safe==false){
                    backward[j]={inc,dec,false};
                }
                else if(backward[j+1].inc!=inc||backward[j+1].dec!=dec){
                    backward[j]={inc,dec,false};
                }
                else{
                    backward[j]={inc,dec,true};
                }
            }
        }
        if(forward[vec[i].size()-1].safe==true){
            out[i]=1;
            continue;
        }
        for(int j =0;j<vec[i].size();++j){
            //consider skipping j//
            //forward j is the subsequence up to and including j//
            //backward j is the subsequence down to and including j//
            if(j==0){
                if(backward[1].safe==true){
                    out[i]=1;
                    //std::cout<<i<<" "<<j<<std::endl;
                    break;
                }
            }
            if(j==vec[i].size()-1){
                if(forward[vec[i].size()-2].safe==true){
                    out[i]=1;
                    //std::cout<<i<<" "<<j<<std::endl;
                    break;
                }
            }
            else{
                bool both_safe = backward[j+1].safe==true&&forward[j-1].safe==true;
                bool dec_shared = backward[j+1].dec==true&&forward[j-1].dec==true;
                bool inc_shared = backward[j+1].inc==true&&forward[j-1].inc==true;
                if(both_safe){
                    bool diff = std::abs(vec[i][j-1]-vec[i][j+1])>0&&std::abs(vec[i][j-1]-vec[i][j+1])<4;
                    bool inc = vec[i][j-1]<vec[i][j+1];
                    bool dec = vec[i][j-1]>vec[i][j+1];
                    if(diff==true&&((dec_shared==dec&&dec==true)!=(inc_shared==inc&&inc==true))){
                        out[i]=1;
                        //std::cout<<i<<" "<<j<<std::endl;
                        //std::cout<<"dec "<<dec<<" dec_shared "<<dec_shared<<std::endl;
                        //std::cout<<"inc "<<inc<<" inc_shared "<<inc_shared<<std::endl;
                        break;
                    }
                }
            }
        }
    }
    return out;
}
