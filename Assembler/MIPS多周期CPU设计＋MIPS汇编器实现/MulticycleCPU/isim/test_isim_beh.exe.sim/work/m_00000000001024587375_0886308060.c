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
static const char *ng0 = "F:/ISE_workspace/CPU/MulticycleCPU/ALU.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {0U, 0U};
static unsigned int ng4[] = {1U, 0U};
static unsigned int ng5[] = {2U, 0U};
static unsigned int ng6[] = {3U, 0U};
static unsigned int ng7[] = {4U, 0U};
static unsigned int ng8[] = {5U, 0U};
static unsigned int ng9[] = {6U, 0U};
static unsigned int ng10[] = {7U, 0U};



static void Initial_8_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(8, ng0);

LAB2:    xsi_set_current_line(9, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1928);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB1:    return;
}

static void Cont_11_1(char *t0)
{
    char t3[8];
    char t4[8];
    char *t1;
    char *t2;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    unsigned int t29;
    unsigned int t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    char *t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;

LAB0:    t1 = (t0 + 3096U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(11, ng0);
    t2 = (t0 + 1928);
    t5 = (t2 + 56U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t7);
    t9 = (~(t8));
    t10 = *((unsigned int *)t6);
    t11 = (t10 & t9);
    t12 = (t11 & 4294967295U);
    if (t12 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t7) != 0)
        goto LAB6;

LAB7:    t14 = (t4 + 4);
    t15 = *((unsigned int *)t4);
    t16 = *((unsigned int *)t14);
    t17 = (t15 || t16);
    if (t17 > 0)
        goto LAB8;

LAB9:    t19 = *((unsigned int *)t4);
    t20 = (~(t19));
    t21 = *((unsigned int *)t14);
    t22 = (t20 || t21);
    if (t22 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t14) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t23, 8);

LAB16:    t24 = (t0 + 3760);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    memset(t28, 0, 8);
    t29 = 1U;
    t30 = t29;
    t31 = (t3 + 4);
    t32 = *((unsigned int *)t3);
    t29 = (t29 & t32);
    t33 = *((unsigned int *)t31);
    t30 = (t30 & t33);
    t34 = (t28 + 4);
    t35 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t35 | t29);
    t36 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t36 | t30);
    xsi_driver_vfirst_trans(t24, 0, 0);
    t37 = (t0 + 3664);
    *((int *)t37) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t13 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t13) = 1;
    goto LAB7;

LAB8:    t18 = ((char*)((ng1)));
    goto LAB9;

LAB10:    t23 = ((char*)((ng2)));
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 32, t18, 32, t23, 32);
    goto LAB16;

LAB14:    memcpy(t3, t18, 8);
    goto LAB16;

}

static void Always_12_2(char *t0)
{
    char t10[8];
    char t11[8];
    char t12[8];
    char t63[8];
    char t95[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    char *t30;
    unsigned int t31;
    int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    char *t67;
    char *t68;
    char *t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    char *t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    int t87;
    int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    char *t99;
    char *t100;
    char *t101;
    unsigned int t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    char *t109;
    char *t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    char *t123;

LAB0:    t1 = (t0 + 3344U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(12, ng0);
    t2 = (t0 + 3680);
    *((int *)t2) = 1;
    t3 = (t0 + 3376);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(12, ng0);

LAB5:    xsi_set_current_line(13, ng0);
    t4 = (t0 + 1368U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t4, 3);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
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

LAB18:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng10)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 3, t2, 3);
    if (t6 == 1)
        goto LAB21;

LAB22:
LAB24:
LAB23:    xsi_set_current_line(22, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1928);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);

LAB25:    goto LAB2;

LAB7:    xsi_set_current_line(14, ng0);
    t7 = (t0 + 1048U);
    t8 = *((char **)t7);
    t7 = (t0 + 1208U);
    t9 = *((char **)t7);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_add(t10, 32, t8, 32, t9, 32);
    t7 = (t0 + 1928);
    xsi_vlogvar_assign_value(t7, t10, 0, 0, 32);
    goto LAB25;

LAB9:    xsi_set_current_line(15, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_minus(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 1928);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB25;

LAB11:    xsi_set_current_line(16, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t12, 0, 8);
    t3 = (t4 + 4);
    if (*((unsigned int *)t3) != 0)
        goto LAB27;

LAB26:    t8 = (t7 + 4);
    if (*((unsigned int *)t8) != 0)
        goto LAB27;

LAB30:    if (*((unsigned int *)t4) < *((unsigned int *)t7))
        goto LAB28;

LAB29:    memset(t11, 0, 8);
    t13 = (t12 + 4);
    t14 = *((unsigned int *)t13);
    t15 = (~(t14));
    t16 = *((unsigned int *)t12);
    t17 = (t16 & t15);
    t18 = (t17 & 1U);
    if (t18 != 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t13) != 0)
        goto LAB33;

LAB34:    t20 = (t11 + 4);
    t21 = *((unsigned int *)t11);
    t22 = *((unsigned int *)t20);
    t23 = (t21 || t22);
    if (t23 > 0)
        goto LAB35;

LAB36:    t25 = *((unsigned int *)t11);
    t26 = (~(t25));
    t27 = *((unsigned int *)t20);
    t28 = (t26 || t27);
    if (t28 > 0)
        goto LAB37;

LAB38:    if (*((unsigned int *)t20) > 0)
        goto LAB39;

LAB40:    if (*((unsigned int *)t11) > 0)
        goto LAB41;

LAB42:    memcpy(t10, t29, 8);

LAB43:    t30 = (t0 + 1928);
    xsi_vlogvar_assign_value(t30, t10, 0, 0, 32);
    goto LAB25;

LAB13:    xsi_set_current_line(17, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_rshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 1928);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB25;

LAB15:    xsi_set_current_line(18, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_lshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 1928);
    xsi_vlogvar_assign_value(t3, t10, 0, 0, 32);
    goto LAB25;

LAB17:    xsi_set_current_line(19, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t7);
    t16 = (t14 | t15);
    *((unsigned int *)t10) = t16;
    t3 = (t4 + 4);
    t8 = (t7 + 4);
    t9 = (t10 + 4);
    t17 = *((unsigned int *)t3);
    t18 = *((unsigned int *)t8);
    t21 = (t17 | t18);
    *((unsigned int *)t9) = t21;
    t22 = *((unsigned int *)t9);
    t23 = (t22 != 0);
    if (t23 == 1)
        goto LAB44;

LAB45:
LAB46:    t20 = (t0 + 1928);
    xsi_vlogvar_assign_value(t20, t10, 0, 0, 32);
    goto LAB25;

LAB19:    xsi_set_current_line(20, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t7);
    t16 = (t14 & t15);
    *((unsigned int *)t10) = t16;
    t3 = (t4 + 4);
    t8 = (t7 + 4);
    t9 = (t10 + 4);
    t17 = *((unsigned int *)t3);
    t18 = *((unsigned int *)t8);
    t21 = (t17 | t18);
    *((unsigned int *)t9) = t21;
    t22 = *((unsigned int *)t9);
    t23 = (t22 != 0);
    if (t23 == 1)
        goto LAB47;

LAB48:
LAB49:    t20 = (t0 + 1928);
    xsi_vlogvar_assign_value(t20, t10, 0, 0, 32);
    goto LAB25;

LAB21:    xsi_set_current_line(21, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    memset(t10, 0, 8);
    t3 = (t10 + 4);
    t7 = (t4 + 4);
    t14 = *((unsigned int *)t4);
    t15 = (~(t14));
    *((unsigned int *)t10) = t15;
    *((unsigned int *)t3) = 0;
    if (*((unsigned int *)t7) != 0)
        goto LAB51;

LAB50:    t22 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t22 & 4294967295U);
    t23 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t23 & 4294967295U);
    t8 = (t0 + 1208U);
    t9 = *((char **)t8);
    t25 = *((unsigned int *)t10);
    t26 = *((unsigned int *)t9);
    t27 = (t25 & t26);
    *((unsigned int *)t11) = t27;
    t8 = (t10 + 4);
    t13 = (t9 + 4);
    t19 = (t11 + 4);
    t28 = *((unsigned int *)t8);
    t31 = *((unsigned int *)t13);
    t33 = (t28 | t31);
    *((unsigned int *)t19) = t33;
    t34 = *((unsigned int *)t19);
    t35 = (t34 != 0);
    if (t35 == 1)
        goto LAB52;

LAB53:
LAB54:    t29 = (t0 + 1048U);
    t30 = *((char **)t29);
    t29 = (t0 + 1208U);
    t53 = *((char **)t29);
    memset(t12, 0, 8);
    t29 = (t12 + 4);
    t54 = (t53 + 4);
    t55 = *((unsigned int *)t53);
    t56 = (~(t55));
    *((unsigned int *)t12) = t56;
    *((unsigned int *)t29) = 0;
    if (*((unsigned int *)t54) != 0)
        goto LAB56;

LAB55:    t61 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t61 & 4294967295U);
    t62 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t62 & 4294967295U);
    t64 = *((unsigned int *)t30);
    t65 = *((unsigned int *)t12);
    t66 = (t64 & t65);
    *((unsigned int *)t63) = t66;
    t67 = (t30 + 4);
    t68 = (t12 + 4);
    t69 = (t63 + 4);
    t70 = *((unsigned int *)t67);
    t71 = *((unsigned int *)t68);
    t72 = (t70 | t71);
    *((unsigned int *)t69) = t72;
    t73 = *((unsigned int *)t69);
    t74 = (t73 != 0);
    if (t74 == 1)
        goto LAB57;

LAB58:
LAB59:    t96 = *((unsigned int *)t11);
    t97 = *((unsigned int *)t63);
    t98 = (t96 | t97);
    *((unsigned int *)t95) = t98;
    t99 = (t11 + 4);
    t100 = (t63 + 4);
    t101 = (t95 + 4);
    t102 = *((unsigned int *)t99);
    t103 = *((unsigned int *)t100);
    t104 = (t102 | t103);
    *((unsigned int *)t101) = t104;
    t105 = *((unsigned int *)t101);
    t106 = (t105 != 0);
    if (t106 == 1)
        goto LAB60;

LAB61:
LAB62:    t123 = (t0 + 1928);
    xsi_vlogvar_assign_value(t123, t95, 0, 0, 32);
    goto LAB25;

LAB27:    t9 = (t12 + 4);
    *((unsigned int *)t12) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB29;

LAB28:    *((unsigned int *)t12) = 1;
    goto LAB29;

LAB31:    *((unsigned int *)t11) = 1;
    goto LAB34;

LAB33:    t19 = (t11 + 4);
    *((unsigned int *)t11) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB34;

LAB35:    t24 = ((char*)((ng2)));
    goto LAB36;

LAB37:    t29 = ((char*)((ng1)));
    goto LAB38;

LAB39:    xsi_vlog_unsigned_bit_combine(t10, 32, t24, 32, t29, 32);
    goto LAB43;

LAB41:    memcpy(t10, t24, 8);
    goto LAB43;

LAB44:    t25 = *((unsigned int *)t10);
    t26 = *((unsigned int *)t9);
    *((unsigned int *)t10) = (t25 | t26);
    t13 = (t4 + 4);
    t19 = (t7 + 4);
    t27 = *((unsigned int *)t13);
    t28 = (~(t27));
    t31 = *((unsigned int *)t4);
    t32 = (t31 & t28);
    t33 = *((unsigned int *)t19);
    t34 = (~(t33));
    t35 = *((unsigned int *)t7);
    t36 = (t35 & t34);
    t37 = (~(t32));
    t38 = (~(t36));
    t39 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t39 & t37);
    t40 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t40 & t38);
    goto LAB46;

LAB47:    t25 = *((unsigned int *)t10);
    t26 = *((unsigned int *)t9);
    *((unsigned int *)t10) = (t25 | t26);
    t13 = (t4 + 4);
    t19 = (t7 + 4);
    t27 = *((unsigned int *)t4);
    t28 = (~(t27));
    t31 = *((unsigned int *)t13);
    t33 = (~(t31));
    t34 = *((unsigned int *)t7);
    t35 = (~(t34));
    t37 = *((unsigned int *)t19);
    t38 = (~(t37));
    t32 = (t28 & t33);
    t36 = (t35 & t38);
    t39 = (~(t32));
    t40 = (~(t36));
    t41 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t41 & t39);
    t42 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t42 & t40);
    t43 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t43 & t39);
    t44 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t44 & t40);
    goto LAB49;

LAB51:    t16 = *((unsigned int *)t10);
    t17 = *((unsigned int *)t7);
    *((unsigned int *)t10) = (t16 | t17);
    t18 = *((unsigned int *)t3);
    t21 = *((unsigned int *)t7);
    *((unsigned int *)t3) = (t18 | t21);
    goto LAB50;

LAB52:    t37 = *((unsigned int *)t11);
    t38 = *((unsigned int *)t19);
    *((unsigned int *)t11) = (t37 | t38);
    t20 = (t10 + 4);
    t24 = (t9 + 4);
    t39 = *((unsigned int *)t10);
    t40 = (~(t39));
    t41 = *((unsigned int *)t20);
    t42 = (~(t41));
    t43 = *((unsigned int *)t9);
    t44 = (~(t43));
    t45 = *((unsigned int *)t24);
    t46 = (~(t45));
    t32 = (t40 & t42);
    t36 = (t44 & t46);
    t47 = (~(t32));
    t48 = (~(t36));
    t49 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t49 & t47);
    t50 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t50 & t48);
    t51 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t51 & t47);
    t52 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t52 & t48);
    goto LAB54;

LAB56:    t57 = *((unsigned int *)t12);
    t58 = *((unsigned int *)t54);
    *((unsigned int *)t12) = (t57 | t58);
    t59 = *((unsigned int *)t29);
    t60 = *((unsigned int *)t54);
    *((unsigned int *)t29) = (t59 | t60);
    goto LAB55;

LAB57:    t75 = *((unsigned int *)t63);
    t76 = *((unsigned int *)t69);
    *((unsigned int *)t63) = (t75 | t76);
    t77 = (t30 + 4);
    t78 = (t12 + 4);
    t79 = *((unsigned int *)t30);
    t80 = (~(t79));
    t81 = *((unsigned int *)t77);
    t82 = (~(t81));
    t83 = *((unsigned int *)t12);
    t84 = (~(t83));
    t85 = *((unsigned int *)t78);
    t86 = (~(t85));
    t87 = (t80 & t82);
    t88 = (t84 & t86);
    t89 = (~(t87));
    t90 = (~(t88));
    t91 = *((unsigned int *)t69);
    *((unsigned int *)t69) = (t91 & t89);
    t92 = *((unsigned int *)t69);
    *((unsigned int *)t69) = (t92 & t90);
    t93 = *((unsigned int *)t63);
    *((unsigned int *)t63) = (t93 & t89);
    t94 = *((unsigned int *)t63);
    *((unsigned int *)t63) = (t94 & t90);
    goto LAB59;

LAB60:    t107 = *((unsigned int *)t95);
    t108 = *((unsigned int *)t101);
    *((unsigned int *)t95) = (t107 | t108);
    t109 = (t11 + 4);
    t110 = (t63 + 4);
    t111 = *((unsigned int *)t109);
    t112 = (~(t111));
    t113 = *((unsigned int *)t11);
    t114 = (t113 & t112);
    t115 = *((unsigned int *)t110);
    t116 = (~(t115));
    t117 = *((unsigned int *)t63);
    t118 = (t117 & t116);
    t119 = (~(t114));
    t120 = (~(t118));
    t121 = *((unsigned int *)t101);
    *((unsigned int *)t101) = (t121 & t119);
    t122 = *((unsigned int *)t101);
    *((unsigned int *)t101) = (t122 & t120);
    goto LAB62;

}


extern void work_m_00000000001024587375_0886308060_init()
{
	static char *pe[] = {(void *)Initial_8_0,(void *)Cont_11_1,(void *)Always_12_2};
	xsi_register_didat("work_m_00000000001024587375_0886308060", "isim/test_isim_beh.exe.sim/work/m_00000000001024587375_0886308060.didat");
	xsi_register_executes(pe);
}
