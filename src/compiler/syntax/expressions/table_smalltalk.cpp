#include "expressions.h"

extern const std::vector<std::vector<std::vector<Precedence>>> table_smalltalk;

/*
|     | $   | id  | lit | (   | )   | .   | ;   | :=  | :   | [   | #   | +   | -   | *   | /   | //  | %   | &   | \|  | === | !== | ==  | !=  | <   | >   | <=  | >=  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| $   |     | p   | p   | p   | x   | p   | p   | x   | x   | x   | {2} | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| id  | r   | r   | r   | x   | r   | r   | r   | e   | e   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| lit | r   | r   | r   | x   | r   | r   | r   | x   | x   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| (   | r   | p   | p   | p   | e   | x   | x   | x   | x   | x   | {2} | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| )   | r   | x   | x   | x   | r   | r   | r   | x   | x   | x   | x   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| .   | r   | p   | p   | p   | x   | r   | p   | x   | x   | x   | {2} | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| ;   | x   | e   | x   | x   | x   | x   | x   | x   | x   | x   | x   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   | e   |
| :=  | r   | p   | p   | p   | r   | r   | p   | x   | x   | x   | {2} | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| :   | r   | p   | p   | p   | r   | r   | r   | x   | x   | f   | {2} | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| [   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   |
| #   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   |
| +   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| \-  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| *   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| /   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| //  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| %   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| &   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| \|  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| === | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| !== | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| ==  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| !=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| <   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| >   | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| <=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |
| >=  | r   | {1} | p   | p   | r   | r   | r   | x   | x   | x   | {2} | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   | r   |

|     | $   | id  | lit | (   | )   | .   | ;   | :=  | :   | [   | #   | +   | -   | *   | /   | //  | %   | &   | \|  | === | !== | ==  | !=  | <   | >   | <=  | >=  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| {1} | p   | p   | p   | p   | p   | p   | p   | p   | r   | x   | x   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   | p   |
| {2} | x   | x   | x   | f   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   | x   |

*/

const std::vector<Precedence> operator_identifier{
    /* $ */ Precedence::PushStop, /* id */ Precedence::PushStop,  /* lit */ Precedence::PushStop, /* ( */ Precedence::PushStop,  /* ) */ Precedence::PushStop,  /* . */ Precedence::PushStop,
    /* ; */ Precedence::PushStop, /* := */ Precedence::PushStop,  /* : */ {Precedence::Reduce},   /* [ */ Precedence::Error,     /* # */ Precedence::Error,     /* + */ Precedence::PushStop,
    /* - */ Precedence::PushStop, /* * */ Precedence::PushStop,   /* / */ Precedence::PushStop,   /* // */ Precedence::PushStop, /* % */ Precedence::PushStop,  /* & */ Precedence::PushStop,
    /* , */ Precedence::PushStop, /* === */ Precedence::PushStop, /* !== */ Precedence::PushStop, /* == */ Precedence::PushStop, /* != */ Precedence::PushStop, /* < */ Precedence::PushStop,
    /* > */ Precedence::PushStop, /* <= */ Precedence::PushStop,  /* >= */ Precedence::PushStop};
    
const std::vector<Precedence> constant_array{/* $ */ Precedence::Error,   /* id */ Precedence::Error, /* lit */ Precedence::Error, /* ( */ Precedence::Function, /* ) */ Precedence::Error,
                                             /* . */ Precedence::Error,   /* ; */ Precedence::Error,  /* := */ Precedence::Error,  /* : */ Precedence::Error,    /* [ */ Precedence::Error,
                                             /* # */ Precedence::Error,   /* + */ Precedence::Error,  /* - */ Precedence::Error,   /* * */ Precedence::Error,    /* / */ Precedence::Error,
                                             /* // */ Precedence::Error,  /* % */ Precedence::Error,  /* & */ Precedence::Error,   /* , */ Precedence::Error,    /* === */ Precedence::Error,
                                             /* !== */ Precedence::Error, /* == */ Precedence::Error, /* != */ Precedence::Error,  /* < */ Precedence::Error,    /* > */ Precedence::Error,
                                             /* <= */ Precedence::Error,  /* >= */ Precedence::Error};

const std::vector<std::vector<std::vector<Precedence>>> table_smalltalk{
    /* $     ===================================================================== */
    {/* $ */ {Precedence::End},        /* id */ {Precedence::PushStop}, /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Error},
     /* . */ {Precedence::PushStop},   /* ; */ {Precedence::PushStop},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,           /* + */ {Precedence::PushStop},  /* - */ {Precedence::PushStop},   /* * */ {Precedence::PushStop}, /* / */ {Precedence::PushStop},
     /* // */ {Precedence::PushStop},  /* % */ {Precedence::PushStop},  /* & */ {Precedence::PushStop},   /* , */ {Precedence::PushStop}, /* === */ {Precedence::PushStop},
     /* !== */ {Precedence::PushStop}, /* == */ {Precedence::PushStop}, /* != */ {Precedence::PushStop},  /* < */ {Precedence::PushStop}, /* > */ {Precedence::PushStop},
     /* <= */ {Precedence::PushStop},  /* >= */ {Precedence::PushStop}},

    /* id   ===================================================================== */
    {/* $ */ {Precedence::Reduce}, /* id */ {Precedence::Reduce},  /* lit */ {Precedence::Reduce}, /* ( */ {Precedence::Error},   /* ) */ {Precedence::Reduce},  /* . */ {Precedence::Reduce},
     /* ; */ {Precedence::Reduce}, /* := */ {Precedence::Push},    /* : */ {Precedence::Push},     /* [ */ {Precedence::Error},   /* # */ {Precedence::Error},   /* + */ {Precedence::Reduce},
     /* - */ {Precedence::Reduce}, /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},   /* // */ {Precedence::Reduce}, /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},
     /* , */ {Precedence::Reduce}, /* === */ {Precedence::Reduce}, /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce}, /* < */ {Precedence::Reduce},
     /* > */ {Precedence::Reduce}, /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* lit  ===================================================================== */
    {/* $ */ {Precedence::Reduce}, /* id */ {Precedence::Reduce},  /* lit */ {Precedence::Reduce}, /* ( */ {Precedence::Error},   /* ) */ {Precedence::Reduce},  /* . */ {Precedence::Reduce},
     /* ; */ {Precedence::Reduce}, /* := */ {Precedence::Error},   /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},   /* # */ {Precedence::Error},   /* + */ {Precedence::Reduce},
     /* - */ {Precedence::Reduce}, /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},   /* // */ {Precedence::Reduce}, /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},
     /* , */ {Precedence::Reduce}, /* === */ {Precedence::Reduce}, /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce}, /* < */ {Precedence::Reduce},
     /* > */ {Precedence::Reduce}, /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* (    ===================================================================== */
    {/* $ */ {Precedence::Reduce},     /* id */ {Precedence::PushStop}, /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Push},
     /* . */ {Precedence::Error},      /* ; */ {Precedence::Error},     /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,           /* + */ {Precedence::PushStop},  /* - */ {Precedence::PushStop},   /* * */ {Precedence::PushStop}, /* / */ {Precedence::PushStop},
     /* // */ {Precedence::PushStop},  /* % */ {Precedence::PushStop},  /* & */ {Precedence::PushStop},   /* , */ {Precedence::PushStop}, /* === */ {Precedence::PushStop},
     /* !== */ {Precedence::PushStop}, /* == */ {Precedence::PushStop}, /* != */ {Precedence::PushStop},  /* < */ {Precedence::PushStop}, /* > */ {Precedence::PushStop},
     /* <= */ {Precedence::PushStop},  /* >= */ {Precedence::PushStop}},

    /* )    ===================================================================== */
    {/* $ */ {Precedence::Reduce}, /* id */ {Precedence::Error},   /* lit */ {Precedence::Error},  /* ( */ {Precedence::Error},   /* ) */ {Precedence::Reduce},  /* . */ {Precedence::Reduce},
     /* ; */ {Precedence::Reduce}, /* := */ {Precedence::Error},   /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},   /* # */ {Precedence::Error},   /* + */ {Precedence::Reduce},
     /* - */ {Precedence::Reduce}, /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},   /* // */ {Precedence::Reduce}, /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},
     /* , */ {Precedence::Reduce}, /* === */ {Precedence::Reduce}, /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce}, /* < */ {Precedence::Reduce},
     /* > */ {Precedence::Reduce}, /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* .    ===================================================================== */
    {/* $ */ {Precedence::Reduce},     /* id */ {Precedence::PushStop}, /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Error},
     /* . */ {Precedence::Reduce},     /* ; */ {Precedence::PushStop},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,           /* + */ {Precedence::PushStop},  /* - */ {Precedence::PushStop},   /* * */ {Precedence::PushStop}, /* / */ {Precedence::PushStop},
     /* // */ {Precedence::PushStop},  /* % */ {Precedence::PushStop},  /* & */ {Precedence::PushStop},   /* , */ {Precedence::PushStop}, /* === */ {Precedence::PushStop},
     /* !== */ {Precedence::PushStop}, /* == */ {Precedence::PushStop}, /* != */ {Precedence::PushStop},  /* < */ {Precedence::PushStop}, /* > */ {Precedence::PushStop},
     /* <= */ {Precedence::PushStop},  /* >= */ {Precedence::PushStop}},

    /* ;    ===================================================================== */
    {/* $ */ {Precedence::Error}, /* id */ {Precedence::Push},  /* lit */ {Precedence::Error}, /* ( */ {Precedence::Error}, /* ) */ {Precedence::Error}, /* . */ {Precedence::Error},
     /* ; */ {Precedence::Error}, /* := */ {Precedence::Error}, /* : */ {Precedence::Error},   /* [ */ {Precedence::Error}, /* # */ {Precedence::Error}, /* + */ {Precedence::Push},
     /* - */ {Precedence::Push},  /* * */ {Precedence::Push},   /* / */ {Precedence::Push},    /* // */ {Precedence::Push}, /* % */ {Precedence::Push},  /* & */ {Precedence::Push},
     /* , */ {Precedence::Push},  /* === */ {Precedence::Push}, /* !== */ {Precedence::Push},  /* == */ {Precedence::Push}, /* != */ {Precedence::Push}, /* < */ {Precedence::Push},
     /* > */ {Precedence::Push},  /* <= */ {Precedence::Push},  /* >= */ {Precedence::Push}},

    /* :=   ===================================================================== */
    {/* $ */ {Precedence::Reduce},     /* id */ {Precedence::PushStop}, /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},     /* ; */ {Precedence::PushStop},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,           /* + */ {Precedence::PushStop},  /* - */ {Precedence::PushStop},   /* * */ {Precedence::PushStop}, /* / */ {Precedence::PushStop},
     /* // */ {Precedence::PushStop},  /* % */ {Precedence::PushStop},  /* & */ {Precedence::PushStop},   /* , */ {Precedence::PushStop}, /* === */ {Precedence::PushStop},
     /* !== */ {Precedence::PushStop}, /* == */ {Precedence::PushStop}, /* != */ {Precedence::PushStop},  /* < */ {Precedence::PushStop}, /* > */ {Precedence::PushStop},
     /* <= */ {Precedence::PushStop},  /* >= */ {Precedence::PushStop}},

    /* :    ===================================================================== */
    {/* $ */ {Precedence::Reduce},     /* id */ {Precedence::PushStop}, /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},     /* ; */ {Precedence::Reduce},    /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Function},
     /* # */ constant_array,           /* + */ {Precedence::PushStop},  /* - */ {Precedence::PushStop},   /* * */ {Precedence::PushStop}, /* / */ {Precedence::PushStop},
     /* // */ {Precedence::PushStop},  /* % */ {Precedence::PushStop},  /* & */ {Precedence::PushStop},   /* , */ {Precedence::PushStop}, /* === */ {Precedence::PushStop},
     /* !== */ {Precedence::PushStop}, /* == */ {Precedence::PushStop}, /* != */ {Precedence::PushStop},  /* < */ {Precedence::PushStop}, /* > */ {Precedence::PushStop},
     /* <= */ {Precedence::PushStop},  /* >= */ {Precedence::PushStop}},

    /* [    ===================================================================== */
    {/* $ */ {Precedence::Error}, /* id */ {Precedence::Error},  /* lit */ {Precedence::Error}, /* ( */ {Precedence::Error},  /* ) */ {Precedence::Error},  /* . */ {Precedence::Error},
     /* ; */ {Precedence::Error}, /* := */ {Precedence::Error},  /* : */ {Precedence::Error},   /* [ */ {Precedence::Error},  /* # */ {Precedence::Error},  /* + */ {Precedence::Error},
     /* - */ {Precedence::Error}, /* * */ {Precedence::Error},   /* / */ {Precedence::Error},   /* // */ {Precedence::Error}, /* % */ {Precedence::Error},  /* & */ {Precedence::Error},
     /* , */ {Precedence::Error}, /* === */ {Precedence::Error}, /* !== */ {Precedence::Error}, /* == */ {Precedence::Error}, /* != */ {Precedence::Error}, /* < */ {Precedence::Error},
     /* > */ {Precedence::Error}, /* <= */ {Precedence::Error},  /* >= */ {Precedence::Error}},

    /* #    ===================================================================== */
    {/* $ */ {Precedence::Error}, /* id */ {Precedence::Error},  /* lit */ {Precedence::Error}, /* ( */ {Precedence::Error},  /* ) */ {Precedence::Error},  /* . */ {Precedence::Error},
     /* ; */ {Precedence::Error}, /* := */ {Precedence::Error},  /* : */ {Precedence::Error},   /* [ */ {Precedence::Error},  /* # */ {Precedence::Error},  /* + */ {Precedence::Error},
     /* - */ {Precedence::Error}, /* * */ {Precedence::Error},   /* / */ {Precedence::Error},   /* // */ {Precedence::Error}, /* % */ {Precedence::Error},  /* & */ {Precedence::Error},
     /* , */ {Precedence::Error}, /* === */ {Precedence::Error}, /* !== */ {Precedence::Error}, /* == */ {Precedence::Error}, /* != */ {Precedence::Error}, /* < */ {Precedence::Error},
     /* > */ {Precedence::Error}, /* <= */ {Precedence::Error},  /* >= */ {Precedence::Error}},

    /* +    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* \-   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* *    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* /    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* //   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* %    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* &    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* \,   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* ===  ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* !==  ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* ==   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* !=   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* <    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* >    ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* <=   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},

    /* >=   ===================================================================== */
    {/* $ */ {Precedence::Reduce},   /* id */ operator_identifier,  /* lit */ {Precedence::PushStop}, /* ( */ {Precedence::PushStop}, /* ) */ {Precedence::Reduce},
     /* . */ {Precedence::Reduce},   /* ; */ {Precedence::Reduce},  /* := */ {Precedence::Error},     /* : */ {Precedence::Error},    /* [ */ {Precedence::Error},
     /* # */ constant_array,         /* + */ {Precedence::Reduce},  /* - */ {Precedence::Reduce},     /* * */ {Precedence::Reduce},   /* / */ {Precedence::Reduce},
     /* // */ {Precedence::Reduce},  /* % */ {Precedence::Reduce},  /* & */ {Precedence::Reduce},     /* , */ {Precedence::Reduce},   /* === */ {Precedence::Reduce},
     /* !== */ {Precedence::Reduce}, /* == */ {Precedence::Reduce}, /* != */ {Precedence::Reduce},    /* < */ {Precedence::Reduce},   /* > */ {Precedence::Reduce},
     /* <= */ {Precedence::Reduce},  /* >= */ {Precedence::Reduce}},
};
