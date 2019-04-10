
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
            p.pname = uname;
            p.bdate = bdate;
            p.bgroup = "";
            p.sugarfasting = "";
            p.sugarnormal = "";
            p.bloodpressure = "";
            p.email = email;
            p.address = address;
            p.city = city;
            p.district = district;
            p.state = state;
            p.note = "";
        });

    }

    

}
