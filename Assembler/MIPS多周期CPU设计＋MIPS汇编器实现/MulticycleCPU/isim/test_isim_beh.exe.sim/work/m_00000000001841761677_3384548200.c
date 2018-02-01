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
static const char *ng0 = "F:/ISE_workspace/CPU/MulticycleCPU/NextState.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {7U, 0U};
static unsigned int ng4[] = {6U, 0U};
static unsigned int ng5[] = {52U, 0U};
static unsigned int ng6[] = {5U, 0U};
static unsigned int ng7[] = {2U, 0U};
static unsigned int ng8[] = {3U, 0U};
static unsigned int ng9[] = {49U, 0U};
static unsigned int ng10[] = {4U, 0U};



static void Always_15_0(char *t0)
{
    char t9[8];
    char t19[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    int t16;
    char *t17;
    char *t18;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    char *t31;
    char *t32;

LAB0:    t1 = (t0 + 3616U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(15, ng0);
    t2 = (t0 + 3936);
    *((int *)t2) = 1;
    t3 = (t0 + 3648);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(15, ng0);

LAB5:    xsi_set_current_line(16, ng0);
    t4 = (t0 + 2136U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t4, 3);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng8)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng10)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB21;

LAB22:
LAB24:
LAB23:    xsi_set_current_line(37, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2696);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);

LAB25:    goto LAB2;

LAB7:    xsi_set_current_line(17, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t0 + 2696);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 3);
    goto LAB25;

LAB9:    xsi_set_current_line(18, ng0);

LAB26:    xsi_set_current_line(19, ng0);
    t3 = (t0 + 2296U);
    t4 = *((char **)t3);
    memset(t9, 0, 8);
    t3 = (t9 + 4);
    t7 = (t4 + 4);
    t10 = *((unsigned int *)t4);
    t11 = (t10 >> 3);
    *((unsigned int *)t9) = t11;
    t12 = *((unsigned int *)t7);
    t13 = (t12 >> 3);
    *((unsigned int *)t3) = t13;
    t14 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t14 & 7U);
    t15 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t15 & 7U);

LAB27:    t8 = ((char*)((ng3)));
    t16 = xsi_vlog_unsigned_case_compare(t9, 3, t8, 3);
    if (t16 == 1)
        goto LAB28;

LAB29:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t9, 3, t2, 3);
    if (t6 == 1)
        goto LAB30;

LAB31:
LAB33:
LAB32:    xsi_set_current_line(25, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 2696);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);

LAB34:    goto LAB25;

LAB11:    xsi_set_current_line(28, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 2696);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB25;

LAB13:    xsi_set_current_line(29, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 2696);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB25;

LAB15:    xsi_set_current_line(30, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2696);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB25;

LAB17:    xsi_set_current_line(31, ng0);

LAB43:    xsi_set_current_line(32, ng0);
    t3 = (t0 + 2296U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng9)));
    memset(t19, 0, 8);
    t7 = (t4 + 4);
    t8 = (t3 + 4);
    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t3);
    t12 = (t10 ^ t11);
    t13 = *((unsigned int *)t7);
    t14 = *((unsigned int *)t8);
    t15 = (t13 ^ t14);
    t20 = (t12 | t15);
    t21 = *((unsigned int *)t7);
    t22 = *((unsigned int *)t8);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB47;

LAB44:    if (t23 != 0)
        goto LAB46;

LAB45:    *((unsigned int *)t19) = 1;

LAB47:    t18 = (t19 + 4);
    t26 = *((unsigned int *)t18);
    t27 = (~(t26));
    t28 = *((unsigned int *)t19);
    t29 = (t28 & t27);
    t30 = (t29 != 0);
    if (t30 > 0)
        goto LAB48;

LAB49:    xsi_set_current_line(33, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2696);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);

LAB50:    goto LAB25;

LAB19:    xsi_set_current_line(35, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 2696);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB25;

LAB21:    xsi_set_current_line(36, ng0);
    t3 = ((char*)((ng1)));
    t4 = (t0 + 2696);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    goto LAB25;

LAB28:    xsi_set_current_line(20, ng0);
    t17 = ((char*)((ng1)));
    t18 = (t0 + 2696);
    xsi_vlogvar_assign_value(t18, t17, 0, 0, 3);
    goto LAB34;

LAB30:    xsi_set_current_line(21, ng0);

LAB35:    xsi_set_current_line(22, ng0);
    t3 = (t0 + 2296U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng5)));
    memset(t19, 0, 8);
    t7 = (t4 + 4);
    t8 = (t3 + 4);
    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t3);
    t12 = (t10 ^ t11);
    t13 = *((unsigned int *)t7);
    t14 = *((unsigned int *)t8);
    t15 = (t13 ^ t14);
    t20 = (t12 | t15);
    t21 = *((unsigned int *)t7);
    t22 = *((unsigned int *)t8);
    t23 = (t21 | t22);
    t24 = (~(t23));
    t25 = (t20 & t24);
    if (t25 != 0)
        goto LAB39;

LAB36:    if (t23 != 0)
        goto LAB38;

LAB37:    *((unsigned int *)t19) = 1;

LAB39:    t18 = (t19 + 4);
    t26 = *((unsigned int *)t18);
    t27 = (~(t26));
    t28 = *((unsigned int *)t19);
    t29 = (t28 & t27);
    t30 = (t29 != 0);
    if (t30 > 0)
        goto LAB40;

LAB41:    xsi_set_current_line(23, ng0);
    t2 = ((char*)((ng7)));
    t3 = (t0 + 2696);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);

LAB42:    goto LAB34;

LAB38:    t17 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t17) = 1;
    goto LAB39;

LAB40:    xsi_set_current_line(22, ng0);
    t31 = ((char*)((ng6)));
    t32 = (t0 + 2696);
    xsi_vlogvar_assign_value(t32, t31, 0, 0, 3);
    goto LAB42;

LAB46:    t17 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t17) = 1;
    goto LAB47;

LAB48:    xsi_set_current_line(32, ng0);
    t31 = ((char*)((ng10)));
    t32 = (t0 + 2696);
    xsi_vlogvar_assign_value(t32, t31, 0, 0, 3);
    goto LAB50;

}


extern void work_m_00000000001841761677_3384548200_init()
{
	static char *pe[] = {(void *)Always_15_0};
	xsi_register_didat("work_m_00000000001841761677_3384548200", "isim/test_isim_beh.exe.sim/work/m_00000000001841761677_3384548200.didat");
	xsi_register_executes(pe);
}
