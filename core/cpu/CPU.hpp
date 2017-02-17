#pragma once

// Copyright 2016-2017 oneup

#include <cassert>

#include "core/Base.hpp"
#include "core/cpu/Instruction.hpp"
#include "core/cpu/Opcode.hpp"
#include "core/cpu/Regs.hpp"
#include "core/Serializer.hpp"

namespace gb1 {

namespace {

static inline std::string operand_to_string(AddrMode am, u16 ea, u32 val) {
    switch (am) {
        case AM_NONE:
            return "";
        case AM_IMM8:
            return "$" + to_hex(val, 2);
        case AM_IMM16:
            return "$" + to_hex(val, 4);
        case AM_MIMM16:
            return "($" + to_hex(ea, 4) + ") = $" + to_hex(val, 2);
        case AM_A:
            return "A";
        case AM_B:
            return "B";
        case AM_C:
            return "C";
        case AM_D:
            return "D";
        case AM_E:
            return "E";
        case AM_H:
            return "H";
        case AM_L:
            return "L";
        case AM_AF:
            return "AF";
        case AM_BC:
            return "BC";
        case AM_DE:
            return "DE";
        case AM_HL:
            return "HL";
        case AM_SP:
            return "SP";
        case AM_MBC:
            return "(BC) = $" + to_hex(val, 2);
        case AM_MDE:
            return "(DE) = $" + to_hex(val, 2);
        case AM_MHL:
            return "(HL) = $" + to_hex(val, 2);
        case AM_MHLI:
            return "(HL+) = $" + to_hex(val, 2);
        case AM_MHLD:
            return "(HL-) = $" + to_hex(val, 2);
        case AM_HMIMM8:
            return "($FF00+$" + to_hex(ea & 0xff, 2) + ") = $" + to_hex(val, 2);
        case AM_HMC:
            return "($FF00+C) = $" + to_hex(val, 2);
        case AM_SPIMM8:
            return "SP+$" + to_hex(val & 0xff, 2);
        default:
            assert(0);
            return "XXX";
    }
}

}    // namespace (anonymous)
struct Machine;

// Why does C++ make this so difficult?
// The operator<</>> functions need access to the CPU class members so
//   the definitions must come after the class definition.
// They need access to private CPU class members, so they need friend
//   declarations in the CPU class.
// Friend function declarations can't specify a storage class, so the functions
//   need to be declared again before the CPU class definition so the storage
//   class can be specified.
// They have arguments of type CPU, so CPU must be forward declared.

class CPU;

static inline Serializer& operator<<(Serializer &s, const CPU &cpu);
static inline Deserializer& operator>>(Deserializer &d, CPU &cpu);

class CPU {
    size_t busy_;
    Regs reg_;
    u16 if_, ie_;
    bool ime_, halt_;

    Machine *m_;
    friend struct Machine;

    bool FetchInstruction(Instruction *ins);
    bool Decode(Instruction *ins);
    bool FetchOperand(Instruction *ins, AddrMode am, u16 *ea, u32 *val);
    bool FetchOperands(Instruction *ins);
    bool Execute(Instruction *ins);
    bool Store(Instruction *ins);

    bool Step();

    static constexpr const u8 version_ = 0x00;
    static constexpr const u64 code_ = eight_cc(version_,'c','p','u');
    friend Serializer& operator<<(Serializer &s, const CPU &cpu);
    friend Deserializer& operator>>(Deserializer &d, CPU &cpu);
public:
    CPU(Machine *machine);
    CPU(const CPU&) = delete;
    CPU(CPU&&) = delete;
    CPU& operator=(const CPU&) = delete;
    CPU& operator=(CPU&&) = delete;

    bool Tick();
    void Interrupt(u8 num);

    const Regs& GetRegs() const { return reg_; }
};

static inline Serializer& operator<<(Serializer &s, const CPU &cpu) {
    s.Start(CPU::code_);
    return s << cpu.busy_ << cpu.reg_ << cpu.if_ << cpu.ie_ << cpu.ime_ << cpu.halt_;
}

static inline Deserializer& operator>>(Deserializer &d, CPU &cpu) {
    d.Start(CPU::code_);
    return d >> cpu.busy_ >> cpu.reg_ >> cpu.if_ >> cpu.ie_ >> cpu.ime_ >> cpu.halt_;
}

} // namespace gb1
