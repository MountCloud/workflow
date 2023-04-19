#include "workflow.hpp"

#include <iostream>
#include <cstdio>
#include <string>

class AddNode : public mc::workflow::WorkNode<int,int>{
public:
    //constructor
    AddNode(int add){
        this->add = add;
    };
    //process
    virtual int onProcess(int idata) override{
        return idata + add;
    };
private:
    int add = 0;
};

class PrintNode : public mc::workflow::WorkNode<int,void*>{
public:
    //constructor
    PrintNode(std::string name){
        this->name = name;
    };
    //process
    virtual void* onProcess(int idata) override{
        std::cout << name << ":" << idata << std::endl;
        return nullptr;
    };

private:
    std::string name;
};


int main(){


/***
test node



*/

    AddNode addNode1(1);

    AddNode addNode2(10);

    PrintNode pnode1("pnode1");
    PrintNode pnode2("pnode2");
    PrintNode pnode3("pnode3");

    addNode1.addConditionNext([](int odata){
        return odata > 10;
    },&pnode1);
    
    addNode1.addConditionNext([](int odata){
        return odata <= 10;
    },&pnode2);

    addNode1.addConditionNext([](int odata){
        return odata < 5;
    },&pnode3);


    PrintNode pnode4("pnode4");
    addNode2.addNext(&pnode4);

    addNode1.addNext(&addNode2);

    
    while (true)
    {
        std::string str;
        std::cin >> str;
        if(str == "exit"){
            break;
        }

        int num = std::stoi(str);
        addNode1.run(num);
    }
    

    return 0;
}