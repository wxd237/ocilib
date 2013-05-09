#include "ocilib.hpp"

using namespace ocilib;

int main(void)
{
    try
    {
        Environment::Initialize();

        Timestamp tm(OCI_TIMESTAMP);
        Interval itv(OCI_INTERVAL_DS);

        tm.SysTimestamp();
        std::cout << tm.ToString("DD/MM/YYYY HH24:MI:SS:FF3") << std::endl;

        itv.SetDaySecond(1,1,1,1,0);
        std::cout << itv.ToString() << std::endl;

        tm.AddInterval(itv);
        std::cout << tm.ToString("DD/MM/YYYY HH24:MI:SS:FF3") << std::endl;
    }
    catch(Exception &ex)
    {
         std::cout << ex.GetMessage() << std::endl;
    }

    Environment::Cleanup();
 
    return EXIT_SUCCESS;
}
