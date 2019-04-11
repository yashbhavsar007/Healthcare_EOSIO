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
        void regpatient(name uname,string bdate, string address, string email, string city, string district, string state);

        [[eosio::action]]
        void regdoctor(name uname, name hname, uint64_t bdate, string bgroup, string expertise, uint64_t experiance, string contactnum, string email, string address, string city, string district, string state);

        [[eosio::action]]
        void reghospital(name hname, std::vector<string> services, string contact, string email, string address, string city, string district, string state);

        [[eosio::action]]
        void docapproval(name hname, name dname, bool approval);

        [[eosio::action]]
        void hosapproval(name hname, bool approval);

        [[eosio::action]]
        void docaction(name dname, name pname, string sugerfasting, string sugarnormal, string bloodpressure, string note );

        // [[eosio::action]]
        // void hosaction(name hname, name dname, bool approval );

        // action for patient for updating information
        // [[eosio::action]] 
        // void paction()

        private:
         struct [[eosio::table]] patient {
            name pname;
            uint64_t bdate;
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

           // EOSLIB_SERIALIZE( patient ,(pname) (bdate) (bgroup) (sugarfasting) (sugarnormal) (bloodpressure) (email) (address) (city) (district) (state) (note) );

            name primary_key()const { return pname; }
         };

         typedef eosio::multi_index< "patients"_n, patient > patientt;

         struct [[eosio::table]] doctor {
            name dname;
            name hname;
            bool approval = "false";
            uint64_t bdate;
            string bgroup;
            string expertise;
            uint64_t experiance;
            string contact;
            string email;
            string address;
            string city;
            string district;
            string state;

            name primary_key()const { return dname; }
        };

         typedef eosio::multi_index< "doctors"_n, doctor > doctort;

          struct [[eosio::table]] hospital {
            name hname;
            bool approval;
            uint64_t numofdoc;
            std::vector<string> services;
            std::vector<name> doctors;
            string email;
            string address;
            string city;
            string district;
            string state;

            name primary_key()const { return hname; }
         };

        typedef eosio::multi_index< "hospitals"_n, hospital > hospitalt;
        
    
    };   

}