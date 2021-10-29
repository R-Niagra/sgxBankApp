#include <string.h>
#include <sys/types.h>
#include <string>
#include "../Enclave.h"
#include "Enclave_t.h"
#include "sgx_lfence.h"
#include "sgx_trts.h"
#include <unordered_map>
// #include "../Enclave.h"
// #include "Enclave_t.h"

using namespace std;

//This class is used by condition variable demo
unordered_map<string, int> bank;


int ecall_createAccount(const char* name){

    string strName = name;

    if(strlen(name)==0){
        printf("Name is empty");
        return -1;
    }

    // printf("name lenght: %zu\n",strlen(name));

    // printf("name pointer : %p\n",(void *)name);

    if(bank.find(strName)!=bank.end()){
        printf("name exists");
        return -1;
    }
    // bank.insert(make_pair<const char*, int>(name,0));
    // string str = name;

    bank[strName]=0;

    // for (auto& x: bank)
    // printf(x.first.c_str(), x.second);
    
    // printf("Account successfully created! \n");
    return 1;
}

int ecall_deposit_fund(const char* name, int amount){
    if(strlen(name)==0){
        // printf("Name is empty");
        return -1;
    }
    string strName = name;

    auto it = bank.find(strName);
    if( it ==bank.end()){
        return -1;
    }

    it->second += amount;
    printf("deposit: %d",bank[name]);
    // printf("Account successfully created! \n");
    return 1;
}

int ecall_withdraw_fund(const char* name, int amount){
    if(strlen(name)==0){
        // printf("Name is empty");
        return -1;

    }
    string strName = name;
    
    auto it = bank.find(strName);
    if(it==bank.end() || it->second < amount){
        return -1;
    }

    it->second -= amount;
    // printf("Account successfully created! \n");
    return 1;
}

int ecall_transfer_fund(const char* sender, const char* receiver, int amount){
    if(strlen(sender)==0 || strlen(receiver)==0){
        printf("Name is empty");
        return -1;
    }
    string strSender = sender;
    string strReceiver = receiver;

    auto sit = bank.find(strSender); //sender iterator
    auto rit = bank.find(strReceiver); //receiver iterator

    //if sender and receiver doesn't exist. Simply return 
    if(sit==bank.end() || rit==bank.end()){
        return -1;
    }else if(sit->second < amount){
        printf("insufficient balance to transfer");
        return -1;
    }

    rit->second += amount;
    sit->second -=amount;
    // printf("Account successfully created! \n");
    return 1;
}

int ecall_get_balance(const char* name){
    if(strlen(name)==0){
        // printf("Name is empty");
        return -1;
    }
    string strName = name;
    auto it = bank.find(strName);
    if(it==bank.end()){
        //entry doesn't exist
        return -1;
    }

    return it->second;

}

