#include <iostream>
#include "../App.h"
#include "Enclave_u.h"

using namespace std;

void createBankAccount(const char* name){
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retValue=0;
    ret = ecall_createAccount(global_eid,&retValue,name);
    if (ret != SGX_SUCCESS)
        abort();
    if(retValue==1){
        cout<<"Account creation successfull"<<endl;
    }else{
        cout<<"Account creation failed"<<endl;
    }
}

void depositFund(const char* name, int amount){
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retValue=0;
    ret = ecall_deposit_fund(global_eid,&retValue,name,amount);
    if (ret != SGX_SUCCESS)
        abort();
    if(retValue==1){
        cout<<"Deposit successfull"<<endl;
    }else{
        cout<<"Deposit failed"<<endl;
    }
}

void withdrawFund(const char* name, int amount){
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retValue=0;
    ret = ecall_withdraw_fund(global_eid,&retValue,name,amount);
    if (ret != SGX_SUCCESS)
        abort();
    
    if(retValue==1){
        cout<<"Withdraw successfull"<<endl;
    }else{
        cout<<"Withdraw failed"<<endl;
    }
}

void transferFund(const char* sender, const char* receiver, int amount){
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retValue=0;
    ret = ecall_transfer_fund(global_eid,&retValue,sender,receiver,amount);
    if (ret != SGX_SUCCESS)
        abort();
    if(retValue==1){
        cout<<"Transfer successfull"<<endl;
    }else{
        cout<<"Transfer failed"<<endl;
    }
}

void getBalance(const char* name){
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int retValue=0;
    ret = ecall_get_balance(global_eid,&retValue,name);
    if (ret != SGX_SUCCESS)
        abort();
    
    const char* tmp = name;
    while(*tmp != 0) cout<<*tmp++;
    cout<<" balance is: "<<retValue<<endl;
}


