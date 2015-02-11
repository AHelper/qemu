/*
 * SH7720 Realtime Clock
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
 * FUNCTIONS - Static functions
 */

#ifdef HEADER
#define SH7720_RTC_BASE         0xA413FEC0
#define SH7720_RTC_END          SH7720_RTC_BASE+0x24+1

#ifdef BO
#undef BO
#endif
#define BO(x) (SH7720_RTC_BASE+x)

/* 64-Hz counter */
#define SH7720_RTC_R64CNT	SH7720_RTC_BASE+0x0
#define SH7720_RTC_R64CNT_S     1
/* Second counter */
#define SH7720_RTC_RSECCNT	SH7720_RTC_BASE+0x2
#define SH7720_RTC_RSECCNT_S	1
/* Minute counter */
#define SH7720_RTC_RMINCNT	SH7720_RTC_BASE+0x4
#define SH7720_RTC_RMINCNT_S	1
/* Hour counter */
#define SH7720_RTC_RHRCNT	SH7720_RTC_BASE+0x6
#define SH7720_RTC_RHRCNT_S	1
/* Day of week counter */
#define SH7720_RTC_RWKCNT	SH7720_RTC_BASE+0x8
#define SH7720_RTC_RWKCNT_S	1
/* Day counter */
#define SH7720_RTC_RDAYCNT	SH7720_RTC_BASE+0xA
#define SH7720_RTC_RDAYCNT_S	1
/* Month counter */
#define SH7720_RTC_RMONCNT	SH7720_RTC_BASE+0xC
#define SH7720_RTC_RMONCNT_S	1
/* Year counter */
#define SH7720_RTC_RYRCNT	SH7720_RTC_BASE+0xE
#define SH7720_RTC_RYRCNT_S	2
/* Second alarm register */
#define SH7720_RTC_RSECAR	SH7720_RTC_BASE+0x10
#define SH7720_RTC_RSECAR_S	1
/* Minute alarm register */
#define SH7720_RTC_RMINAR	SH7720_RTC_BASE+0x12
#define SH7720_RTC_RMINAR_S	1
/* Hour alarm register */
#define SH7720_RTC_RHRAR	SH7720_RTC_BASE+0x14
#define SH7720_RTC_RHRAR_S	1
/* Day of week alarm register */
#define SH7720_RTC_RWKAR	SH7720_RTC_BASE+0x16
#define SH7720_RTC_RWKAR_S	1
/* Day alarm register */
#define SH7720_RTC_RDAYAR	SH7720_RTC_BASE+0x18
#define SH7720_RTC_RDAYAR_S	1
/* Month alarm register */
#define SH7720_RTC_RMONAR	SH7720_RTC_BASE+0x1A
#define SH7720_RTC_RMONAR_S	1
/* RTC control register 1 */
#define SH7720_RTC_RCR1 	SH7720_RTC_BASE+0x1C
#define SH7720_RTC_RCR1_S	1
/* RTC control register 2 */
#define SH7720_RTC_RCR2 	SH7720_RTC_BASE+0x1E
#define SH7720_RTC_RCR2_S	1
/* Year alarm register */
#define SH7720_RTC_RYRAR	SH7720_RTC_BASE+0x20
#define SH7720_RTC_RYRAR_S	2
/* RTC control register 3 */
#define SH7720_RTC_RCR3 	SH7720_RTC_BASE+0x24
#define SH7720_RTC_RCR3_S	1

struct SH7720RTC
{
  // Variables
  uint8_t carry; // Carry on 64Hz occurred
  uint8_t alarm; // Aalarm flag
  uint8_t carry_int; // Enable interrupt on carry
  uint8_t alarm_int; // Enable interrupt on alarm
  uint8_t periodic; // Periodic interrupt timing
  // 000 - No interrupts
  // 001 - 1/256 sec
  // 010 - 1/64 sec
  // 011 - 1/16 sec
  // 100 - 1/4 sec
  // 101 - 1/2 sec
  // 110 - 1 sec
  // 111 - 2 seconds
  uint8_t periodic_int; // Enable periodic interrupts
  uint8_t crystal; // Enable crystal oscillator
  uint8_t start; // Starts counters (64Hz counter always runs except with RTCEN/crystal)
  uint8_t year_cp; // Enables comparing the year for alarms
  // Counters
  uint8_t cnt_64hz;
  uint8_t cnt_sec;
  uint8_t cnt_min;
  uint8_t cnt_hr;
  uint8_t cnt_wk;
  uint8_t cnt_day;
  uint8_t cnt_mon;
  uint16_t cnt_yr;
  // TODO alarms
  QEMUTimer *rtc_128hz;
};

#undef BO
#endif /* HEADER */

#ifdef DATA
struct SH7720RTC rtc;
#endif /* DATA */

#ifdef HANDLER
#define S (s->rtc)
// Case: register, size, read, write
CASE(SH7720_RTC_R64CNT, SH7720_RTC_R64CNT_S,
  return S.cnt_64hz;
,
  INVALID
)
CASE(SH7720_RTC_RSECCNT, SH7720_RTC_RSECCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RMINCNT, SH7720_RTC_RMINCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RHRCNT, SH7720_RTC_RHRCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RWKCNT,SH7720_RTC_RWKCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RDAYCNT, SH7720_RTC_RDAYCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RMONCNT, SH7720_RTC_RMONCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RYRCNT, SH7720_RTC_RYRCNT_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RSECAR, SH7720_RTC_RSECAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RMINAR, SH7720_RTC_RMINAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RHRAR, SH7720_RTC_RHRAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RWKAR, SH7720_RTC_RWKAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RDAYAR, SH7720_RTC_RDAYAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RMONAR, SH7720_RTC_RMONAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RCR1, SH7720_RTC_RCR1_S,
  // Read code, returning value
  printf("todo SH7720_RTC_RCR1 read\n");
,
  // Write operation
  printf("todo SH7720_RTC_RCR1 write\n");
)
CASE(SH7720_RTC_RCR2, SH7720_RTC_RCR2_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RYRAR, SH7720_RTC_RYRAR_S,
  TODO
,
  TODO
)
CASE(SH7720_RTC_RCR3, SH7720_RTC_RCR3_S,
  TODO
,
  TODO
)

     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
  // Set SH7720RTC variables to their startup values in s->rtc
  s->rtc.rtc_128hz = timer_new_ns(QEMU_CLOCK_REALTIME, sh7720_rtc_timer_expire, s);
  sh7720_rtc_reset(s);
#endif /* INIT */
	       
#ifdef FUNCTIONS
void sh7720_rtc_reset(void *opaque)
{
  SH7305State *s = opaque;
  
  timer_mod(s->rtc.rtc_128hz, qemu_clock_get_ns(QEMU_CLOCK_REALTIME) + 7812500); // 128Hz
}

void sh7720_rtc_timer_expire(void *opaque)
{
  SH7305State *s = opaque;
  uint8_t bit_1hz = s->rtc.cnt_64hz & 0b01000000;
  
  sh7720_rtc_reset(s);
  
  s->rtc.cnt_64hz++;
  
  if(s->rtc.cnt_64hz > 0b1111111)
  {
    s->rtc.carry = 1;
    s->rtc.cnt_64hz = 0;
  
  printf("Timer\n");
  }
  
  if((s->rtc.cnt_64hz & 0b01000000) ^ bit_1hz)
  {
    // Add to seconds, and so on
  }
}
#endif