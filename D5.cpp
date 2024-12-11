#include <iostream>
#include <fstream>
#include <vector>
#include <list>

void Input(std::string path,std::vector<std::vector<int>>* D,std::vector<std::vector<int>>* T){
        std::ifstream read_file(path);
        std::string str;
        int i =0;
        while (std::getline (read_file, str)) {
            //std::cout<<str<<std::endl;
            if(str.size()==0){
                continue;
            }
            else if(str[2]=='|'){
                //std::cout<<"hi"<<std::endl;
                int num1 = std::stoi(str.substr(0,2));
                int num2=std::stoi(str.substr(3,2));
                //std::cout<<num1<<" "<<num2<<std::endl;
                D->at(num1)[num2]=1;
            }
            else if(str[2]==','){
                int j = 0;
                std::vector<int> vec = {};
                std::string num = "";
                while(j<str.size()){
                    if(isdigit(str[j])){
                        num.push_back(str[j]);
                    }
                    else if(str[j]==','){
                        //std::cout<<num<<std::endl;
                        vec.push_back(std::stoi(num));
                        num="";
                        
                    }
                    j++;
                }
                vec.push_back(std::stoi(num));
                T->push_back(vec);
                i++;
            }
        }
    read_file.close();
    return ;
}

//ugly brute force//
int Solve1(std::vector<std::vector<int>>*D,std::vector<std::vector<int>>*T){
    int sum  = 0;
    for(int i =0;i<T->size();++i){
        bool broken = false;
        //std::cout<<"Line no "<<i<<std::endl;
        //std::cout<<"Line size "<<T->at(i).size()<<std::endl;
        for(int j =0;j<T->at(i).size();++j){
            for(int k=j+1;k<T->at(i).size();++k){
                std::cout<<T->at(i)[j]<<" "<<T->at(i)[k]<<std::endl;
                if(D->at(T->at(i)[k])[T->at(i)[j]]==1){
                    broken = true;
                    //std::cout<<"broke"<<std::endl;
                }
            }
        }
        if(broken==false){
            sum+=T->at(i)[T->at(i).size()>>1];
        }
    }
    return sum;
}
//spse G is a general graph//
//create all descendants graph from direct descendants graph//
//j->descends from i//
// Traversing from node u, descendants of u are D(u),D(D(u)) ad infinitum//
//for each node u this requires a total of E computations//
// So this would be an E*V complexity operation//

int Solve2(std::vector<std::vector<int>>*D,std::vector<std::vector<int>>*T){
    //compose descendants array//
    //ie each entry A[i][j] is whether j is descendant of i//
    //this represents an order relation, and thus using std::sort//
    //can get n log n complexity//
    //composing the descendants array//
    //D[i][j]==1=>i is ancestor of j//
    int sum  = 0;
    for(int i =0;i<T->size();++i){
        bool broken = false;
        for(int j =0;j<T->at(i).size();++j){
            for(int k=j+1;k<T->at(i).size();++k){
                if(D->at(T->at(i)[k])[T->at(i)[j]]==1){
                    broken = true;
                }
            }
        }
        if(broken==true){
            //construct new graph//
            //and toposort it//
            std::vector<int> in_count(T->at(i).size(),0);
            std::vector<std::vector<int>> adj_lis(T->at(i).size());
            std::vector<int> sorted;
            for(int j =0;j<T->at(i).size();++j){
                for(int k=0;k<T->at(i).size();++k){
                    if(D->at(T->at(i)[j])[T->at(i)[k]]==1){
                        adj_lis[j].push_back(k);
                        in_count[k]+=1;
                    }
                }
            }
            std::list<int> parentless;
            for(int j=0;j<T->at(i).size();++j){
                if(in_count[j]==0){
                    parentless.push_back(j);
                }
            }
            while(parentless.size()!=0){
                int front = parentless.front();
                sorted.push_back(front);
                parentless.pop_front();
                for(int k=0;k<adj_lis[front].size();++k){
                    in_count[adj_lis[front][k]]--;
                    if(in_count[adj_lis[front][k]]==0){
                        parentless.push_back(adj_lis[front][k]);
                    }
                }
            }
            
            int summand  =T->at(i)[sorted[sorted.size()/2]];
            std::cout<<i<<std::endl;
            std::cout<<summand<<std::endl;
            int first = T->at(i)[sorted[0]];
            std::cout<<"First "<<first<<std::endl;
            for(int k = 0;k<100;++k){
                if(D->at(k)[first]==1){
                    std::cout<<"parent of "<<first<<" "<<k<<std::endl;
                }
            }
            sum += summand;
        }
    }
    return sum;
}
