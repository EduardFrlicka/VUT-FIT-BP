/*!file:__class_name__/message___method_name__.cpp*/
#include "net_multiset.h"

/*!ignore*/
{
    {
        auto arg = *it++;
        if (arg->empty())
            std::cout << "Empty method argument" << std::endl;
        m.place("__argument_name__")->push(PNtalk::MultiSet(arg));
    }
    /*?__argument__*/

    /*!ignore*/
}