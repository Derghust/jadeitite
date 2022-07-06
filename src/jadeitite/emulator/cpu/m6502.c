#include "m6502.h"
#include "jadeitite/log.h"

/*============================================================================*/
/*                              Bus Functions                                 */
/*============================================================================*/

void m6502_put_data_to_bus(m6502_cpu *p_cpu, u8 p_data) {
  p_cpu->pins->d =p_data;
}

void m6502_put_address_to_bus(m6502_cpu *p_cpu, u16 p_data) {
  p_cpu->pins->a = p_data;
}

u8 m6502_bus_read_data(m6502_cpu *p_cpu, u16 p_address) {
  m6502_put_address_to_bus(p_cpu, p_address);
  p_cpu->required_process_bus(p_cpu->pins);
  LOG_INFO(
    "M65c02 Reading [address=0x%04X; data=0x%02X]",
    p_cpu->pins->a,
    p_cpu->pins->d);
  return p_cpu->pins->d;
}

void m6502_bus_put_data(m6502_cpu *p_cpu, u16 p_address, u8 p_value){
  m6502_put_address_to_bus(p_cpu, p_address);
  m6502_put_data_to_bus(p_cpu, p_value);
  LOG_INFO(
    "M65c02 Writing [address=0x%04X; data=0x%02X]",
    p_cpu->pins->a,
    p_cpu->pins->d);
  p_cpu->required_process_bus(p_cpu->pins);
}

void m6502_bus_put_address(m6502_cpu *p_cpu, u16 p_address){
  m6502_put_address_to_bus(p_cpu, p_address);
  LOG_INFO(
    "M65c02 Writing [address=0x%04X; data=0x%02X]",
    p_cpu->pins->a,
    p_cpu->pins->d);
  p_cpu->required_process_bus(p_cpu->pins);
}

/*============================================================================*/
/*                              Base Functions                                */
/*============================================================================*/

void m6502_reset(m6502_cpu *p_cpu){
  // Assign operation code for processing reset
  p_cpu->regs.pc = m6502_bus_read_data(p_cpu, 0xFFFC);
  p_cpu->regs.pc |= m6502_bus_read_data(p_cpu, 0xFFFD) << 8;

  // Reset registers
  p_cpu->regs.a = 0;
  p_cpu->regs.x = 0;
  p_cpu->regs.y = 0;
  p_cpu->regs.sp = 0xFD;
  p_cpu->regs.status |= M65C02_FLAG_CONSTANT;
}

u8 m6502_step(m6502_cpu *p_cpu) {
  p_cpu->opcode = m6502_bus_read_data(p_cpu, p_cpu->regs.pc++);
  p_cpu->regs.status |= M65C02_FLAG_CONSTANT;

  p_cpu->penalty_op = 0;
  p_cpu->penalty_address = 0;

  (*m6502_address_table[p_cpu->opcode])(p_cpu);
  (*m6502_opcode_table[p_cpu->opcode])(p_cpu);
//  clockticks6502 += ticktable[p_cpu->opcode];
//  if (p_cpu->penalty_op && p_cpu->penalty_address) clockticks6502++;
//  clockgoal6502 = clockticks6502;

  p_cpu->instruction_counter++;

//  if (callexternal) (*loopexternal)();
}
