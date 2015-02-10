/*
 * SH7724 CPG
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
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

#ifdef DATA
struct SH7724CPG cpg;
#endif /* DATA */

#ifdef HANDLER
#define S (s->cpg)
// Case: register, size, read, write
CASE(SH7724_CPG_FRQCRA, SH7724_CPG_FRQCRA_S,
     printf("SH7724_CPG_FRQCRA read\n");
  return (S.stc << 24) | (S.ifc << 20) | (S.sfc << 12) | (S.bfc << 8) | (S.p1fc);
,
  // Handle validation
     printf("FRQCRA got %08X\n", value);
)
     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
     
#endif /* INIT */