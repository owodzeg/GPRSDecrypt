#include <iostream>
#include <fstream>
#include <vector>
//#include <windows.h>

//using namespace std;

void decrypt(const std::vector <char>& GPRS_file, std::vector <char>& GARC_file) {
	uint32_t GPRS_start = 0x0;
	uint32_t GARC_start = 0xA210D0;
	// uint32_t MAGIC_start = 0x8B07558;
	// uint32_t MIPS_start = 0x88059B0;

	uint32_t v0 = 0x80;       //0x1CFD8;
	uint32_t v1 = 0x0;        //0x0;
	uint32_t a0 = GARC_start; //GARC_start;
	uint32_t a1 = 0x9;        //0x8;
	uint32_t a2 = 0xA;        //0x0;
	uint32_t a3 = 0x8;        //0x8;
	uint32_t t0 = 0x1;        //0x0;
	uint32_t t1 = 0x0;        //0x0;
	uint32_t t2 = -0x100;     //0x0;
	uint32_t t3 = 0x0;        //0x0;
	uint32_t t4 = 0x0;        //0x0;
	uint32_t at = 0x0;        //0x0;

	uint32_t cur_addr = 0;

	bool running = true;
	bool jump = false;
	std::vector<uint32_t> MAGIC_file = { 0x350,0x348,0x340,0x338,0x330,0x328,0x320,0x318,0x86C,0x864,0x85C,0x854,0x84C,0x844,0x83C,0x834 };
	//std::vector<char> GARC_file;

	//int ins = 0;
	//std::string filename(c_filename);
	//std::string garc_filename = filename.substr(filename.find_last_of("\\") + 1);
	//garc_filename = garc_filename.substr(0, garc_filename.find_first_of(".")) + ".GARC";
	//std::string workdir(c_workdir);
	//workdir = workdir.substr(0, workdir.find_last_of("\\") + 1);

	int jump_count = 0;
	uint32_t jump_addr = 0x0;

	while (running)
	{
		///cout << cur_addr << endl;
		//++ins;
		//cout << "0x" << std::hex << cur_addr << std::dec << endl;
		//Sleep(100);

		switch (cur_addr) {
		case 0x0: {
			a3 = GPRS_file[0x8];
			// a1 = a1 + int32_t(0x1);
			// v0 = int32_t(0x80);
			// t0 = int32_t(0x1);
			// t2 = int32_t(-0x100);
			// a2 = a1 + int32_t(0x1);
			// cout << a2 << endl;
			cur_addr = 0x18;
			break;
		}

		case 0x18: {
			// cout << ".";
			if (v0 != 0x0) {
				jump = true;
				jump_addr = 0x34;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1C: {
			t1 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x20: {
			if ((a1 >= GPRS_start) && (a1 < GARC_start)) {
				a3 = GPRS_file[a1];
			}

			if (a1 >= GARC_start) {
				uint32_t t_addr = a1 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}

			a1 = a2;
			v0 = int32_t(0x80);
			a2 = a1 + int32_t(0x1);
			t1 = a3 & v0;

			cur_addr += 0x14;
			break;
		}

		case 0x34: {
			if (t1 == 0x0) {
				jump = true;
				jump_addr = 0x48;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x38: {
			t3 = v0 >> 0x1;
			v0 = t3;

			cur_addr += 0x8;
			break;
		}

		case 0x40: {
			jump = true;
			jump_addr = 0x50;
			cur_addr += 0x4;
			break;
		}

		case 0x44: {
			t1 = t0;
			cur_addr += 0x4;
			break;
		}

		case 0x48: {
			v0 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x4C: {
			t1 = int32_t(0);
			cur_addr += 0x4;
			break;
		}

		case 0x50: {
			if (t1 != 0x0) {
				jump = true;
				jump_addr = 0x70;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x54: {
			cur_addr += 0x4;
			break;
		}

		case 0x58: {
			if ((a1 >= GPRS_start) && (a1 < GARC_start)) {
				t1 = GPRS_file[a1];
			}
			if (a1 >= GARC_start) {
				uint32_t t_addr = a1 - GARC_start;
				t1 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x5C: {
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x60: {
			if (a0 >= GARC_start) {
				char tmp = t1;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x64: {
			a0 = a0 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x68: {
			jump = true;
			jump_addr = 0x364;
			cur_addr += 0x4;
			break;
		}

		case 0x6C: {
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x70: {
			if (t3 != 0x0)
			{
				jump = true;
				jump_addr = 0x8C;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x74: {
			t1 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x78: {
			if ((a1 >= GPRS_start) && (a1 < GARC_start)) {
				a3 = GPRS_file[a1];
			}
			if (a1 >= GARC_start) {
				uint32_t t_addr = a1 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x7C: {
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x80: {
			v0 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x84: {
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x88: {
			t1 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x8C: {
			if (t1 == 0x0) {
				jump = true;
				jump_addr = 0xA0;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x90: {
			v0 = v0 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x94: {
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0x98: {
			jump = true;
			jump_addr = 0xA8;
			cur_addr += 0x4;
			break;
		}

		case 0x9C: {
			t1 = t0;
			cur_addr += 0x4;
			break;
		}

		case 0xA0: {
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0xA4: {
			t1 = int32_t(0);
			cur_addr += 0x4;
			break;
		}

		case 0xA8: {
			if (t1 != t0) {
				jump = true;
				jump_addr = 0x1A4;
			}
			cur_addr += 0x4;
			break;
		}

		case 0xAC: {
			cur_addr += 0x4;
			break;
		}

		case 0xB0: {
			if ((a1 >= GPRS_start) && (a1 < GARC_start)) {
				t1 = GPRS_file[a1];
			}
			if (a1 >= GARC_start) {
				uint32_t t_addr = a1 - GARC_start;
				t1 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0xB4: {
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0xB8: {
			t1 = t1 | t2;
			cur_addr += 0x4;
			break;
		}

		case 0xBC: {
			if (v0 != 0x0) {
				jump = true;
				jump_addr = 0xD4;
			}
			cur_addr += 0x4;
			break;
		}

		case 0xC0: {
			t1 = t1 << 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0xC4: {
			if ((a2 >= GPRS_start) && (a2 < GARC_start)) {
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start) {
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0xC8: {
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0xCC: {
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0xD0: {
			v1 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0xD4: {
			t3 = a3 & v1;
			cur_addr += 0x4;
			break;
		}

		case 0xD8: {
			if (t3 == 0x0) {
				jump = true;
				jump_addr = 0xEC;
			}
			cur_addr += 0x4;
			break;
		}

		case 0xDC: {
			v1 = v1 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0xE0: {
			t3 = v1;
			cur_addr += 0x4;
			break;
		}

		case 0xE4: {
			jump = true;
			jump_addr = 0xF4;
			cur_addr += 0x4;
			break;
		}

		case 0xE8: {
			t1 = t1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0xEC: {
			t3 = v1;
			cur_addr += 0x4;
			break;
		}

		case 0xF0: {
			t1 = t1;
			cur_addr += 0x4;
			break;
		}

		case 0xF4: {
			if (v1 != 0x0) {
				jump = true;
				jump_addr = 0x10C;
			}
			cur_addr += 0x4;
			break;
		}

		case 0xF8: {
			t1 = t1 << 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0xFC: {
			if ((a2 >= GPRS_start) && (a2 < GARC_start)) {
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start) {
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x100: {
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x104: {
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x108: {
			t3 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x10C: {
			v0 = a3 & t3;
			cur_addr += 0x4;
			break;
		}

		case 0x110: {
			if (v0 == 0x0) {
				jump = true;
				jump_addr = 0x124;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x114: {
			t3 = t3 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x118: {
			v0 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x11C: {
			jump = true;
			jump_addr = 0x12C;
			cur_addr += 0x4;
			break;
		}

		case 0x120: {
			t1 = t1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x124: {
			v0 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x128: {
			t1 = t1;
			cur_addr += 0x4;
			break;
		}

		case 0x12C: {
			if (t3 != 0x0)
			{
				jump = true;
				jump_addr = 0x144;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x130:
		{
			t1 = t1 << 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x134:
		{
			if ((a2 >= GPRS_start) && (a2 < GARC_start))
			{
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start)
			{
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x138:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x13C:
		{
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x140:
		{
			v0 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x144:
		{
			v1 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x148:
		{
			if (v1 == 0x0)
			{
				jump = true;
				jump_addr = 0x15C;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x14C:
		{
			t3 = v0 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x150:
		{
			v0 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x154:
		{
			jump = true;
			jump_addr = 0x164;
			cur_addr += 0x4;
			break;
		}

		case 0x158:
		{
			t1 = t1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x15C:
		{
			v0 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x160:
		{
			t1 = t1;
			cur_addr += 0x4;
			break;
		}

		case 0x164:
		{
			if (t3 != 0x0)
			{
				jump = true;
				jump_addr = 0x17C;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x168:
		{
			t1 = t1 << 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x16C:
		{
			if ((a2 >= GPRS_start) && (a2 < GARC_start))
			{
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start)
			{
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x170:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x174:
		{
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x178:
		{
			v0 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x17C:
		{
			t3 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x180:
		{
			if (t3 == 0x0)
			{
				jump = true;
				jump_addr = 0x194;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x184:
		{
			v0 = v0 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x188:
		{
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0x18C:
		{
			jump = true;
			jump_addr = 0x19C;
			cur_addr += 0x4;
			break;
		}

		case 0x190:
		{
			t1 = t1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x194:
		{
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0x198:
		{
			t1 = t1;
			cur_addr += 0x4;
			break;
		}

		case 0x19C:
		{
			jump = true;
			jump_addr = 0x1C0;
			cur_addr += 0x4;
			break;
		}

		case 0x1A0:
		{
			t1 = t1 + int32_t(-0xFF);
			cur_addr += 0x4;
			break;
		}

		case 0x1A4:
		{
			if ((a1 >= GPRS_start) && (a1 < GARC_start))
			{
				t1 = GPRS_file[a1];
			}
			if (a1 >= GARC_start)
			{
				uint32_t t_addr = a1 - GARC_start;
				t1 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1A8:
		{
			if (t1 == 0x0)
			{
				jump = true;
				jump_addr = 0x1B8;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1AC:
		{
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x1B0:
		{
			jump = true;
			jump_addr = 0x1C0;
			cur_addr += 0x4;
			break;
		}

		case 0x1B4:
		{
			t1 = t1 | t2;
			cur_addr += 0x4;
			break;
		}

		case 0x1B8:
		{
			jump = true;
			jump_addr = 0x36C;
			cur_addr += 0x4;
			break;
		}

		case 0x1BC:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x1C0:
		{
			t3 = t0;
			cur_addr += 0x4;
			break;
		}

		case 0x1C4:
		{
			if (v0 != 0x0)
			{
				jump = true;
				jump_addr = 0x1E0;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1C8:
		{
			v0 = a3 & v1;
			cur_addr += 0x4;
			break;
		}

		case 0x1CC:
		{
			if ((a2 >= GPRS_start) && (a2 < GARC_start))
			{
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start)
			{
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1D0:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x1D4:
		{
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x1D8:
		{
			v1 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x1DC:
		{
			v0 = a3 & v1;
			cur_addr += 0x4;
			break;
		}

		case 0x1E0:
		{
			if (v0 == 0x0)
			{
				jump = true;
				jump_addr = 0x1F4;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x1E4:
		{
			v1 = v1 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x1E8:
		{
			v0 = v1;
			cur_addr += 0x4;
			break;
		}

		case 0x1EC:
		{
			jump = true;
			jump_addr = 0x1FC;
			cur_addr += 0x4;
			break;
		}

		case 0x1F0:
		{
			t4 = t0;
			cur_addr += 0x4;
			break;
		}

		case 0x1F4:
		{
			v0 = v1;
			cur_addr += 0x4;
			break;
		}

		case 0x1F8:
		{
			t4 = int32_t(0);
			cur_addr += 0x4;
			break;
		}

		case 0x1FC:
		{
			if (t4 != t0)
			{
				jump = true;
				jump_addr = 0x244;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x200:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x204:
		{
			if (v1 != 0x0)
			{
				jump = true;
				jump_addr = 0x21C;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x208:
		{
			t3 = t3 << 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x20C:
		{
			if ((a2 >= GPRS_start) && (a2 < GARC_start))
			{
				a3 = GPRS_file[a2];
			}
			if (a2 >= GARC_start)
			{
				uint32_t t_addr = a2 - GARC_start;
				a3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x210:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x214:
		{
			a1 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x218:
		{
			v0 = int32_t(0x80);
			cur_addr += 0x4;
			break;
		}

		case 0x21C:
		{
			v1 = a3 & v0;
			cur_addr += 0x4;
			break;
		}

		case 0x220:
		{
			if (v1 == 0x0)
			{
				jump = true;
				jump_addr = 0x234;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x224:
		{
			v0 = v0 >> 0x1;
			cur_addr += 0x4;
			break;
		}

		case 0x228:
		{
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0x22C:
		{
			jump = true;
			jump_addr = 0x23C;
			cur_addr += 0x4;
			break;
		}

		case 0x230:
		{
			t3 = t3 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x234:
		{
			v1 = v0;
			cur_addr += 0x4;
			break;
		}

		case 0x238:
		{
			t3 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x23C:
		{
			jump = true;
			jump_addr = 0x1C4;
			cur_addr += 0x4;
			break;
		}

		case 0x240:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x244:
		{
			if (t3 < 0x7)
			{
				a2 = 1;
			}
			else
			{
				a2 = 0;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x248:
		{
			if (a2 == 0x0)
			{
				jump = true;
				jump_addr = 0x278;
				cur_addr += 0x4;
			}
			else
			{
				cur_addr += 0x8;
			}
			break;
		}

		case 0x24C:
		{
			t3 = t3 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x250:
		{
			if (t3 < 0)
			{
				jump = true;
				jump_addr = 0x364;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x254:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x258:
		{
			v1 = a0 + t1;
			cur_addr += 0x4;
			break;
		}

		case 0x25C:
		{
			if ((v1 >= GPRS_start) && (v1 < GARC_start))
			{
				v1 = GPRS_file[v1];
			}
			if (v1 >= GARC_start)
			{
				uint32_t t_addr = v1 - GARC_start;
				v1 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x260:
		{
			t3 = t3 + int32_t(-0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x264:
		{
			if (a0 >= GARC_start)
			{
				char tmp = v1;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x268:
		{
			if ((int32_t)t3 >= 0)
			{
				jump = true;
				jump_addr = 0x258;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x26C:
		{
			a0 = a0 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x270:
		{
			jump = true;
			jump_addr = 0x364;
			cur_addr += 0x4;
			break;
		}

		case 0x274:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x278:
		{
			a2 = t3 >> 0x3;
			cur_addr += 0x4;
			break;
		}

		case 0x27C:
		{
			t3 = t3 & 0x7;
			cur_addr += 0x4;
			break;
		}

		case 0x280:
		{
			v1 = t3 + int32_t(-0x8);
			cur_addr += 0x4;
			break;
		}

		case 0x284:
		{
			a0 = a0 + v1;
			cur_addr += 0x4;
			break;
		}

		case 0x288:
		{
			if (t3 < 0x8)
			{
				v1 = 1;
			}
			else
			{
				v1 = 0;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x28C:
		{
			if (v1 == 0x0)
			{
				jump = true;
				jump_addr = 0x2AC;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x290:
		{
			t1 = a0 + t1;
			cur_addr += 0x4;
			break;
		}

		case 0x294:
		{
			t3 = t3 << 0x2;
			cur_addr += 0x4;
			break;
		}

		case 0x298:
		{
			at = 0x0;
			cur_addr += 0x4;
			break;
		}

		case 0x29C:
		{
			at = at + t3;
			cur_addr += 0x4;
			break;
		}

		case 0x2A0:
		{
			uint32_t tmp;
			// cout << at / 4 << endl;
			at = MAGIC_file[at / 4];

			cur_addr += 0x4;
			break;
		}

		case 0x2A4:
		{
			jump = true;
			jump_addr = at;
			cur_addr += 0x4;
			break;
		}

		case 0x2A8:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x2AC:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				t3 = GPRS_file[t1];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2B0:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2B4:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x1 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x1 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2B8:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2BC:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x2 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x2 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2C0:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2C4:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x3 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x3 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2C8:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2CC:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x4 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x4 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2D0:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2D4:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x5 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x5 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2D8:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2DC:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x6 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x6 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2E0:
		{
			if (a0 >= GARC_start)
			{
				char tmp = t3;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2E4:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x7 + t1;
				v1 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x7 + t1 - GARC_start;
				v1 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2E8:
		{
			t3 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x2EC:
		{
			a2 = a0 + int32_t(0x8);
			cur_addr += 0x4;
			break;
		}

		case 0x2F0:
		{
			if (a0 >= GARC_start)
			{
				char tmp = v1;
				GARC_file.push_back(tmp);
			}
			cur_addr += 0x4;
			break;
		}

		case 0x2F4:
		{
			t1 = t1 + int32_t(0x8);
			cur_addr += 0x4;
			break;
		}

		case 0x2F8:
		{
			a0 = t3 + int32_t(-0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x2FC:
		{
			t3 = a0;
			cur_addr += 0x4;
			break;
		}

		case 0x300:
		{
			a0 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x304:
		{
			a2 = t3;
			cur_addr += 0x4;
			break;
		}

		case 0x308:
		{
			if ((int32_t)a2 >= 0)
			{
				jump = true;
				jump_addr = 0x2AC;
			}
			cur_addr += 0x4;
			break;
		}

		case 0x30C:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x310:
		{
			jump = true;
			jump_addr = 0x364;
			cur_addr += 0x4;
			break;
		}

		case 0x314:
		{
			a2 = a1 + int32_t(0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x318:
		{
			jump = true;
			jump_addr = 0x2B8;
			cur_addr += 0x4;
			break;
		}

		case 0x31C:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x1 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x1 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x320:
		{
			jump = true;
			jump_addr = 0x2C0;
			cur_addr += 0x4;
			break;
		}

		case 0x324:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x2 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x2 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x328:
		{
			jump = true;
			jump_addr = 0x2C8;
			cur_addr += 0x4;
			break;
		}

		case 0x32C:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x3 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x3 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x330:
		{
			jump = true;
			jump_addr = 0x2D0;
			cur_addr += 0x4;
			break;
		}

		case 0x334:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x4 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x4 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x338:
		{
			jump = true;
			jump_addr = 0x2D8;
			cur_addr += 0x4;
			break;
		}

		case 0x33C:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x5 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x5 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x340:
		{
			jump = true;
			jump_addr = 0x2E0;
			cur_addr += 0x4;
			break;
		}

		case 0x344:
		{
			if ((t1 >= GPRS_start) && (t1 < GARC_start))
			{
				uint32_t t_addr = 0x6 + t1;
				t3 = GPRS_file[t_addr];
			}
			if (t1 >= GARC_start)
			{
				uint32_t t_addr = 0x6 + t1 - GARC_start;
				t3 = (int32_t)GARC_file[t_addr];
			}
			cur_addr += 0x4;
			break;
		}

		case 0x348:
		{
			jump = true;
			jump_addr = 0x2E4;
			cur_addr += 0x4;
			break;
		}

		case 0x34C:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x350:
		{
			t3 = a2;
			cur_addr += 0x4;
			break;
		}

		case 0x354:
		{
			a2 = a0 + int32_t(0x8);
			cur_addr += 0x4;
			break;
		}

		case 0x358:
		{
			t1 = t1 + int32_t(0x8);
			cur_addr += 0x4;
			break;
		}

		case 0x35C:
		{
			jump = true;
			jump_addr = 0x2FC;
			cur_addr += 0x4;
			break;
		}

		case 0x360:
		{
			a0 = t3 + int32_t(-0x1);
			cur_addr += 0x4;
			break;
		}

		case 0x364:
		{
			jump = true;
			jump_addr = 0x18;
			cur_addr += 0x4;
			break;
		}

		case 0x368:
		{
			cur_addr += 0x4;
			break;
		}

		case 0x36C:
		{
			running = false;
			break;
		}
		}

		if (jump_count >= 1) {
			jump_count = 0;
			cur_addr = jump_addr;

			//cout << "Jump to 0x" << std::hex << jump_addr << std::dec << endl;
		}

		if (jump) {
			jump = false;
			jump_count = 1;
		}
	}

	//cout << "Program took " << ins << " instructions to decompress this file" << endl;

}
int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Usage: input_filename [output_filename]\n";
		std::cout << "Dafault output_filename is input_filename with extension \".GARC\"";
		return 0;
	}

	std::ifstream in(argv[1], std::ios::binary);
	if (!in.is_open()) {
		std::cout << "Error! File " << argv[1] << " can't be opened\n";
		return 0;
	}
	std::vector<char> GPRS_file((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	in.close();
	// TO DO: is it safe to use GPRS_file after in has been closed?
	
	std::string output_path;
	if (argc < 3) {
		output_path = (std::string(argv[1]) += ".GARC");
	}
	else {
		output_path = argv[2];
	}

	std::ofstream garc_out(output_path, std::ios::binary);
	if (!garc_out.is_open()) {
		std::cout << "Error! Output file " << output_path.c_str() << " can't be opened\n";
		//std::cout << std::string();
		return 0;
	}

	std::vector <char> GARC_file;

	decrypt(GPRS_file, GARC_file); // decrypt will accept arguments: const std::vector <char>& GPRS_file, const std::vector <char>& GARC_file

	for (int i = 0; i < GARC_file.size(); i++) {
		garc_out.put(GARC_file[i]);
	}
	garc_out.close();
	std::cout << "Success!";

	//system("pause");
	return 0;
}
