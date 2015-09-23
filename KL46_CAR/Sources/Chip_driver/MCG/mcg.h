
#ifndef __MCG_H__
#define __MCG_H__

//==============================INCLUDE==============================//
#include "common.h"

//==============================TYPEDEF==============================//
typedef struct _mcg_div
{
    unsigned char prdiv;        //+1    1-25
    unsigned char vdiv;         //+24   24-55
    unsigned char core_div;     //+1    1-16
    unsigned char bus_div;      //+1    1-8
    unsigned int mcg_mhz;
} _mcg_div_;

typedef enum _clk_opt
{
    MCG_disinit = 0,
    PLL24,
    PLL26,
    PLL30,
    PLL34,
    PLL48,
    PLL39,
    PLL45,
    PLL51,
    PLL72,
    PLL52,
    PLL60,
    PLL68,
    PLL78,
} _clk_opt_;


//==============================PARAMETER==============================//
static const _mcg_div_
PLL_Para[] =
{
    //prdiv, vdiv, core_civ,  bus_civ,  mcg_mhz
    {     0,    0,        0,        0,      8},
    {    15,   24,        0,        0,     24},
    {     7,    2,        0,        1,     26},
    {     7,    6,        0,        1,     30},
    {     7,   10,        0,        1,     34},
    {     7,   24,        0,        1,     48},
    {     7,   15,        0,        2,     39},
    {     7,   21,        0,        2,     45},
    {     7,   27,        0,        2,     51},
    {     3,   12,        0,        2,     72},
    {     3,    2,        0,        3,     52},
    {     3,    6,        0,        3,     60},
    {     3,   10,        0,        3,     68},
    {     3,   15,        0,        2,     78},
};


//==============================FUNCTION==============================//
void MCG_Init(const _clk_opt_ clk_opt);

int PLL_Init(const _clk_opt_ clk_opt);


//==============================END==============================//


#endif /* __MCG_H__ */


