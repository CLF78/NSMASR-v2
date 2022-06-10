// These defines allow using Gekko instructions in inline assembly

#define dcbz_l(rA, rB) \
opword 0x100007EC | (rA & 0x1F) << 16 | (rB & 0x1F) << 11

#define psq_l(fD, EA, rA, W, I) \
opword 0xE0000000 | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (W & 1) << 15 | (I & 7) << 12 | EA & 0xFFF

#define psq_lu(fD, EA, rA, W, I) \
opword 0xE4000000 | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (W & 1) << 15 | (I & 7) << 12 | EA & 0xFFF

#define psq_lux(fD, rA, rB, W, I) \
opword 0x1000004C | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (rB & 0x1F) << 11 | (W & 1) << 10 | (I & 7) << 7

#define psq_lx(fD, rA, rB, W, I) \
opword 0x1000000C | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (rB & 0x1F) << 11 | (W & 1) << 10 | (I & 7) << 7

#define psq_st(fD, EA, rA, W, I) \
opword 0xF0000000 | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (W & 1) << 15 | (I & 7) << 12 | EA & 0xFFF

#define psq_stu(fD, EA, rA, W, I) \
opword 0xF4000000 | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (W & 1) << 15 | (I & 7) << 12 | EA & 0xFFF

#define psq_stux(fD, rA, rB, W, I) \
opword 0x1000004E | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (rB & 0x1F) << 11 | (W & 1) << 10 | (I & 7) << 7

#define psq_stx(fD, rA, rB, W, I) \
opword 0x1000000E | (fD & 0x1F) << 21 | (rA & 0x1F) << 16 | (rB & 0x1F) << 11 | (W & 1) << 10 | (I & 7) << 7

#define ps_abs(fD, fB, Rc) \
opword 0x10000210 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_add(fD, fA, fB, Rc) \
opword 0x1000002A | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_cmpo0(crD, fA, fB) \
opword 0x10000040 | (crD & 7) << 23 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11

#define ps_cmpo1(crD, fA, fB) \
opword 0x100000C0 | (crD & 7) << 23 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11

#define ps_cmpu0(crD, fA, fB) \
opword 0x10000000 | (crD & 7) << 23 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11

#define ps_cmpu1(crD, fA, fB) \
opword 0x10000080 | (crD & 7) << 23 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11

#define ps_div(fD, fA, fB, Rc) \
opword 0x10000024 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_madd(fD, fA, fC, fB, Rc) \
opword 0x1000003A | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_madds0(fD, fA, fC, fB, Rc) \
opword 0x1000001C | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_madds1(fD, fA, fC, fB, Rc) \
opword 0x1000001E | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_merge00(fD, fA, fB, Rc) \
opword 0x10000420 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_merge01(fD, fA, fB, Rc) \
opword 0x10000460 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_merge10(fD, fA, fB, Rc) \
opword 0x100004A0 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_merge11(fD, fA, fB, Rc) \
opword 0x100004E0 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_mr(fD, fB, Rc) \
opword 0x10000090 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_msub(fD, fA, fC, fB, Rc) \
opword 0x10000038 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_mul(fD, fA, fC) \
opword 0x10000032 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fC & 0x1F << 6) | Rc & 1

#define ps_muls0(fD, fA, fC) \
opword 0x10000018 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fC & 0x1F << 6) | Rc & 1

#define ps_muls1(fD, fA, fC) \
opword 0x1000001A | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fC & 0x1F << 6) | Rc & 1

#define ps_nabs(fD, fB, Rc) \
opword 0x10000110 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_neg(fD, fB, Rc) \
opword 0x10000050 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_nmadd(fD, fA, fC, fB, Rc) \
opword 0x1000003E | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_nmsub(fD, fA, fC, fB, Rc) \
opword 0x1000003C | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_res(fD, fB, Rc) \
opword 0x10000030 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_rsqrte(fD, fB, Rc) \
opword 0x10000034 | (fD & 0x1F) << 21 | (fB & 0x1F) << 11 | Rc & 1

#define ps_sel(fD, fA, fC, fB, Rc) \
opword 0x1000002E | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_sub(fD, fA, fB, Rc) \
opword 0x10000028 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | Rc & 1

#define ps_sum0(fD, fA, fC, fB, Rc) \
opword 0x10000014 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1

#define ps_sum1(fD, fA, fC, fB, Rc) \
opword 0x10000016 | (fD & 0x1F) << 21 | (fA & 0x1F) << 16 | (fB & 0x1F) << 11 | (fC & 0x1F) << 6 | Rc & 1
