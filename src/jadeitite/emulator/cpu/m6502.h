#ifndef JADEITITE_M6502_H
#define JADEITITE_M6502_H

/*============================================================================*/
/*                            MOS 6502 Processor                              */
/*----------------------------------------------------------------------------*/
/* Processor:                                                                 */
/* MOS 65c02 Processor are emulator for processor MOS 65c02 mainly inspired,  */
/* cloned, refined, ... by Fake6502 from Mike Chambers.                       */
/*                                                                            */
/* How to use it:                                                             */
/* TODO                                                                       */
/*============================================================================*/

#include "jadeitite/datatypes.h"

/*============================================================================*/
/*                             MOS 6502 Flags                                 */
/*============================================================================*/

#define M65C02_FLAG_CARRY     0x01
#define M65C02_FLAG_ZERO      0x02
#define M65C02_FLAG_INTERRUPT 0x04
#define M65C02_FLAG_DECIMAL   0x08
#define M65C02_FLAG_BREAK     0x10
#define M65C02_FLAG_CONSTANT  0x20
#define M65C02_FLAG_OVERFLOW  0x40
#define M65C02_FLAG_SIGN      0x80
#define M65C02_BASE_STACK     0x100

/*============================================================================*/
/*                       Processor 6502 Structures                            */
/*============================================================================*/

typedef struct {
  u16 pc; // Program Counter
  u8 sp;  // Stack Pointer
  u8 a;   // Accumulator
  u8 x;   // Register X
  u8 y;   // Register Y
  u8 status;
} m6502_cpu_register;

typedef struct {
  u8 fi2;   // Clock
  u8 rw;    // Read/Write
  u16 a;    // Address bus
  u8 d;     // Data bus
} m6502_cpu_pins;

typedef struct {
  m6502_cpu_register regs;
  m6502_cpu_pins     *pins;

  u8 opcode;
  u16 ea, reladdr;
  u32 clockticks6502, clockgoal6502;
  u8 penalty_op, penalty_address;
  u64 instruction_counter;
  void (*required_process_bus)(m6502_cpu_pins*);
} m6502_cpu;

/*============================================================================*/
/*                              Base Functions                                */
/*============================================================================*/

void m6502_reset(m6502_cpu *p_cpu);
u8 m6502_step(m6502_cpu *p_cpu);

/*============================================================================*/
/*                              Bus Functions                                 */
/*============================================================================*/

u8 m6502_bus_read_data(m6502_cpu *p_cpu, u16 p_address);
void m6502_bus_put_data(m6502_cpu *p_cpu, u16 p_address, u8 p_value);
u16 m6502_bus_read_address(m6502_cpu *p_cpu);
void m6502_bus_put_address(m6502_cpu *p_cpu, u16 p_address);

/*============================================================================*/
/*                           Status Modifier                                  */
/*============================================================================*/

static inline void m6502_set_carry(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_CARRY;
}

static inline void m6502_clear_carry(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_CARRY);
}

static inline void m6502_set_zero(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_ZERO;
}

static inline void m6502_clear_zero(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_ZERO);
}

static inline void m6502_set_interrupt(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_INTERRUPT;
}

static inline void m6502_clear_interrupt(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_INTERRUPT);
}
static inline void m6502_set_decimal(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_DECIMAL;
}

static inline void m6502_clear_decimal(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_DECIMAL);
}

static inline void m6502_set_overflow(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_OVERFLOW;

}
static inline void m6502_clear_overflow(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_OVERFLOW);
}

static inline void m6502_set_sign(m6502_cpu *p_cpu) {
  p_cpu->regs.status |= M65C02_FLAG_SIGN;
}

static inline void m6502_clear_sign(m6502_cpu *p_cpu) {
  p_cpu->regs.status &= (~M65C02_FLAG_SIGN);
}

/*============================================================================*/
/*                           Flag Calculation                                 */
/*============================================================================*/

static inline void m6502_zero_calc(m6502_cpu *p_cpu, u16 p_result) {
  if (p_result & 0x00FF) {
    m6502_clear_zero(p_cpu);
  } else {
    m6502_set_zero(p_cpu);
  }
}

static inline void m6502_sign_calc(m6502_cpu *p_cpu, u16 p_result) {
  if (p_result & 0x0080) {
    m6502_set_sign(p_cpu);
  } else {
    m6502_clear_sign(p_cpu);
  }
}

static inline void m6502_carry_calc(m6502_cpu *p_cpu, u16 p_result) {
  if (p_result & 0xFF00) {
    m6502_set_carry(p_cpu);
  } else {
    m6502_clear_carry(p_cpu);
  }
}

static inline void m6502_overflow_calc(m6502_cpu *p_cpu, u16 p_result, u16 p_accumulator, u16 p_memory) {
  if ((p_result ^ p_accumulator) & (p_result ^ p_memory)) {
    m6502_set_overflow(p_cpu);
  } else {
    m6502_clear_overflow(p_cpu);
  }
}

/*============================================================================*/
/*                                  Address                                   */
/*============================================================================*/

void abso(m6502_cpu *p_cpu);
void absx(m6502_cpu *p_cpu);
void absy(m6502_cpu *p_cpu);
void acc (m6502_cpu *p_cpu);
void imp (m6502_cpu *p_cpu);
void imm (m6502_cpu *p_cpu);
void ind (m6502_cpu *p_cpu);
void indx(m6502_cpu *p_cpu);
void indy(m6502_cpu *p_cpu);
void rel (m6502_cpu *p_cpu);
void zp  (m6502_cpu *p_cpu);
void zpx (m6502_cpu *p_cpu);
void zpy (m6502_cpu *p_cpu);

/*============================================================================*/
/*                                  Opcodes                                   */
/*============================================================================*/

void adc(m6502_cpu *p_cpu);
void and(m6502_cpu *p_cpu);
void asl(m6502_cpu *p_cpu);
void bcc(m6502_cpu *p_cpu);
void bcs(m6502_cpu *p_cpu);
void bit(m6502_cpu *p_cpu);
void bmi(m6502_cpu *p_cpu);
void bne(m6502_cpu *p_cpu);
void brk(m6502_cpu *p_cpu);
void bpl(m6502_cpu *p_cpu);
void bvc(m6502_cpu *p_cpu);
void bvs(m6502_cpu *p_cpu);
void beq(m6502_cpu *p_cpu);
void cmp(m6502_cpu *p_cpu);
void clc(m6502_cpu *p_cpu);
void cpy(m6502_cpu *p_cpu);
void dcp(m6502_cpu *p_cpu);
void iny(m6502_cpu *p_cpu);
void jsr(m6502_cpu *p_cpu);
void eor(m6502_cpu *p_cpu);
void nop(m6502_cpu *p_cpu);
void ora(m6502_cpu *p_cpu);
void rol(m6502_cpu *p_cpu);
void rla(m6502_cpu *p_cpu);
void rra(m6502_cpu *p_cpu);
void rts(m6502_cpu *p_cpu);
void slo(m6502_cpu *p_cpu);
void sre(m6502_cpu *p_cpu);
void php(m6502_cpu *p_cpu);
void plp(m6502_cpu *p_cpu);
void rti(m6502_cpu *p_cpu);
void sty(m6502_cpu *p_cpu);
void clv(m6502_cpu *p_cpu);
void sec(m6502_cpu *p_cpu);
void lsr(m6502_cpu *p_cpu);
void cli(m6502_cpu *p_cpu);
void ror(m6502_cpu *p_cpu);
void sax(m6502_cpu *p_cpu);
void sta(m6502_cpu *p_cpu);
void lax(m6502_cpu *p_cpu);
void pha(m6502_cpu *p_cpu);
void stx(m6502_cpu *p_cpu);
void pla(m6502_cpu *p_cpu);
void lda(m6502_cpu *p_cpu);
void ldx(m6502_cpu *p_cpu);
void ldy(m6502_cpu *p_cpu);
void sei(m6502_cpu *p_cpu);
void jmp(m6502_cpu *p_cpu);
void inc(m6502_cpu *p_cpu);
void txa(m6502_cpu *p_cpu);
void dec(m6502_cpu *p_cpu);
void dey(m6502_cpu *p_cpu);
void txs(m6502_cpu *p_cpu);
void tay(m6502_cpu *p_cpu);
void tax(m6502_cpu *p_cpu);
void tya(m6502_cpu *p_cpu);
void dex(m6502_cpu *p_cpu);
void tsx(m6502_cpu *p_cpu);
void sbc(m6502_cpu *p_cpu);
void cpx(m6502_cpu *p_cpu);
void isb(m6502_cpu *p_cpu);
void sed(m6502_cpu *p_cpu);
void inx(m6502_cpu *p_cpu);
void cld(m6502_cpu *p_cpu);

#define lax nop
#define sax nop
#define dcp nop
#define isb nop
#define slo nop
#define rla nop
#define sre nop
#define rra nop

/*============================================================================*/
/*                         Opcode and Address Tables                          */
/*============================================================================*/

static void (*m6502_address_table[256])() = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 0 */
/* 1 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 1 */
/* 2 */    abso, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 2 */
/* 3 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 3 */
/* 4 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm, abso, abso, abso, abso, /* 4 */
/* 5 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 5 */
/* 6 */     imp, indx,  imp, indx,   zp,   zp,   zp,   zp,  imp,  imm,  acc,  imm,  ind, abso, abso, abso, /* 6 */
/* 7 */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* 7 */
/* 8 */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* 8 */
/* 9 */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, absy, /* 9 */
/* A */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* A */
/* B */     rel, indy,  imp, indy,  zpx,  zpx,  zpy,  zpy,  imp, absy,  imp, absy, absx, absx, absy, absy, /* B */
/* C */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* C */
/* D */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx, /* D */
/* E */     imm, indx,  imm, indx,   zp,   zp,   zp,   zp,  imp,  imm,  imp,  imm, abso, abso, abso, abso, /* E */
/* F */     rel, indy,  imp, indy,  zpx,  zpx,  zpx,  zpx,  imp, absy,  imp, absy, absx, absx, absx, absx  /* F */
};

static void (*m6502_opcode_table[256])() = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |      */
/* 0 */      brk,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  php,  ora,  asl,  nop,  nop,  ora,  asl,  slo, /* 0 */
/* 1 */      bpl,  ora,  nop,  slo,  nop,  ora,  asl,  slo,  clc,  ora,  nop,  slo,  nop,  ora,  asl,  slo, /* 1 */
/* 2 */      jsr,  and,  nop,  rla,  bit,  and,  rol,  rla,  plp,  and,  rol,  nop,  bit,  and,  rol,  rla, /* 2 */
/* 3 */      bmi,  and,  nop,  rla,  nop,  and,  rol,  rla,  sec,  and,  nop,  rla,  nop,  and,  rol,  rla, /* 3 */
/* 4 */      rti,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  pha,  eor,  lsr,  nop,  jmp,  eor,  lsr,  sre, /* 4 */
/* 5 */      bvc,  eor,  nop,  sre,  nop,  eor,  lsr,  sre,  cli,  eor,  nop,  sre,  nop,  eor,  lsr,  sre, /* 5 */
/* 6 */      rts,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  pla,  adc,  ror,  nop,  jmp,  adc,  ror,  rra, /* 6 */
/* 7 */      bvs,  adc,  nop,  rra,  nop,  adc,  ror,  rra,  sei,  adc,  nop,  rra,  nop,  adc,  ror,  rra, /* 7 */
/* 8 */      nop,  sta,  nop,  sax,  sty,  sta,  stx,  sax,  dey,  nop,  txa,  nop,  sty,  sta,  stx,  sax, /* 8 */
/* 9 */      bcc,  sta,  nop,  nop,  sty,  sta,  stx,  sax,  tya,  sta,  txs,  nop,  nop,  sta,  nop,  nop, /* 9 */
/* A */      ldy,  lda,  ldx,  lax,  ldy,  lda,  ldx,  lax,  tay,  lda,  tax,  nop,  ldy,  lda,  ldx,  lax, /* A */
/* B */      bcs,  lda,  nop,  lax,  ldy,  lda,  ldx,  lax,  clv,  lda,  tsx,  lax,  ldy,  lda,  ldx,  lax, /* B */
/* C */      cpy,  cmp,  nop,  dcp,  cpy,  cmp,  dec,  dcp,  iny,  cmp,  dex,  nop,  cpy,  cmp,  dec,  dcp, /* C */
/* D */      bne,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp,  cld,  cmp,  nop,  dcp,  nop,  cmp,  dec,  dcp, /* D */
/* E */      cpx,  sbc,  nop,  isb,  cpx,  sbc,  inc,  isb,  inx,  sbc,  nop,  sbc,  cpx,  sbc,  inc,  isb, /* E */
/* F */      beq,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb,  sed,  sbc,  nop,  isb,  nop,  sbc,  inc,  isb  /* F */
};

static const u32 m6502_tick_table[256] = {
/*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
/* 0 */      7,    6,    2,    8,    3,    3,    5,    5,    3,    2,    2,    2,    4,    4,    6,    6,  /* 0 */
/* 1 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 1 */
/* 2 */      6,    6,    2,    8,    3,    3,    5,    5,    4,    2,    2,    2,    4,    4,    6,    6,  /* 2 */
/* 3 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 3 */
/* 4 */      6,    6,    2,    8,    3,    3,    5,    5,    3,    2,    2,    2,    3,    4,    6,    6,  /* 4 */
/* 5 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 5 */
/* 6 */      6,    6,    2,    8,    3,    3,    5,    5,    4,    2,    2,    2,    5,    4,    6,    6,  /* 6 */
/* 7 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 7 */
/* 8 */      2,    6,    2,    6,    3,    3,    3,    3,    2,    2,    2,    2,    4,    4,    4,    4,  /* 8 */
/* 9 */      2,    6,    2,    6,    4,    4,    4,    4,    2,    5,    2,    5,    5,    5,    5,    5,  /* 9 */
/* A */      2,    6,    2,    6,    3,    3,    3,    3,    2,    2,    2,    2,    4,    4,    4,    4,  /* A */
/* B */      2,    5,    2,    5,    4,    4,    4,    4,    2,    4,    2,    4,    4,    4,    4,    4,  /* B */
/* C */      2,    6,    2,    8,    3,    3,    5,    5,    2,    2,    2,    2,    4,    4,    6,    6,  /* C */
/* D */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* D */
/* E */      2,    6,    2,    8,    3,    3,    5,    5,    2,    2,    2,    2,    4,    4,    6,    6,  /* E */
/* F */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7   /* F */
};

/*============================================================================*/
/*                      6502 Opcodes helper functions                         */
/*============================================================================*/

static inline u16 m6502_opcode_get_value_8(m6502_cpu *p_cpu) {
  if (m6502_address_table[p_cpu->opcode] == acc) return((u16)p_cpu->regs.a);
  else return((u16)m6502_bus_read_data(p_cpu, p_cpu->ea));
}

static inline u16 m6502_opcode_get_value_16(m6502_cpu *p_cpu) {
  return ((u16)m6502_bus_read_data(p_cpu, p_cpu->ea) |
  ((u16)m6502_bus_read_data(p_cpu, p_cpu->ea+1) << 8));
}

static inline void m6502_opcode_put_value_8(m6502_cpu *p_cpu, u16 p_value) {
  if (m6502_address_table[p_cpu->opcode] == acc) p_cpu->regs.a = (u8)(p_value & 0x00FF);
  else m6502_bus_put_data(p_cpu, p_cpu->ea, (p_value & 0x00FF));
}

static inline void m6502_opcode_put_value_16(m6502_cpu *p_cpu, u16 p_value) {
  m6502_bus_put_data(p_cpu, M65C02_BASE_STACK + p_cpu->regs.sp, (p_value >> 8) & 0xFF);
  m6502_bus_put_data(p_cpu, M65C02_BASE_STACK + ((p_cpu->regs.sp - 1) & 0xFF), p_value & 0xFF);
  p_cpu->regs.sp -= 2;
}

static inline void m6502_opcode_save_accumulator(m6502_cpu *p_cpu, u16 p_value) {
  p_cpu->regs.a = p_value & 0x00FF;
}

#endif //JADEITITE_M6502_H
