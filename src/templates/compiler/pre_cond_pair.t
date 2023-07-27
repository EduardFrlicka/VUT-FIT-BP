//*!slot:transition_filename:__class_name__/*?/__net_name__*//__transition_name__*/

/*!file:__transition_filename__/check.cpp*/
/*!ignore*/
int check() {

    if (!match("__place_name__", __multiset__))
        return false;

    /*!ignore*/
}
/*?__pre_cond__*/

/*!file:__transition_filename__/execute.cpp*/

/*!ignore*/
int check() {

    if (!pop("__place_name__", __multiset__))
        return;

    /*!ignore*/
}
/*?__pre_cond__*/
