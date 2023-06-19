#include <bits/stdc++.h>

using namespace std;

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

string get_bin(int n) {
    if (n >= 'a') {
        n = n - 'a' + 10;
    }
    
    string ans;
    
    for (int i = 0; i < 4; i++) {
        ans.push_back(n % 2 + '0');
        n /= 2;
    }
    
    for (int i = 0; i < 2; i++) {
        swap(ans[i], ans[3 - i]);
    }
    
    return ans;
}

string get_bin(string hex_num) {
    string ans;
    
    for (int i = 0; i < (int)hex_num.length(); i++) {
        ans.append(get_bin(hex_num[i]));
    }
    
    return ans;
}

int get_int(string bin, bool neg) {
    int ans = 0;
    
    if (neg && bin[0] == '1') {
        for (int i = (int)bin.size() - 1; i > -1; i--) {
            if (bin[i] == '1') {
                bin[i] = '0';
            } else {
                bin[i] = '1';
            }
        }
        
        ans = get_int(bin, neg);
        ans++;
        return -1*ans;
    }
    
    for (int i = (int)bin.size() - 1; i > -1; i--) {
        ans += ((bin[i] - '0') * pow(2, (int)bin.size() - i - 1));
    }
    
    return ans;
}

int get_index(vector<int>& jp, int pc) {
    for (int i = 0; i<(int)jp.size(); i++) {
        if (jp[i] == pc) {
            return i;
        }
    }
    
    return -1;
}

void get_ass(vector<string>& inst) {
    int pc = 0;
    vector<int> jump_pc;
    int num_inst = (int)inst.size();
    for (int j = 0; j < num_inst; j++) {
        pc+=4;
        
        int loc = get_index(jump_pc, pc);
        if (loc != -1) {
            cout<<"L"<<loc + 1<<":"<<endl;
        }
        
        string bin_i = get_bin(inst[j]);
        
        string opcode;
        
        for (int i = 0; i < 7; i++) {
            opcode.push_back(bin_i[i + 25]);
        }
        
        if (opcode == "0110011") {
            // R-Type
            string func3;
            string func7;
            
            for (int i = 0; i < 3; i++) {
                func3.push_back(bin_i[17 + i]);
            }
            
            for (int i = 0; i < 7; i++) {
                func7.push_back(bin_i[i]);
            }
            
            string rs1;
            string rs2;
            string rd;
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rs2.push_back(bin_i[7 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rd.push_back(bin_i[20 + i]);
            }
            
            int r1 = get_int(rs1,0);
            int r2 = get_int(rs2,0);
            int r = get_int(rd,0);
            
            if (func3 == "000" && func7 == "0000000") {
                cout << "add x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "000" && func7 == "0100000") {
                cout << "sub x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "111" && func7 == "0000000") {
                cout << "and x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "110" && func7 == "0000000") {
                cout << "or x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "100" && func7 == "0000000") {
                cout << "xor x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "001" && func7 == "0000000") {
                cout << "sll x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "101" && func7 == "0000000") {
                cout << "srl x" << r << ", x" << r1 << ", x" << r2 << endl;
            } else if (func3 == "101" && func7 == "0100000") {
                cout << "sra x" << r << ", x" << r1 << ", x" << r2 << endl;
            }
        } // add
        else if (opcode == "0010011") {
            // I-Type
            string func3;
            
            for (int i = 0; i < 3; i++) {
                func3.push_back(bin_i[17 + i]);
            }
            
            string rs1;
            string rd;
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rd.push_back(bin_i[20 + i]);
            }
            
            string immi;
            
            for (int i = 0; i<12; i++) {
                immi.push_back(bin_i[i]);
            }
            
            int r1 = get_int(rs1,0);
            int imm = get_int(immi,1);
            int r = get_int(rd,0);
            
            if (func3 == "000") {
                cout << "addi x" << r << ", x" << r1 << ", " << imm << endl;
            } else if (func3 == "100") {
                cout << "xori x" << r << ", x" << r1 << ", " << imm << endl;
            } else if (func3 == "110") {
                cout << "ori x" << r << ", x" << r1 << ", " << imm << endl;
            } else if (func3 == "111") {
                cout << "andi x" << r << ", x" << r1 << ", " << imm << endl;
            } else {
                string shamt;
                
                for (int i = 0; i < 12; i++) {
                    shamt.push_back(bin_i[i]);
                }
                shamt[1] = '0';
                int s = get_int(shamt, 0);
                
                if (func3 == "001") {
                    cout << "slli x" << r << ", x" << r1 << ", " << s << endl;
                } else if (func3 == "101") {
                    if (bin_i[1] == '0') {
                        cout << "srli x" << r << ", x" << r1 << ", " << s << endl;
                    } else {
                        cout << "srai x" << r << ", x" << r1 << ", " << s << endl;
                    }
                }
            }
        } // addi
        else if (opcode == "0000011") {
            string func3;
            
            for (int i = 0; i < 3; i++) {
                func3.push_back(bin_i[17 + i]);
            }
            
            string rs1;
            string rd;
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rd.push_back(bin_i[20 + i]);
            }
            
            string immi_long;
            
            for (int i = 0; i<12; i++) {
                immi_long.push_back(bin_i[i]);
            }
            
            int r1 = get_int(rs1,0);
            int r = get_int(rd,0);
            int il = get_int(immi_long,1);
            
            if (func3 == "000") {
                cout << "lb x" << r << ", " << il << "(x" << r1 << ")" << endl;
            } else if (func3 == "001") {
                cout << "lh x" << r << ", " << il << "(x" << r1 << ")" << endl;
            } else if (func3 == "010") {
                cout << "lw x" << r << ", " << il << "(x" << r1 << ")" << endl;
            } else if (func3 == "100") {
                cout << "lbu x" << r << ", " << il << "(x" << r1 << ")" << endl;
            } else if (func3 == "101") {
                cout << "lhu x" << r << ", " << il << "(x" << r1 << ")" << endl;
            } else if (func3 == "001") {
                cout << "lh x" << r << ", " << il << "(x" << r1 << ")" << endl;
            }
        } // lw
        else if (opcode == "1100011") {
            string func3;
            
            for (int i = 0; i < 3; i++) {
                func3.push_back(bin_i[17 + i]);
            }
            
            string rs1;
            string rs2;
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rs2.push_back(bin_i[7 + i]);
            }
            
            int r1 = get_int(rs1,0);
            int r2 = get_int(rs2,0);
            
            string immi;
            
            immi.push_back(bin_i[0]);
            immi.push_back(bin_i[24]);
            
            for (int i = 1; i<7; i++) {
                immi.push_back(bin_i[i]);
            }
            
            for (int i = 0; i < 4; i++) {
                immi.push_back(bin_i[20 + i]);
            }
            
            immi.push_back('0');
            
            int imm = get_int(immi,1);
            int lab;
            int loc = get_index(jump_pc, pc + imm);
            if (loc != -1) {
                lab = loc + 1;
            } else {
                jump_pc.push_back(imm + pc);
                if (imm >= 0)
                    lab = (int)jump_pc.size();
                else
                    lab = imm;
            }
            
            
            if (func3 == "000") {
                cout<<"beq x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            } else if (func3 == "001") {
                cout<<"bne x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            } else if (func3 == "100") {
                cout<<"blt x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            } else if (func3 == "101") {
                cout<<"bge x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            } else if (func3 == "110") {
                cout<<"bltu x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            } else if (func3 == "111") {
                cout<<"bgeu x"<<r1<<", x"<<r2<<", L"<<lab<<endl;
            }
        } // beq
        else if (opcode == "1101111") {
            string rd;
            
            for (int i = 0; i < 5; i++) {
                rd.push_back(bin_i[20 + i]);
            }
            
            string immi;
            immi.push_back(bin_i[0]);
            immi.push_back(bin_i[11]);
            
            for (int i = 12; i<20; i++) {
                immi.push_back(bin_i[i]);
            }
            
            for (int i = 1; i<11; i++) {
                immi.push_back(bin_i[i]);
            }
            
            int r = get_int(rd,0);
            int imm = get_int(immi,1);
            int loc = get_index(jump_pc, pc+imm);
            int lab;
            if (loc != -1) {
                lab = loc + 1;
            } else {
                jump_pc.push_back(imm + pc);
                lab = (int)jump_pc.size();
            }
            
            cout<<"jal x"<<r<<", L"<<lab<<endl;
        } // jal
        else if (opcode == "0100011") {
            string func3;
            
            for (int i = 0; i < 3; i++) {
                func3.push_back(bin_i[17 + i]);
            }
            
            string rs1;
            string rs2;
            string immi;
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rs2.push_back(bin_i[7 + i]);
            }
            
            for (int i = 0; i<7; i++) {
                immi.push_back(bin_i[i]);
            }
            
            for (int i = 0; i < 5; i++) {
                immi.push_back(bin_i[20 + i]);
            }
            
            int imm = get_int(immi,1);
            int r1 = get_int(rs1,0);
            int r2 = get_int(rs2,0);
            
            if (func3 == "000") {
                printf("sb x%d, %d(x%d)\n", r2, imm, r1);
            } else if (func3 == "001") {
                printf("sh x%d, %d(x%d)\n", r2, imm, r1);
            } else if (func3 == "010") {
                printf("sw x%d, %d(x%d)\n", r2, imm, r1);
            }
        } // sw
        else if (opcode == "0110111") {
            string immi;
            
            for (int i = 0; i<20; i++) {
                immi.push_back(bin_i[i]);
            }
            
            string rd;
            
            for (int i = 0; i<5; i++) {
                rd.push_back(bin_i[20+i]);
            }
            
            int imm = get_int(immi,0);
            int r = get_int(rd,0);
            
            printf("lui x%d, %d\n", r, imm);
        } // lui
        else if (opcode == "1100111") {
            string rd;
            string rs1;
            string immi;
            
            for (int i = 0; i<5; i++) {
                rd.push_back(bin_i[20+i]);
            }
            
            for (int i = 0; i < 5; i++) {
                rs1.push_back(bin_i[12 + i]);
            }
            
            for (int i = 0; i<12; i++) {
                immi.push_back(bin_i[i]);
            }
            
            int r = get_int(rd,0);
            int r1 = get_int(rs1,0);
            int imm = get_int(immi, 1);
            
            printf("jalr x%d, %d(x%d)\n", r, imm, r1);
        } // jalr
    }
}

int main() {
    vector<string> v1;
    
    cout<<get_int("110011", 1)<<endl;
    
    while (1) {
        string str;
        if (!(cin>>str)) {
            break;
        }

        v1.push_back(str);
    }
    
    vector<string> v = {"11f52fb7"};
    
    get_ass(v1);

    return 0;
}
