
#include <healthcare.hpp>

namespace eosio {

    // Action for registeering patient on eos blockchain
    void healthcare::regpatient(name uname,string bdate, string address, string email, string city, string district, string state)
    {   
        require_auth( uname );
        
        patient ptable( name, uname.code().raw() );
        auto existing = ptable.find( uname.code().raw() );
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
        
        doctor dtable( name, uname.code().raw() );
        auto existing = dtable.find( uname.code().raw() );
        check( existing == dtable.end(), "Doctor already exists in our record!" );

        dtable.emplace(_self,[&]( auto &d ){
            d.dname        = uname;
            d.hname        = hname;
            d.bdate        = bdate;
            d.bgroup       = bgroup;
            d.expertise    = expertise;
            d.experiance   = experiance;
            d.contactnum   = contactnum;
            d.email        = email;
            d.address      = address;
            d.city         = city;
            d.district     = district;
            d.state        = state;
            
        });
    }


    // This action is for registering hospital
    void healthcare::reghospital(name hname, std::vector<string> services, string contact, string email, string address, string city, string district, string state)
    {
        require_auth(hname);

        hospital htable(name, hname.code().raw());
        auto existing = htable.find(hname.code.raw());
        check( existing == htable.end(), "Hospital already exists in our record!");

        htable.emplace(_self,[&]( auto &h ){
            h.name      = hname;
            h.numofdoc  = 0;
            h.services  = services;
            h.doctors   = "";
            h.contact   = contact;
            h.email     = email;
            h.address   = address;
            h.city      = city;
            h.district  = district;
            h.state     = state;
        })
    }

    // This action is for approval of doctor by hospital
    void healthcare::docapproval(name hname, name dname, bool approval)
    {
        require_auth( hname );
        
        doctor dtable( name, dname.code().raw() );
        auto dexisting = dtable.find( dname.code().raw() );
        check( existing == dtable.end(), "Doctor already exists in our record!" );


        hospital htable( name, hname.code().raw());
        auto hexisting = htable.find(hname.code.raw());
        check( existing == htable.end(), "Hospital already exists in our record!");

        dtable.modify(dexisting,_self,[&]( auto &d ){

            d.approval = approval;

        });

        htable.modify(hexisting,_self,[&]( auto &d ){

            d.doctors = dname;

        });

    }    


    void healthcare::hosapproval(name hname, bool approval)
    {
        require_auth( _self );
        
        
        hospital htable( name, hname.code().raw());
        auto hexisting = htable.find(hname.code.raw());
        check( existing == htable.end(), "Hospital already exists in our record!");

        htable.modify(hexisting,_self,[&]( auto &h ){

            h.approval = approval;

        });
    }

}
