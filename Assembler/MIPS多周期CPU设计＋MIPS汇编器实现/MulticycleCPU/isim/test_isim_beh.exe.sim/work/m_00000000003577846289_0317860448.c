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
static const char *ng0 = "F:/ISE_workspace/CPU/MulticycleCPU/ROM.v";
static const char *ng1 = "my_rom_data.coe";
static int ng2[] = {0, 0};
static int ng3[] = {31, 0};
static int ng4[] = {24, 0};
static int ng5[] = {1, 0};
static int ng6[] = {23, 0};
static int ng7[] = {16, 0};
static int ng8[] = {2, 0};
static int ng9[] = {15, 0};
static int ng10[] = {8, 0};
static int ng11[] = {3, 0};
static int ng12[] = {7, 0};



static void Initial_8_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;

LAB0:    t1 = (t0 + 2848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(8, ng0);

LAB4:    xsi_set_current_line(9, ng0);
    t2 = (t0 + 2656);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB5;

LAB1:    return;
LAB5:    xsi_set_current_line(10, ng0);
    t2 = (t0 + 1928);
    t3 = (t0 + 1368U);
    t4 = *((char **)t3);
    xsi_vlogfile_readmemb(ng1, 0, t2, 1, *((unsigned int *)t4), 0, 0);
    xsi_set_current_line(11, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1768);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    goto LAB1;

}

static void Always_13_1(char *t0)
{
    char t14[8];
    char t23[8];
    char t24[8];
    char t25[8];
    char t48[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    char *t13;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    unsigned int t32;
    int t33;
    char *t34;
    unsigned int t35;
    int t36;
    int t37;
    char *t38;
    unsigned int t39;
    int t40;
    int t41;
    unsigned int t42;
    int t43;
    unsigned int t44;
    unsigned int t45;
    int t46;
    int t47;

LAB0:    t1 = (t0 + 3096U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(13, ng0);
    t2 = (t0 + 3416);
    *((int *)t2) = 1;
    t3 = (t0 + 3128);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(14, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(14, ng0);

LAB8:    xsi_set_current_line(15, ng0);
    t11 = (t0 + 1928);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t15 = (t0 + 1928);
    t16 = (t15 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 1928);
    t19 = (t18 + 64U);
    t20 = *((char **)t19);
    t21 = (t0 + 1208U);
    t22 = *((char **)t21);
    xsi_vlog_generic_get_array_select_value(t14, 8, t13, t17, t20, 2, 1, t22, 32, 2);
    t21 = (t0 + 1768);
    t26 = (t0 + 1768);
    t27 = (t26 + 72U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng3)));
    t30 = ((char*)((ng4)));
    xsi_vlog_convert_partindices(t23, t24, t25, ((int*)(t28)), 2, t29, 32, 1, t30, 32, 1);
    t31 = (t23 + 4);
    t32 = *((unsigned int *)t31);
    t33 = (!(t32));
    t34 = (t24 + 4);
    t35 = *((unsigned int *)t34);
    t36 = (!(t35));
    t37 = (t33 && t36);
    t38 = (t25 + 4);
    t39 = *((unsigned int *)t38);
    t40 = (!(t39));
    t41 = (t37 && t40);
    if (t41 == 1)
        goto LAB9;

LAB10:    xsi_set_current_line(16, ng0);
    t2 = (t0 + 1928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1928);
    t11 = (t5 + 72U);
    t12 = *((char **)t11);
    t13 = (t0 + 1928);
    t15 = (t13 + 64U);
    t16 = *((char **)t15);
    t17 = (t0 + 1208U);
    t18 = *((char **)t17);
    t17 = ((char*)((ng5)));
    memset(t23, 0, 8);
    xsi_vlog_unsigned_add(t23, 32, t18, 32, t17, 32);
    xsi_vlog_generic_get_array_select_value(t14, 8, t4, t12, t16, 2, 1, t23, 32, 2);
    t19 = (t0 + 1768);
    t20 = (t0 + 1768);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t26 = ((char*)((ng6)));
    t27 = ((char*)((ng7)));
    xsi_vlog_convert_partindices(t24, t25, t48, ((int*)(t22)), 2, t26, 32, 1, t27, 32, 1);
    t28 = (t24 + 4);
    t6 = *((unsigned int *)t28);
    t33 = (!(t6));
    t29 = (t25 + 4);
    t7 = *((unsigned int *)t29);
    t36 = (!(t7));
    t37 = (t33 && t36);
    t30 = (t48 + 4);
    t8 = *((unsigned int *)t30);
    t40 = (!(t8));
    t41 = (t37 && t40);
    if (t41 == 1)
        goto LAB11;

LAB12:    xsi_set_current_line(17, ng0);
    t2 = (t0 + 1928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1928);
    t11 = (t5 + 72U);
    t12 = *((char **)t11);
    t13 = (t0 + 1928);
    t15 = (t13 + 64U);
    t16 = *((char **)t15);
    t17 = (t0 + 1208U);
    t18 = *((char **)t17);
    t17 = ((char*)((ng8)));
    memset(t23, 0, 8);
    xsi_vlog_unsigned_add(t23, 32, t18, 32, t17, 32);
    xsi_vlog_generic_get_array_select_value(t14, 8, t4, t12, t16, 2, 1, t23, 32, 2);
    t19 = (t0 + 1768);
    t20 = (t0 + 1768);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t26 = ((char*)((ng9)));
    t27 = ((char*)((ng10)));
    xsi_vlog_convert_partindices(t24, t25, t48, ((int*)(t22)), 2, t26, 32, 1, t27, 32, 1);
    t28 = (t24 + 4);
    t6 = *((unsigned int *)t28);
    t33 = (!(t6));
    t29 = (t25 + 4);
    t7 = *((unsigned int *)t29);
    t36 = (!(t7));
    t37 = (t33 && t36);
    t30 = (t48 + 4);
    t8 = *((unsigned int *)t30);
    t40 = (!(t8));
    t41 = (t37 && t40);
    if (t41 == 1)
        goto LAB13;

LAB14:    xsi_set_current_line(18, ng0);
    t2 = (t0 + 1928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1928);
    t11 = (t5 + 72U);
    t12 = *((char **)t11);
    t13 = (t0 + 1928);
    t15 = (t13 + 64U);
    t16 = *((char **)t15);
    t17 = (t0 + 1208U);
    t18 = *((char **)t17);
    t17 = ((char*)((ng11)));
    memset(t23, 0, 8);
    xsi_vlog_unsigned_add(t23, 32, t18, 32, t17, 32);
    xsi_vlog_generic_get_array_select_value(t14, 8, t4, t12, t16, 2, 1, t23, 32, 2);
    t19 = (t0 + 1768);
    t20 = (t0 + 1768);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t26 = ((char*)((ng12)));
    t27 = ((char*)((ng2)));
    xsi_vlog_convert_partindices(t24, t25, t48, ((int*)(t22)), 2, t26, 32, 1, t27, 32, 1);
    t28 = (t24 + 4);
    t6 = *((unsigned int *)t28);
    t33 = (!(t6));
    t29 = (t25 + 4);
    t7 = *((unsigned int *)t29);
    t36 = (!(t7));
    t37 = (t33 && t36);
    t30 = (t48 + 4);
    t8 = *((unsigned int *)t30);
    t40 = (!(t8));
    t41 = (t37 && t40);
    if (t41 == 1)
        goto LAB15;

LAB16:    goto LAB7;

LAB9:    t42 = *((unsigned int *)t25);
    t43 = (t42 + 0);
    t44 = *((unsigned int *)t23);
    t45 = *((unsigned int *)t24);
    t46 = (t44 - t45);
    t47 = (t46 + 1);
    xsi_vlogvar_assign_value(t21, t14, t43, *((unsigned int *)t24), t47);
    goto LAB10;

LAB11:    t9 = *((unsigned int *)t48);
    t43 = (t9 + 0);
    t10 = *((unsigned int *)t24);
    t32 = *((unsigned int *)t25);
    t46 = (t10 - t32);
    t47 = (t46 + 1);
    xsi_vlogvar_assign_value(t19, t14, t43, *((unsigned int *)t25), t47);
    goto LAB12;

LAB13:    t9 = *((unsigned int *)t48);
    t43 = (t9 + 0);
    t10 = *((unsigned int *)t24);
    t32 = *((unsigned int *)t25);
    t46 = (t10 - t32);
    t47 = (t46 + 1);
    xsi_vlogvar_assign_value(t19, t14, t43, *((unsigned int *)t25), t47);
    goto LAB14;

LAB15:    t9 = *((unsigned int *)t48);
    t43 = (t9 + 0);
    t10 = *((unsigned int *)t24);
    t32 = *((unsigned int *)t25);
    t46 = (t10 - t32);
    t47 = (t46 + 1);
    xsi_vlogvar_assign_value(t19, t14, t43, *((unsigned int *)t25), t47);
    goto LAB16;

}


extern void work_m_00000000003577846289_0317860448_init()
{
	static char *pe[] = {(void *)Initial_8_0,(void *)Always_13_1};
	xsi_register_didat("work_m_00000000003577846289_0317860448", "isim/test_isim_beh.exe.sim/work/m_00000000003577846289_0317860448.didat");
	xsi_register_executes(pe);
}
