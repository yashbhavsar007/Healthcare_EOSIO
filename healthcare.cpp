
#include "healthcare.hpp"
namespace eosio {

    // Action for registeering patient on eos blockchain
    void healthcare::regpatient(name uname, uint64_t bdate, string address, string email, string city, string district, string state)
    {   
        require_auth( uname );
        
        patientt ptable( _self, uname.value );
        auto existing = ptable.find( uname.value);
        check( existing == ptable.end(), "Patient already exists in our record!" );

        // Emplacing records on tables and left some fields blank intentionally because patient doesn't have rights to enter blank fields.
        ptable.emplace( _self, [&]( auto& p) {
            p.pname          = uname;
            p.bdate          = bdate;
            p.bgroup         = "";
            p.sugarfasting   = "";
            p.sugarnormal    = "";
            p.bloodpressure  = "";
            p.email          = email;
            p.address        = address;
            p.city           = city;
            p.district       = district;
            p.state          = state;
            p.note           = "";
        });

    }


    // This action is for registering doctors
    void healthcare::regdoctor(name uname, name hname, uint64_t bdate, string bgroup, string expertise, uint64_t experiance, string contactnum, string email, string address, string city, string district, string state)
    {

        require_auth( uname );
        
        doctort dtable( _self, uname.value );
        auto existing = dtable.find( uname.value );
        check( existing == dtable.end(), "Doctor already exists in our record!" );

        dtable.emplace(_self,[&]( auto &d ){
            d.dname        = uname;
            d.hname        = hname;
            d.bdate        = bdate;
            d.bgroup       = bgroup;
            d.expertise    = expertise;
            d.experiance   = experiance;
            d.contact      = contactnum;
            d.email        = email;
            d.address      = address;
            d.city         = city;
            d.district     = district;
            d.state        = state;
            
        });
    }


    // This action is for registering hospital
    void healthcare::reghospital(name hname, std::vector<string> services, std::vector<name> doctors,string contact, string email, string address, string city, string district, string state)
    {
        require_auth(hname);

        hospitalt htable(_self, hname.value);
        auto existing = htable.find(hname.value);
        check( existing == htable.end(), "Hospital already exists in our record!");

        htable.emplace(_self,[&]( auto &h ){
            h.hname     = hname;
            h.numofdoc  = 0;
            h.services  = services;
            h.doctors   = doctors;
            h.email     = email;
            h.address   = address;
            h.city      = city;
            h.district  = district;
            h.state     = state;
        });
    }

    // This action is for approval of doctor by hospital
    void healthcare::docapproval(name hname, name dname, bool approval)
    {
        require_auth( hname );
        
        doctort dtable( _self, dname.value );
        auto dexisting = dtable.find( dname.value );
        check( dexisting != dtable.end(), "Doctor not exists in our record!" );


        hospitalt htable( _self, hname.value);
        auto hexisting = htable.find(hname.value);
        check( hexisting != htable.end(), "Hospital not exists in our record!");

        dtable.modify(dexisting,_self,[&]( auto &d ){

            d.approval = approval;

        });

        // htable.modify(hexisting,_self,[&]( auto &d ){

        //     d.doctors = dname;

        // });

    }    


    void healthcare::hosapproval(name hname, bool approval)
    {
        require_auth( _self );
        
        
        hospitalt htable( _self, hname.value);
        auto hexisting = htable.find(hname.value);
        check( hexisting != htable.end(), "Hospital not exists in our record!");

        htable.modify(hexisting,_self,[&]( auto &h ){

            h.approval = approval;

        });
    }


    void healthcare::docaction(name dname, name pname, string sugerfasting, string sugarnormal, string bloodpressure, string note )
    {
        require_auth(dname);

        patientt ptable( _self, pname.value );
        auto existing = ptable.find( pname.value );
        check( existing != ptable.end(), "Patient not exists in our record!" );

        ptable.modify( existing,_self,[&]( auto &p){
            p.sugarfasting  = sugerfasting;
            p.sugarnormal   = sugarnormal;
            p.bloodpressure = bloodpressure;
            p.note          = note;
        });

    }

}
EOSIO_DISPATCH( eosio::healthcare, (regpatient) (regdoctor) (reghospital) (docapproval) (hosapproval) (docaction) )
