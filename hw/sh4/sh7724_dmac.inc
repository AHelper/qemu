/*
 * SH7724 Direct Memory Access Controller
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
 */

#ifdef HEADER
#define SH7724_DMAC_BASE         0xnnnnnnnn
#define SH7724_DMAC_END          0xnnnnnnnn+m

/* Register Name */
#define SH7724_DMAC_<Reg>       SH7724_DMAC_BASE+0xn
#define SH7724_DMAC_<Reg>_S     1|2|4

struct SH7724DMAC
{
  // Variables
};

#endif /* HEADER */

#ifdef DATA
struct SH7724DMAC dmac;
#endif /* DATA */

#ifdef HANDLER
#define S (s->dmac)
// Case: register, size, read, write
CASE(SH7724_DMAC_<Reg>, SH7724_DMAC_<Reg>_S,
  // Read code, returning value
,
  // Write operation
)
     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
  // Set SH7724DMAC variables to their startup values in s->dmac
#endif /* INIT */