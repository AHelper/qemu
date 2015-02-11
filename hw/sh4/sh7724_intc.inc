/*
 * SH7724 Interrupt Controller
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
 */

#ifdef HEADER
#define SH7724_INTC_BASE         0xnnnnnnnn
#define SH7724_INTC_END          0xnnnnnnnn+m

/* Register Name */
#define SH7724_INTC_<Reg>       SH7724_INTC_BASE+0xn
#define SH7724_INTC_<Reg>_S     1|2|4

struct SH7724INTC
{
  // Variables
};

#endif /* HEADER */

#ifdef DATA
struct SH7724INTC intc;
#endif /* DATA */

#ifdef HANDLER
#define S (s->intc)
// Case: register, size, read, write
CASE(SH7724_INTC_<Reg>, SH7724_INTC_<Reg>_S,
  // Read code, returning value
,
  // Write operation
)
     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
  // Set SH7724INTC variables to their startup values in s->intc
#endif /* INIT */