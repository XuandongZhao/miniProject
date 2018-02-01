/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "F:/ISE_workspace/CPU/MulticycleCPU/SignExtend.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
static unsigned int ng4[] = {1U, 0U};
static unsigned int ng5[] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
static unsigned int ng6[] = {2U, 0U};
static int ng7[] = {16, 0};



static void Initial_7_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(7, ng0);

LAB2:    xsi_set_current_line(8, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1608);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB1:    return;
}

static void Always_10_1(char *t0)
{
    char t7[224];
    char t8[8];
    char t20[136];
    char t21[8];
    char t22[8];
    char t23[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;

LAB0:    t1 = (t0 + 2776U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(10, ng0);
    t2 = (t0 + 3096);
    *((int *)t2) = 1;
    t3 = (t0 + 2808);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(10, ng0);

LAB5:    xsi_set_current_line(11, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 2, t4, 2);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t6 == 1)
        goto LAB11;

LAB12:
LAB14:
LAB13:    xsi_set_current_line(15, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t21, 0, 8);
    t2 = (t21 + 4);
    t4 = (t3 + 4);
    t12 = *((unsigned int *)t3);
    t13 = (t12 >> 0);
    *((unsigned int *)t21) = t13;
    t14 = *((unsigned int *)t4);
    t15 = (t14 >> 0);
    *((unsigned int *)t2) = t15;
    t16 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t16 & 65535U);
    t17 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t17 & 65535U);
    t9 = ((char*)((ng7)));
    t10 = (t0 + 1048U);
    t11 = *((char **)t10);
    memset(t23, 0, 8);
    t10 = (t23 + 4);
    t18 = (t11 + 4);
    t24 = *((unsigned int *)t11);
    t25 = (t24 >> 15);
    t26 = (t25 & 1);
    *((unsigned int *)t23) = t26;
    t27 = *((unsigned int *)t18);
    t28 = (t27 >> 15);
    t29 = (t28 & 1);
    *((unsigned int *)t10) = t29;
    xsi_vlog_mul_concat(t22, 16, 1, t9, 1U, t23, 1);
    xsi_vlogtype_concat(t8, 32, 32, 2U, t22, 16, t21, 16);
    t19 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t19, t8, 0, 0, 32, 0LL);

LAB15:    goto LAB2;

LAB7:    xsi_set_current_line(12, ng0);
    t9 = (t0 + 1048U);
    t10 = *((char **)t9);
    memset(t8, 0, 8);
    t9 = (t8 + 4);
    t11 = (t10 + 4);
    t12 = *((unsigned int *)t10);
    t13 = (t12 >> 6);
    *((unsigned int *)t8) = t13;
    t14 = *((unsigned int *)t11);
    t15 = (t14 >> 6);
    *((unsigned int *)t9) = t15;
    t16 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t16 & 31U);
    t17 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t17 & 31U);
    t18 = ((char*)((ng3)));
    xsi_vlogtype_concat(t7, 869, 869, 2U, t18, 864, t8, 5);
    t19 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t19, t7, 0, 0, 32, 0LL);
    goto LAB15;

LAB9:    xsi_set_current_line(13, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    memset(t8, 0, 8);
    t3 = (t8 + 4);
    t9 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t13 = (t12 >> 0);
    *((unsigned int *)t8) = t13;
    t14 = *((unsigned int *)t9);
    t15 = (t14 >> 0);
    *((unsigned int *)t3) = t15;
    t16 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t16 & 65535U);
    t17 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t17 & 65535U);
    t10 = ((char*)((ng5)));
    xsi_vlogtype_concat(t20, 528, 528, 2U, t10, 512, t8, 16);
    t11 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t11, t20, 0, 0, 32, 0LL);
    goto LAB15;

LAB11:    xsi_set_current_line(14, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    memset(t21, 0, 8);
    t3 = (t21 + 4);
    t9 = (t4 + 4);
    t12 = *((unsigned int *)t4);
    t13 = (t12 >> 0);
    *((unsigned int *)t21) = t13;
    t14 = *((unsigned int *)t9);
    t15 = (t14 >> 0);
    *((unsigned int *)t3) = t15;
    t16 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t16 & 65535U);
    t17 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t17 & 65535U);
    t10 = ((char*)((ng7)));
    t11 = (t0 + 1048U);
    t18 = *((char **)t11);
    memset(t23, 0, 8);
    t11 = (t23 + 4);
    t19 = (t18 + 4);
    t24 = *((unsigned int *)t18);
    t25 = (t24 >> 15);
    t26 = (t25 & 1);
    *((unsigned int *)t23) = t26;
    t27 = *((unsigned int *)t19);
    t28 = (t27 >> 15);
    t29 = (t28 & 1);
    *((unsigned int *)t11) = t29;
    xsi_vlog_mul_concat(t22, 16, 1, t10, 1U, t23, 1);
    xsi_vlogtype_concat(t8, 32, 32, 2U, t22, 16, t21, 16);
    t30 = (t0 + 1608);
    xsi_vlogvar_wait_assign_value(t30, t8, 0, 0, 32, 0LL);
    goto LAB15;

}


extern void work_m_00000000001037377081_0967961054_init()
{
	static char *pe[] = {(void *)Initial_7_0,(void *)Always_10_1};
	xsi_register_didat("work_m_00000000001037377081_0967961054", "isim/test_isim_beh.exe.sim/work/m_00000000001037377081_0967961054.didat");
	xsi_register_executes(pe);
}
