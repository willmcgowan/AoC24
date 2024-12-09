#include <iostream>
#include <vector>
#include <fstream>
std::vector<std::string> Input(std::string path){
    std::vector<std::string> out;
    std::ifstream read_file(path);
    std::string str;
    while (std::getline (read_file, str)) {
        out.push_back(str);
    }
    read_file.close();
    return out;
}
bool StrEqual(std::string s1,std::string s2){
    if(s1.size()!=s2.size()){
        return false;
    }
    else{
        for(int i =0;i<s1.size();++i){
            if(s1[i]!=s2[i]){
                return false;
            }
        }
        return true;
    }
}

int CountMatches1(std::vector<std::string>* T, int i, int j){
    int width = T->at(0).size();
    int height = T->size();
    int count = 0;
    std::string match = "XMAS";
    if(T->at(i)[j]!='X'){
        return 0;
    }
    bool NORTH = (i-3)>=0;
    bool SOUTH = (i+3)<height;
    bool EAST = (j+3)<width;
    bool WEST = (j-3)>=0;
    //N//
    if(NORTH){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i-k)[j]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    //E//
    if(EAST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i)[j+k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
        
    }
    //S//
    if(SOUTH){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i+k)[j]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    //W//
    if(WEST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i)[j-k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    //NW//
    if(NORTH&&WEST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i-k)[j-k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    //NE//
    if(NORTH&&EAST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i-k)[j+k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    //SW//
    if(SOUTH&&WEST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i+k)[j-k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    if(SOUTH&&EAST){
        std::string s2 = "";
        for(int k =0;k<4;++k){
            s2.push_back(T->at(i+k)[j+k]);
        }
        bool eq = StrEqual(match,s2);
        if(eq){
            count++;
        }
    }
    return count;
}
int CountMatches2(std::vector<std::string>* T,int i, int j){
    int width = T->at(0).size();
    int height = T->size();
    int count = 0;
    std::string match1 = "MAS";
    std::string match2 = "SAM";
    //DIAG//
    if(T->at(i)[j]!='A'){
        return 0;
    }
    if((i-1>=0&&j-1>=0)&&(i+1<height&&j+1<width)){
        std::string s2 = "";
        std::string s3 = "";
        for(int k =-1;k<2;++k){
            s2.push_back(T->at(i+k)[j+k]);
            s3.push_back(T->at(i+k)[j-k]);
        }
        if((StrEqual(match1,s2)||StrEqual(match2,s2))&&(StrEqual(match1,s3)||StrEqual(match2,s3))){
            count=1;
        }
    }
    return count;
}
int Solve1(std::vector<std::string>* T){
    int count = 0;
    for(int i =0;i<T->size();++i){
        for(int j =0;j<T->at(0).size();++j){
            count+=CountMatches1(T,i,j);
        }
    }
    return count;
}
int Solve2(std::vector<std::string>* T){
    int count = 0;
    for(int i =0;i<T->size();++i){
        for(int j =0;j<T->at(0).size();++j){
            count+=CountMatches2(T,i,j);
        }
    }
    return count;
}
