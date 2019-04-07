#pragma once 

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include<string>
           
namespace eosiosystem{
    class system_contract;
}

namespace eosio {
    using std :: string;
    
   class [[eosio::contract("healthcare")]] healthcare : public contract {
        public:
        using contract::contract;
        [[eosio::action]]
        void regpatient(name uname,string age, string address, string email, string city, string district, string state);

        [[eosio::action]]
        void regdoctor(name uname, name hname, uint64_t age, string bgroup, string expertise, uint64_t experiance, string contactnum, string email, string address, string city, string district, string state);

        [[eosio::action]]
        void reghospital(name hname, std::vector<string> services, string contact, string email, string address, string city, string district, string state);

        [[eosio::action]]
        void docapproval(name hname, name dname, bool approval);

        [[eosio::action]]
        void hosapproval(name admin, name hname, bool approval);

        [[eosio::action]]
        void docaction(name dname, name pname, string );

        private:
         struct [[eosio::table]] patient {
            name pname;
            uint64_t age;
            string bgroup;
            string sugarfasting;
            string sugarnormal;
            string bloodpressure;
            string email;
            string address;
            string city;
            string district;
            string state;
            string note;

            name primary_key()const { return pname.symbol.code().raw(); }
         };

         typedef eosio::multi_index< "patient"_n, account > patient;

         struct [[eosio::table]] doctor {
            name dname;
            name hname;
            bool approval;
            uint64_t age;
            string bgroup;
            string expertise;
            uint64_t experiance;
            string contact;
            string email;
            string address;
            string city;
            string district;
            string state;

            name primary_key()const { return dname.symbol.code().raw(); }
        };

         typedef eosio::multi_index< "doctor"_n, account > doctor;

          struct [[eosio::table]] hospital {
            name hname;
            bool approval;
            uint64_t numofdoc;
            std::vector<string> services;
            std::vector<name> doctros;
            string email;
            string address;
            string city;
            string district;
            string state;

            name primary_key()const { return hname.symbol.code().raw(); }
         };

        typedef eosio::multi_index< "hospital"_n, account > hospital;
        
    
    }   

}