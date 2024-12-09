#include <iostream>
#include <vector>
#include <fstream>
#include <string>


std::string InputToString(std::string path){
    std::string out;
    std::ifstream read_file(path);
    std::string str;
    while (std::getline (read_file, str)) {
        for(int i =0;i<str.size();++i){
            out.push_back(str[i]);
        }
    }
    read_file.close();
    return out;
}
int Solve1(std::string* str){
    int out = 0;
    int ptr = 0;
    std::string num1;
    std::string num2;
    int state = 0;
    while(ptr<str->size()){
        switch(state){
            case 0:
                if(str->at(ptr)=='m'){
                    state=1;
                    std::cout<<str->at(ptr);
                }
                break;
            case 1:
                if(str->at(ptr)=='u'){
                    state=2;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state=0;
                }
                break;
            case 2:
                if(str->at(ptr)=='l'){
                    state=3;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state=0;
                }
                break;
            case 3:
                if(str->at(ptr)=='('){
                    state=4;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state=0;
                }
                break;
            case 4:
                if(str->at(ptr)==','){
                    state=5;
                    std::cout<<str->at(ptr);
                }
                else if(isdigit(str->at(ptr))){
                    num1.push_back(str->at(ptr));
                    state=4;
                    std::cout<<str->at(ptr);
                }
                else{
                    state=0;
                    num1="";
                    num2="";
                    std::cout<<std::endl;
                }
                break;
            case 5:
                if(str->at(ptr)==')'){
                    if(num1.size()>0&&num2.size()>0){
                        std::cout<<str->at(ptr)<<std::endl;
                        int n1 = std::stoi(num1);
                        int n2 = std::stoi(num2);
                        std::cout<<n1<<","<<n2<<std::endl;
                        out+=n1*n2;
                        num1="";
                        num2="";
                        state=0;
                    }
                }
                else if(isdigit(str->at(ptr))){
                    num2.push_back(str->at(ptr));
                    std::cout<<str->at(ptr);
                    state=5;
                }
                else{
                    std::cout<<std::endl;
                    num1="";
                    num2="";
                    state=0;
                }
                break;
        }
        ptr++;
    }
    return out;
}
int Solve2(std::string* str){
    int out = 0;
    int ptr = 0;
    std::string num1;
    std::string num2;
    int state1 = 0;
    int state2=0;
    int state3=0;
    int flag = true;
    while(ptr<str->size()){
        switch(state1){
            case 0:
                if(str->at(ptr)=='m'){
                    state1=1;
                    std::cout<<str->at(ptr);
                }
                break;
            case 1:
                if(str->at(ptr)=='u'){
                    state1=2;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state1=0;
                }
                break;
            case 2:
                if(str->at(ptr)=='l'){
                    state1=3;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state1=0;
                }
                break;
            case 3:
                if(str->at(ptr)=='('){
                    state1=4;
                    std::cout<<str->at(ptr);
                }
                else{
                    std::cout<<std::endl;
                    state1=0;
                }
                break;
            case 4:
                if(str->at(ptr)==','){
                    state1=5;
                    std::cout<<str->at(ptr);
                }
                else if(isdigit(str->at(ptr))){
                    num1.push_back(str->at(ptr));
                    state1=4;
                    std::cout<<str->at(ptr);
                }
                else{
                    state1=0;
                    num1="";
                    num2="";
                    std::cout<<std::endl;
                }
                break;
            case 5:
                if(str->at(ptr)==')'){
                    if(num1.size()>0&&num2.size()>0&&flag){
                        std::cout<<str->at(ptr)<<std::endl;
                        int n1 = std::stoi(num1);
                        int n2 = std::stoi(num2);
                        std::cout<<n1<<","<<n2<<std::endl;
                        out+=n1*n2;
                        num1="";
                        num2="";
                        state1=0;
                    }
                }
                else if(isdigit(str->at(ptr))){
                    num2.push_back(str->at(ptr));
                    std::cout<<str->at(ptr);
                    state1=5;
                }
                else{
                    std::cout<<std::endl;
                    num1="";
                    num2="";
                    state1=0;
                }
                break;
        }
        switch(state2){
            case 0:
                if(str->at(ptr)=='d'){
                    state2=1;
                }
                else{
                    state2=0;
                }
                break;
            case 1:
                if(str->at(ptr)=='o'){
                    state2=2;
                }
                else{
                    state2=0;
                }
                break;
            case 2:
                if(str->at(ptr)=='('){
                    state2=3;
                }
                else{
                    state2=0;
                }
                break;
            case 3:
                if(str->at(ptr)==')'){
                    state2=0;
                    std::cout<<"do"<<std::endl;
                    flag=true;
                }
                else{
                    state2=0;
                }
                break;
        }
        switch(state3){
            case 0:
                if(str->at(ptr)=='d'){
                    state3=1;
                }
                else{
                    state3=0;
                }
                break;
            case 1:
                if(str->at(ptr)=='o'){
                    state3=2;
                }
                else{
                    state3=0;
                }
                break;
            case 2:
                if(str->at(ptr)=='n'){
                    state3=3;
                }
                else{
                    state3=0;
                }
                break;
            case 3:
                if(str->at(ptr)=='\''){
                    state3=4;
                }
                else{
                    state3=0;
                }
                break;
            case 4:
                if(str->at(ptr)=='t'){
                    state3=5;
                }
                else{
                    state3=0;
                }
                break;
            case 5:
                if(str->at(ptr)=='('){
                    state3=6;
                }
                else{
                    state3=0;
                }
                break;
            case 6:
                if(str->at(ptr)==')'){
                    state3=0;
                    std::cout<<"dont"<<std::endl;
                    flag=false;
                }
                else{
                    state3=0;
                }
                break;
                
        }
        ptr++;
    }
    return out;
}
