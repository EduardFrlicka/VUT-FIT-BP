#include "expressions.h"

extern const std::vector<std::vector<std::vector<Precedence>>> table_smalltalk;

/*
|     | $   | id  | lit | (   | )   | .   | ;   | :=  | :   | +   | -   | *   | /   | //  | %   | &   | \|  | === | !== | ==  | !=  | <   | >   | <=  | >=  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| $   |     | p   | p   | p   | x   | p   | p   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| id  | r   | r   | r   | x   | r   | r   | r   | e   | e   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| lit | r   | r   | r   | x   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| (   | r   | p   | p   | p   | e   | x   | x   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| )   | r   | r   | x   | x   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| .   | r   | p   | p   | p   | x   | r   | p   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| ;   | x   | e   | x   | x   | x   | x   | x   | x   | x   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   |
| :=  | r   | p   | p   | p   | r   | r   | p   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| :   | r   | p   | p   | p   | r   | r   | r   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| +   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| \-  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| *   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| /   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| //  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| %   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| &   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| \|  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| === | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| !== | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| ==  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| !=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| <   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| >   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| <=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| >=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |

substitutions:
| {1} | p   | p   | p   | p   | p   | p   | p   | p   | r   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |


*/

const std::vector<Precedence> operator_identifior{
    /*$*/ {Precedence::PushStop}, /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::PushStop},
    /*.*/ {Precedence::PushStop}, /*;*/ {Precedence::PushStop},   /*:=*/{Precedence::PushStop},   /*:*/ {Precedence::Reduce},    /*+*/ {Precedence::PushStop},
    /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
    /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
    /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}};

const std::vector<std::vector<std::vector<Precedence>>> table_smalltalk{
    /* $  */
    {/*$*/ {Precedence::End},      /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::Error},
     /*.*/ {Precedence::PushStop}, /*;*/ {Precedence::PushStop},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},     /*+*/ {Precedence::PushStop},
     /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
     /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
     /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}},
    /*==========================================================*/
    /* id */
    {/*$*/ {Precedence::Reduce}, /*id*/ {Precedence::Reduce},  /*lit*/ {Precedence::Reduce}, /*(*/ {Precedence::Error},   /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Push},     /*:*/ {Precedence::Push},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},   /*//*/ {Precedence::Reduce}, /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},  /*!==*/{Precedence::Reduce}, /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},   /*<=*/{Precedence::Reduce},  /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* lit*/
    {/*$*/ {Precedence::Reduce}, /*id*/ {Precedence::Reduce},  /*lit*/ {Precedence::Reduce}, /*(*/ {Precedence::Error},   /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},    /*:*/ {Precedence::Error},   /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},   /*//*/ {Precedence::Reduce}, /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},  /*!==*/{Precedence::Reduce}, /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},   /*<=*/{Precedence::Reduce},  /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* (  */
    {/*$*/ {Precedence::Reduce},   /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::Push},
     /*.*/ {Precedence::Error},    /*;*/ {Precedence::Error},      /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},     /*+*/ {Precedence::PushStop},
     /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
     /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
     /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}},
    /*==========================================================*/
    /* )  */
    {/*$*/ {Precedence::Reduce}, /*id*/ {Precedence::Reduce},  /*lit*/ {Precedence::Error}, /*(*/ {Precedence::Error},   /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},   /*:*/ {Precedence::Error},   /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},  /*//*/ {Precedence::Reduce}, /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce}, /*!==*/{Precedence::Reduce}, /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},  /*<=*/{Precedence::Reduce},  /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* .  */
    {/*$*/ {Precedence::Reduce},   /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::Error},
     /*.*/ {Precedence::Reduce},   /*;*/ {Precedence::PushStop},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},     /*+*/ {Precedence::PushStop},
     /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
     /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
     /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}},
    /*==========================================================*/
    /* ;  */
    {/*$*/ {Precedence::Error}, /*id*/ {Precedence::Push},  /*lit*/ {Precedence::Error}, /*(*/ {Precedence::Error}, /*)*/ {Precedence::Error},
     /*.*/ {Precedence::Error}, /*;*/ {Precedence::Error},  /*:=*/{Precedence::Error},   /*:*/ {Precedence::Error}, /*+*/ {Precedence::Push},
     /*-*/ {Precedence::Push},  /* * */ {Precedence::Push}, /*/*/ {Precedence::Push},    /*//*/ {Precedence::Push}, /*%*/ {Precedence::Push},
     /*&*/ {Precedence::Push},  /*|*/ {Precedence::Push},   /*===*/{Precedence::Push},   /*!==*/{Precedence::Push}, /*==*/{Precedence::Push},
     /*!=*/{Precedence::Push},  /*<*/ {Precedence::Push},   /*>*/ {Precedence::Push},    /*<=*/{Precedence::Push},  /*>=*/{Precedence::Push}},
    /*==========================================================*/
    /* := */
    {/*$*/ {Precedence::Reduce},   /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce},   /*;*/ {Precedence::PushStop},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},     /*+*/ {Precedence::PushStop},
     /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
     /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
     /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}},
    /*==========================================================*/
    /* :  */
    {/*$*/ {Precedence::Reduce},   /*id*/ {Precedence::PushStop},  /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop},  /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce},   /*;*/ {Precedence::Reduce},     /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},     /*+*/ {Precedence::PushStop},
     /*-*/ {Precedence::PushStop}, /* * */ {Precedence::PushStop}, /*/*/ {Precedence::PushStop},   /*//*/ {Precedence::PushStop}, /*%*/ {Precedence::PushStop},
     /*&*/ {Precedence::PushStop}, /*|*/ {Precedence::PushStop},   /*===*/{Precedence::PushStop},  /*!==*/{Precedence::PushStop}, /*==*/{Precedence::PushStop},
     /*!=*/{Precedence::PushStop}, /*<*/ {Precedence::PushStop},   /*>*/ {Precedence::PushStop},   /*<=*/{Precedence::PushStop},  /*>=*/{Precedence::PushStop}},
    /*==========================================================*/
    /* +  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* \- */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* *  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* /  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* // */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* %  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* &  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* \| */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* ===*/
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* !==*/
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* == */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* != */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* <  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* >  */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* <= */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},
    /*==========================================================*/
    /* >= */
    {/*$*/ {Precedence::Reduce}, /*id*/ operator_identifior,   /*lit*/ {Precedence::PushStop}, /*(*/ {Precedence::PushStop}, /*)*/ {Precedence::Reduce},
     /*.*/ {Precedence::Reduce}, /*;*/ {Precedence::Reduce},   /*:=*/{Precedence::Error},      /*:*/ {Precedence::Error},    /*+*/ {Precedence::Reduce},
     /*-*/ {Precedence::Reduce}, /* * */ {Precedence::Reduce}, /*/*/ {Precedence::Reduce},     /*//*/ {Precedence::Reduce},  /*%*/ {Precedence::Reduce},
     /*&*/ {Precedence::Reduce}, /*|*/ {Precedence::Reduce},   /*===*/{Precedence::Reduce},    /*!==*/{Precedence::Reduce},  /*==*/{Precedence::Reduce},
     /*!=*/{Precedence::Reduce}, /*<*/ {Precedence::Reduce},   /*>*/ {Precedence::Reduce},     /*<=*/{Precedence::Reduce},   /*>=*/{Precedence::Reduce}},

};
