#include "m6502.h"

/*============================================================================*/
/*                                  Address                                   */
/*============================================================================*/

void imp(m6502_cpu *p_cpu) { //implied
}

void acc(m6502_cpu *p_cpu) { //accumulator
}

void imm(m6502_cpu *p_cpu) { //immediate
  p_cpu->ea = p_cpu->regs.pc++;
}

void zp(m6502_cpu *p_cpu) { //zero-page
  p_cpu->ea = (u16)m6502_bus_read_data(p_cpu, (u16)p_cpu->regs.pc++);
}

void zpx(m6502_cpu *p_cpu) { //zero-page,X
  p_cpu->ea = ((u16)m6502_bus_read_data(p_cpu, (u16)p_cpu->regs.pc++) + (u16)p_cpu->regs.x) & 0xFF; //zero-page wraparound
}

void zpy(m6502_cpu *p_cpu) { //zero-page,Y
  p_cpu->ea = ((u16)m6502_bus_read_data(p_cpu, (u16)p_cpu->regs.pc++) + (u16)p_cpu->regs.y) & 0xFF; //zero-page wraparound
}

void rel(m6502_cpu *p_cpu) { //relative for branch ops (8-bit immediate value, sign-extended)
  p_cpu->reladdr = (u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc++);
  if (p_cpu->reladdr & 0x80) p_cpu->reladdr |= 0xFF00;
}

void abso(m6502_cpu *p_cpu) { //absolute
  p_cpu->ea = (u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc) | ((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc+1) << 8);
  p_cpu->regs.pc += 2;
}

void absx(m6502_cpu *p_cpu) { //absolute,X
  p_cpu->ea = ((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc) | ((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc+1) << 8));
  const u16 l_start_page = p_cpu->ea & 0xFF00;
  p_cpu->ea += (u16)p_cpu->regs.x;

  if (l_start_page != (p_cpu->ea & 0xFF00)) { //one cycle penlty for page-crossing on some opcodes
    p_cpu->penalty_address = 1;
  }

  p_cpu->regs.pc += 2;
}

void absy(m6502_cpu *p_cpu) { //absolute,Y
  p_cpu->ea = ((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc) | ((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc+1) << 8));
  const u16 l_start_page = p_cpu->ea & 0xFF00;
  p_cpu->ea += (u16)p_cpu->regs.y;

  if (l_start_page != (p_cpu->ea & 0xFF00)) { //one cycle penlty for page-crossing on some opcodes
    p_cpu->penalty_address = 1;
  }

  p_cpu->regs.pc += 2;
}

void ind(m6502_cpu *p_cpu) { //indirect
  u16 eahelp, eahelp2;
  eahelp = (u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc) | (u16)((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc+1) << 8);
  eahelp2 = (eahelp & 0xFF00) | ((eahelp + 1) & 0x00FF); //replicate 6502 page-boundary wraparound bug
  p_cpu->ea = (u16)m6502_bus_read_data(p_cpu, eahelp) | ((u16)m6502_bus_read_data(p_cpu, eahelp2) << 8);
  p_cpu->regs.pc += 2;
}

void indx(m6502_cpu *p_cpu) { // (indirect,X)
  u16 eahelp;
  eahelp = (u16)(((u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc++) + (u16)p_cpu->regs.x) & 0xFF); //zero-page wraparound for table pointer
  p_cpu->ea = (u16)m6502_bus_read_data(p_cpu, eahelp & 0x00FF) | ((u16)m6502_bus_read_data(p_cpu, (eahelp+1) & 0x00FF) << 8);
}

void indy(m6502_cpu *p_cpu) { // (indirect),Y
  u16 eahelp, eahelp2, l_start_page;
  eahelp = (u16)m6502_bus_read_data(p_cpu, p_cpu->regs.pc++);
  eahelp2 = (eahelp & 0xFF00) | ((eahelp + 1) & 0x00FF); //zero-page wraparound
  p_cpu->ea = (u16)m6502_bus_read_data(p_cpu, eahelp) | ((u16)m6502_bus_read_data(p_cpu, eahelp2) << 8);
  l_start_page = p_cpu->ea & 0xFF00;
  p_cpu->ea += (u16)p_cpu->regs.y;

  if (l_start_page != (p_cpu->ea & 0xFF00)) { //one cycle penlty for page-crossing on some opcodes
    p_cpu->penalty_address = 1;
  }
}