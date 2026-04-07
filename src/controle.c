#include "controle.h"

Out_controle controle_sinais(In_controle in){
	Out_controle out = {0};

	switch (in.opcode) {
		case 0x0: // tipo r
			out.RegDst = 1;
			out.RegWrite = 1;
			out.ULASrc = 0;
			out.Memtoreg = 0;
			out.MemRead = 0;
			out.MemWrite = 0;
			out.Branch = 0;
			out.jump = 0;
			out.ULA_op = in.function;
			break;

		case 0xB: // lw
			out.RegDst = 0;
			out.RegWrite = 1;
			out.Memtoreg = 1;
			out.ULASrc = 1;
			out.MemRead = 1;
			out.MemWrite = 0;
			out.Branch = 0;
			out.jump = 0;
			out.ULA_op = 0; 
			break;

		case 0xF: // sw
			out.RegDst = 0;
			out.RegWrite = 0;
			out.Memtoreg = 0;
			out.ULASrc = 1;
			out.MemRead = 0;
			out.MemWrite = 1;
			out.Branch = 0;
			out.jump = 0;
			out.ULA_op = 0;
			break;

        case 0x4: //addi
			out.RegDst = 0;
			out.RegWrite = 1;
			out.Memtoreg = 0;
			out.ULASrc = 1;
			out.MemRead = 0;
			out.MemWrite = 0;
			out.Branch = 0;
			out.jump = 0;
			out.ULA_op = 0;
			break;

        case 0x8: //beq 
			out.RegDst = 0;
			out.RegWrite = 0;
			out.Memtoreg = 0;
			out.ULASrc = 0;
			out.MemRead = 0;
			out.MemWrite = 0;
			out.Branch = 1;
			out.jump = 0;
			out.ULA_op = 2; 
            break;

        case 0x2: //j
			out.RegDst = 0;
			out.RegWrite = 0;
			out.Memtoreg = 0;
			out.ULASrc = 0;
			out.MemRead = 0;
			out.MemWrite = 0;
			out.Branch = 0;
			out.jump = 1;
			out.ULA_op = 0;
            break;

		default:
			break;
	}

	return out;
}

void copiaEntradaControle(In_controle input_backup, In_controle input){
 input_backup.opcode = input.opcode;
 input_backup.function = input.function;
}

void copiaSaidaControle(Out_controle output_backup, Out_controle output){
 output_backup.RegDst = output.RegDst;
 output_backup.RegWrite = output.RegWrite;
 output_backup.Memtoreg = output.Memtoreg;
 output_backup.ULASrc = output.ULASrc;
 output_backup.MemRead = output.MemRead;
 output_backup.MemWrite = output.MemWrite;
 output_backup.Branch = output.Branch;
 output_backup.jump = output.jump;
 output_backup.ULA_op = output.ULA_op; 
}

void copiaControle(Controle* controle_backup, Controle* controle){
 controle_backup->input = controle->input;
 copiaEntradaControle(controle_backup->input, controle->input);
 controle_backup->output = controle->output;
 copiaSaidaControle(controle_backup->output, controle->output);

} 