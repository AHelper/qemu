/*
 * SH7724 Compare Match Timer
 * 
 * HEADER - Defines and struct
 * DATA - Struct instantiation
 * HANDLER - Read/write hander (addr, size, and value are available)
 * INIT - Peripheral initialization
 */

#ifdef HEADER
#define SH7724_CMT_BASE         0xA44A0000
#define SH7724_CMT_END          SH7724_CMT_END+0x68+4

/* Compare match timer start register */
#define SH7724_CMT_CMSTR       SH7724_CMT_BASE+0x0
#define SH7724_CMT_CMSTR_S     2
/* Compare match timer control/status register */
#define SH7724_CMT_CMCSR       SH7724_CMT_BASE+0x60
#define SH7724_CMT_CMCSR_S     2
/* Compare match timer counter */
#define SH7724_CMT_CMCNT       SH7724_CMT_BASE+0x64
#define SH7724_CMT_CMCNT_S     4
/* Compare match timer constant register */
#define SH7724_CMT_CMCOR       SH7724_CMT_BASE+0x68
#define SH7724_CMT_CMCOR_S     4

struct SH7724CMT
{
  // Variables
  uint8_t counting; // Enables counting
  uint8_t matched; // 1 if CMCNT and CMCOR matched
  uint8_t overflowed; // 1 if CMCNT overflowed
  uint8_t cnt_size; // 0 for 16-bit counter, 1 for 32-bit counter
  uint8_t continuous; // 0 for single-shot, 1 for free-running (continuous)
  uint8_t wakeup; // 1 if standby modes can get canceled (wakeup MPU)
  uint8_t interrupt; // 1 for enabling internal interrupt request
  uint8_t clock; // Set clock input to CMCNT
  // 100 - RCLK/8
  // 101 - RCLK/32
  // 110 - RCLK/128
  // All other values are prohibited
  uint32_t reg_cmcnt;
  uint32_t reg_cmcor;
  QEMUTimer *timer;
};

#endif /* HEADER */

#ifdef DATA
struct SH7724CMT cmt;
#endif /* DATA */

#ifdef HANDLER
#define S (s->cmt)
// Case: register, size, read, write
CASE(SH7724_CMT_CMSTR, SH7724_CMT_CMSTR_S,
  TODO
  return (S.counting << 5);
,
  TODO
  if(value & 0x20)
  {
    S.counting = 1;
    sh7724_cmt_reset(s);
  } else {
    S.counting = 0;
    sh7724_cmt_stop(s);
  }
)
CASE(SH7724_CMT_CMCSR, SH7724_CMT_CMCSR_S,
//   printf("SH7724_CMT_CMCSR: %04X\n", (S.matched << 15) | (S.overflowed << 14) | (S.cnt_size << 9) | 
//       (S.continuous << 8) | (S.wakeup << 7) | (S.interrupt << 5) |
//       (S.clock));
  return (S.matched << 15) | (S.overflowed << 14) | (S.cnt_size << 9) | 
      (S.continuous << 8) | (S.wakeup << 7) | (S.interrupt << 5) |
      (S.clock);
,
  TODO
  if((value & (1 << 15)) == 0)
    S.matched = 0;
  
  if((value & (1 << 14)) == 0)
    S.overflowed = 0;
  
  S.cnt_size = (value >> 9) & 0b1;
  S.continuous = (value >> 8) & 0b1;
  S.wakeup = (value >> 7) & 0b1;
  
  if(!S.cnt_size)
  {
    S.reg_cmcnt &= 0xFFFF;
    S.reg_cmcor &= 0xFFFF; // I think that's wrong, maybe just the compare cares?
  }
  
  switch((value >> 4) & 0b11)
  {
    case 0b01:
    case 0b11:
      printf("CMT: Bad CMR\n");
      break;
    case 0b00:
      S.interrupt = 0;
      break;
    case 0b10:
      S.interrupt = 1;
      break;
  }
  
  switch(value & 0b111)
  {
    case 0b100:
    case 0b101:
    case 0b110:
      S.clock = value & 0b111;
      break;
    default:
      printf("CMT: Bad CKS\n");
      break;
  }
)
CASE(SH7724_CMT_CMCNT, SH7724_CMT_CMCNT_S,
  TODO
  return S.reg_cmcnt;
,
  TODO
  if(S.cnt_size)
    S.reg_cmcnt = value;
  else
    S.reg_cmcnt = value & (uint32_t)0xFFFF;
)
CASE(SH7724_CMT_CMCOR, SH7724_CMT_CMCOR_S,
  TODO
  return S.reg_cmcor;
,
  TODO
  if(S.cnt_size)
    S.reg_cmcor = value;
  else
    S.reg_cmcor = value & 0xFFFF;
)
     
#undef S
#endif /* HANDLER */
     
#ifdef INIT
  // Set SH7724CMT variables to their startup values in s->cmt
  s->cmt.clock = 0b100;
  
  s->cmt.timer = timer_new_ns(QEMU_CLOCK_REALTIME, sh7724_cmt_timer_expire, s);
#endif /* INIT */

#ifdef FUNCTIONS
static void sh7724_cmt_reset(void *opaque)
{
  SH7305State *s = opaque;
  
  switch(s->cmt.clock)
  {
    case 0b100:
      timer_mod(s->cmt.timer, qemu_clock_get_ns(QEMU_CLOCK_REALTIME) + 244648); // ~4kHz
      break;
    case 0b101:
      timer_mod(s->cmt.timer, qemu_clock_get_ns(QEMU_CLOCK_REALTIME) + 978593); // ~1kHz
      break;
    case 0b110:
      timer_mod(s->cmt.timer, qemu_clock_get_ns(QEMU_CLOCK_REALTIME) + 3914373); // ~255Hz
      break;
    default:
      printf("sh7724 cmt has invalid clock %d\n", s->cmt.clock);
  }
}

static void sh7724_cmt_stop(void *opaque)
{
  SH7305State *s = opaque;
  
  timer_del(s->cmt.timer);
}

static void sh7724_cmt_timer_expire(void *opaque)
{
  SH7305State *s = opaque;
  
  s->cmt.reg_cmcnt++;
  
  if(s->cmt.reg_cmcnt == 0) // Not sure, docs aren't clear
    s->cmt.overflowed = 1;
  
  if(s->cmt.reg_cmcnt == s->cmt.reg_cmcor)
  {
    s->cmt.matched = 1;
    s->cmt.reg_cmcnt = 0;
    
    if(s->cmt.interrupt)
      printf("sh7724 cmt TODO fire interrupt\n");
    
    if(s->cmt.continuous)
      sh7724_cmt_reset(s);
  }
  else
  {
    sh7724_cmt_reset(s);
  }
}
#endif /* FUNCTIONS */