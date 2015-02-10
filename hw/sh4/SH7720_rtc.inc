/*
 * SH7720 Realtime Clock
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
 */

#ifdef HEADER
#define SH7720_RTC_BASE         0xnnnnnnnn
#define SH7720_RTC_END          0xnnnnnnnn+m

#ifdef BO
#undef BO
#endif
#define BO(x) (SH7720_RTC_BASE+x)

/* Register Name */
#define SH7720_RTC_<Reg>       BO(0xn)
#define SH7720_RTC_<Reg>_S     1|2|4

struct SH<MPU#>RTC
{
  // Variables
};

#endif /* HEADER */

#ifdef DATA
struct SH7720RTC rtc;
#endif /* DATA */

#ifdef HANDLER
#define S (s->rtc)
// Case: register, size, read, write
CASE(SH7720_RTC_<Reg>, SH7720_RTC_<Reg>_S,
  // Read code, returning value
,
  // Write operation
)
     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
  // Set SH7720RTC variables to their startup values in s->rtc
#endif /* INIT */