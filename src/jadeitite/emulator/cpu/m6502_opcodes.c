#include "m6502.h"

/*============================================================================*/
/*                                  Opcodes                                   */
/*============================================================================*/

void adc(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value = m6502_opcode_get_value_8(p_cpu);
  const u16 l_result = (u16)p_cpu->regs.a + l_value + (u16)(p_cpu->regs.status & M65C02_FLAG_CARRY);

  m6502_carry_calc(p_cpu, l_result);
  m6502_zero_calc(p_cpu, l_result);
  m6502_overflow_calc(p_cpu, l_result, p_cpu->regs.a, l_value);
  m6502_sign_calc(p_cpu, l_result);

  m6502_opcode_save_accumulator(p_cpu, l_result);
}

void and(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value = m6502_opcode_get_value_8(p_cpu);
  const u16 l_result = (u16)p_cpu->regs.a & l_value;

  m6502_zero_calc(p_cpu, l_result);
  m6502_sign_calc(p_cpu, l_result);

  m6502_opcode_save_accumulator(p_cpu, l_result);
}

void asl(m6502_cpu *p_cpu) {
  const u16 l_value = m6502_opcode_get_value_8(p_cpu);
  const u16 l_result = l_value << 1;

  m6502_carry_calc(p_cpu, l_result);
  m6502_zero_calc(p_cpu, l_result);
  m6502_sign_calc(p_cpu, l_result);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void bcc(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_CARRY) == 0) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void bcs(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_CARRY) == M65C02_FLAG_CARRY) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void beq(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_ZERO) == M65C02_FLAG_ZERO) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void bit(m6502_cpu *p_cpu) {
  const u16 l_value = m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.a & l_value;

  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  p_cpu->regs.status = (p_cpu->regs.status & 0x3F) | (u8)(l_value & 0xC0);
}

void bmi(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_SIGN) == M65C02_FLAG_SIGN) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void bne(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_ZERO) == 0) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void bpl(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_SIGN) == 0) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void brk(m6502_cpu *p_cpu) {
  p_cpu->regs.pc++;
  m6502_opcode_put_value_16(p_cpu, p_cpu->regs.pc); //push next instruction address onto stack
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.status | M65C02_FLAG_BREAK); //push CPU status to stack
  m6502_set_interrupt(p_cpu); //set interrupt flag
  p_cpu->regs.pc = (u16)m6502_bus_read_data(p_cpu, 0xFFFE) | ((u16)m6502_bus_read_data(p_cpu, 0xFFFF) << 8);
}

void bvc(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_OVERFLOW) == 0) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void bvs(m6502_cpu *p_cpu) {
  if ((p_cpu->regs.status & M65C02_FLAG_OVERFLOW) == M65C02_FLAG_OVERFLOW) {
    const u16 l_oldpc = p_cpu->regs.pc;
    p_cpu->regs.pc += p_cpu->reladdr;
    if ((l_oldpc & 0xFF00) != (p_cpu->regs.pc & 0xFF00)) p_cpu->clockticks6502 += 2; //check if jump crossed a page boundary
    else p_cpu->clockticks6502++;
  }
}

void clc(m6502_cpu *p_cpu) {
  m6502_clear_carry(p_cpu);
}

void cld(m6502_cpu *p_cpu) {
  m6502_clear_decimal(p_cpu);
}

void cli(m6502_cpu *p_cpu) {
  m6502_clear_interrupt(p_cpu);
}

void clv(m6502_cpu *p_cpu) {
  m6502_clear_overflow(p_cpu);
}

void cmp(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.a - l_value;

  if (p_cpu->regs.a >= (u8)(l_value & 0x00FF)) m6502_set_carry(p_cpu);
  else m6502_clear_carry(p_cpu);
  if (p_cpu->regs.a == (u8)(l_value & 0x00FF)) m6502_set_zero(p_cpu);
  else m6502_clear_zero(p_cpu);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);
}

void cpx(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.x - l_value;

  if (p_cpu->regs.x >= (u8)(l_value & 0x00FF)) m6502_set_carry(p_cpu);
  else m6502_clear_carry(p_cpu);
  if (p_cpu->regs.x == (u8)(l_value & 0x00FF)) m6502_set_zero(p_cpu);
  else m6502_clear_zero(p_cpu);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);
}

void cpy(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.y - l_value;

  if (p_cpu->regs.y >= (u8)(l_value & 0x00FF)) m6502_set_carry(p_cpu);
  else m6502_clear_carry(p_cpu);
  if (p_cpu->regs.y == (u8)(l_value & 0x00FF)) m6502_set_zero(p_cpu);
  else m6502_clear_zero(p_cpu);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);
}

void dec(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =l_value - 1;

  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void dex(m6502_cpu *p_cpu) {
  p_cpu->regs.x--;

  m6502_zero_calc(p_cpu, p_cpu->regs.x);
  m6502_sign_calc(p_cpu, p_cpu->regs.x);
}

void dey(m6502_cpu *p_cpu) {
  p_cpu->regs.y--;

  m6502_zero_calc(p_cpu, p_cpu->regs.y);
  m6502_sign_calc(p_cpu, p_cpu->regs.y);
}

void eor(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.a ^ l_value;

  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_save_accumulator(p_cpu, l_result);
}

void inc(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =l_value + 1;

  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void inx(m6502_cpu *p_cpu) {
  p_cpu->regs.x++;

  m6502_zero_calc(p_cpu, p_cpu->regs.x);
  m6502_sign_calc(p_cpu, p_cpu->regs.x);
}

void iny(m6502_cpu *p_cpu) {
  p_cpu->regs.y++;

  m6502_zero_calc(p_cpu, p_cpu->regs.y);
  m6502_sign_calc(p_cpu, p_cpu->regs.y);
}

void jmp(m6502_cpu *p_cpu) {
  p_cpu->regs.pc = p_cpu->ea;
}

void jsr(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_16(p_cpu, p_cpu->regs.pc - 1);
  p_cpu->regs.pc = p_cpu->ea;
}

void lda(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  p_cpu->regs.a = (u8)(l_value & 0x00FF);

  m6502_zero_calc(p_cpu, p_cpu->regs.a);
  m6502_sign_calc(p_cpu, p_cpu->regs.a);
}

void ldx(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  p_cpu->regs.x = (u8)(l_value & 0x00FF);

  m6502_zero_calc(p_cpu, p_cpu->regs.x);
  m6502_sign_calc(p_cpu, p_cpu->regs.x);
}

void ldy(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  p_cpu->regs.y = (u8)(l_value & 0x00FF);

  m6502_zero_calc(p_cpu, p_cpu->regs.y);
  m6502_sign_calc(p_cpu, p_cpu->regs.y);
}

void lsr(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =l_value >> 1;

  if (l_value & 1) m6502_set_carry(p_cpu);
  else m6502_clear_carry(p_cpu);
  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void nop(m6502_cpu *p_cpu) {
  switch (p_cpu->opcode) {
  case 0x1C:
  case 0x3C:
  case 0x5C:
  case 0x7C:
  case 0xDC:
  case 0xFC:
    p_cpu->penalty_op = 1;
    break;
  }
}

void ora(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(u16)p_cpu->regs.a | l_value;

  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_save_accumulator(p_cpu, l_result);
}

void pha(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.a);
}

void php(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.status | M65C02_FLAG_BREAK);
}

void pla(m6502_cpu *p_cpu) {
  p_cpu->regs.a = m6502_opcode_get_value_8(p_cpu);

  m6502_zero_calc(p_cpu, p_cpu->regs.a);
  m6502_sign_calc(p_cpu, p_cpu->regs.a);
}

void plp(m6502_cpu *p_cpu) {
  p_cpu->regs.status = m6502_opcode_get_value_8(p_cpu) | M65C02_FLAG_CONSTANT;
}

void rol(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(l_value << 1) | (p_cpu->regs.status & M65C02_FLAG_CARRY);

  m6502_carry_calc(p_cpu, p_cpu->regs.status);
  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void ror(m6502_cpu *p_cpu) {
  const u16 l_value =m6502_opcode_get_value_8(p_cpu);
  const u16 l_result =(l_value >> 1) | ((p_cpu->regs.status & M65C02_FLAG_CARRY) << 7);

  if (l_value & 1) m6502_set_carry(p_cpu);
  else m6502_clear_carry(p_cpu);
  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_put_value_8(p_cpu, l_result);
}

void rti(m6502_cpu *p_cpu) {
  p_cpu->regs.status = m6502_opcode_get_value_8(p_cpu);
  const u16 l_value = m6502_opcode_get_value_16(p_cpu);
  p_cpu->regs.pc = l_value;
}

void rts(m6502_cpu *p_cpu) {
  const u16 l_value = m6502_opcode_get_value_16(p_cpu);
  p_cpu->regs.pc = l_value + 1;
}

void sbc(m6502_cpu *p_cpu) {
  p_cpu->penalty_op = 1;
  const u16 l_value = m6502_opcode_get_value_8(p_cpu) ^ 0x00FF;
  const u16 l_result = (u16)p_cpu->regs.a + l_value + (u16)(p_cpu->regs.status & M65C02_FLAG_CARRY);

  m6502_carry_calc(p_cpu, p_cpu->regs.status);
  m6502_zero_calc(p_cpu, p_cpu->regs.status);
  m6502_overflow_calc(p_cpu, l_result, p_cpu->regs.a, l_value);
  m6502_sign_calc(p_cpu, p_cpu->regs.status);

  m6502_opcode_save_accumulator(p_cpu, l_result);
}

void sec(m6502_cpu *p_cpu) {
  m6502_set_carry(p_cpu);
}

void sed(m6502_cpu *p_cpu) {
  m6502_set_decimal(p_cpu);
}

void sei(m6502_cpu *p_cpu) {
  m6502_set_interrupt(p_cpu);
}

void sta(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.a);
}

void stx(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.x);
}

void sty(m6502_cpu *p_cpu) {
  m6502_opcode_put_value_8(p_cpu, p_cpu->regs.y);
}

void tax(m6502_cpu *p_cpu) {
  p_cpu->regs.x = p_cpu->regs.a;

  m6502_zero_calc(p_cpu, p_cpu->regs.x);
  m6502_sign_calc(p_cpu, p_cpu->regs.x);
}

void tay(m6502_cpu *p_cpu) {
  p_cpu->regs.y = p_cpu->regs.a;

  m6502_zero_calc(p_cpu, p_cpu->regs.y);
  m6502_sign_calc(p_cpu, p_cpu->regs.y);
}

void tsx(m6502_cpu *p_cpu) {
  p_cpu->regs.x = p_cpu->regs.sp;

  m6502_zero_calc(p_cpu, p_cpu->regs.x);
  m6502_sign_calc(p_cpu, p_cpu->regs.x);
}

void txa(m6502_cpu *p_cpu) {
  p_cpu->regs.a = p_cpu->regs.x;

  m6502_zero_calc(p_cpu, p_cpu->regs.a);
  m6502_sign_calc(p_cpu, p_cpu->regs.a);
}

void txs(m6502_cpu *p_cpu) {
  p_cpu->regs.sp = p_cpu->regs.x;
}

void tya(m6502_cpu *p_cpu) {
  p_cpu->regs.a = p_cpu->regs.y;

  m6502_zero_calc(p_cpu, p_cpu->regs.a);
  m6502_sign_calc(p_cpu, p_cpu->regs.a);
}