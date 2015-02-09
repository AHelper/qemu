/*
 * SH7724 CPG
 */

#ifdef HEADER
#define SH7724_CPG_BASE		0xA4150000
#define SH7724_CPG_END		0xA4150060+4

#ifdef BO
#undef BO
#endif
#define BO(x) (SH7724_CPG_BASE+x)

/* Frequency Control Register A */
#define SH7724_CPG_FRQCRA	BO(0x0)
#define SH7724_CPG_FRQCRA_S	4
/* Frequency Control Register B */
#define SH7724_CPG_FRQCRB	BO(0x04)
#define SH7724_CPG_FRQCRB_S	4
/* PLL control register */
#define SH7724_CPG_PLLCR	BO(0x24)
#define SH7724_CPG_PLLCR_S	4
/* FLL Multiplication register */
#define SH7724_CPG_FLLFRQ	BO(0x50)
#define SH7724_CPG_FLLFRQ_S	4
/* Frequency change status register */
#define SH7724_CPG_LSTATUS	BO(0x60)
#define SH7724_CPG_LSTATUS_S	4

struct SH7724CPG
{
  uint8_t stc;
  uint8_t ifc;
  uint8_t sfc;
  uint8_t bfc;
  uint8_t p1fc;
  uint8_t m1fc;
};

#endif /* HEADER */

#ifdef HANDLER
CASE(sh7724_CPG_FRQCRA)
#ifdef READ
  return (cpg.stc << 24) | (cpg.ifc << 20) | (cpg.sfc << 12) | (cpg.bfc << 8) | (cpg.p1fc);
#else
  // Handle validation
#endif