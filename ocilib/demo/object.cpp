#include "ocilib.hpp"

/* 
    DML for the test 

    create type t_vendor as object
    ( 
        code  number, 
        name  varchar2(30)
    ); 
    /		
    create type t_sale as object 
    ( 
        code  number, 
        price  float, 
        name  varchar2(30),
        ref  varchar2(30), 
        date_sale date, 
        vendor  t_vendor
    ); 
    /
    create table sales(item t_sale);

*/

using namespace ocilib;

int main(void)
{
    try
    {
        Environment::Initialize();

        Connection con("db11g", "usr", "pwd");

        Date date;
        date.SysDate();

        Object sale  (TypeInfo(con, "t_sale"  , OCI_TIF_TYPE));
        Object vendor(TypeInfo(con, "t_vendor", OCI_TIF_TYPE));

        vendor.Set<int>("CODE", 134);
        vendor.Set<dstring>("NAME", "JOHN SMITH");

        sale.Set<int>("CODE", 1);
        sale.Set<double>("PRICE", 12.99);
        sale.Set<dstring>("NAME", "USB KEY 2go");
        sale.Set<dstring>( "REF", "A56547WSAA");
        sale.Set<Date>("DATE_SALE", date);
        sale.Set<Object>("VENDOR", vendor);

        Statement st(con);
        st.Prepare("insert into sales values(:obj)");
        st.Bind(":obj", sale, OCI_BDM_IN);
        st.Execute();

        std::cout << "Rows inserted :  " << st.GetAffectedRows() << std::endl;


        con.Commit();        
    }
    catch(Exception &ex)
    {
         std::cout << ex.GetMessage() << std::endl;
    }

    Environment::Cleanup();
 
    return EXIT_SUCCESS;
}
