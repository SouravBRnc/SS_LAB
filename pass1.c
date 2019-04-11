#include<stdio.h>
#include<math.h>
#include<string.h>

void main(){
	FILE *f1,*f2,*f3,*f4;
	f1 = fopen("input.txt","r");
	f2 = fopen("symbtab1.txt","w");
	f4 = fopen("output1.txt","w");
	char label[20], opcode[20], operand[20];
	int sa, lc;
	fscanf(f1,"%s %s %s",label,opcode,operand);
	if(strcmp(opcode,"START")==0){
		sa = strtol(operand, NULL, 16);
		fprintf(f4, "%x\t%s\t%s\t%s\n",sa,label,opcode,operand);
	}
	else{
		sa = 0;
	}
	lc = sa;
	fscanf(f1,"%s %s %s",label, opcode, operand);
	while(strcmp(opcode,"END")!=0){
		fprintf(f4,"%x\t%s\t%s\t%s\n", lc, label, opcode, operand);
		if(strcmp(label,"-")!=0){
			fprintf(f2,"%s\t%x\n",label, lc);
		}
		char tempcode[20], tempval[20];
		f3 = fopen("optab.txt","r");
		fscanf(f3,"%s %s", tempcode, tempval);
		while(!feof(f3)){
			if(strcmp(tempcode, opcode)==0){
				lc = lc+3;
				break;
			}
			fscanf(f3, "%s %s",tempcode, tempval);
		}
		fclose(f3);
		
		if(strcmp(opcode,"WORD")==0){
			lc = lc+3;
		}
		
		if(strcmp(opcode,"RESB")==0){
			lc = lc + strtol(operand, NULL, 10);
		}
		
		if(strcmp(opcode,"RESW")==0){
			lc = lc+3*strtol(operand, NULL, 10);
		}
		
		if(strcmp(opcode,"BYTE")==0){
			if(opcode[0]=='X'){
				lc = lc+ ceil((strlen(operand)-3)/2);
			}
			else{
				lc = lc+ strlen(operand)-3;	
			}
		}
		
		fscanf(f1,"%s %s %s", label, opcode, operand);
		
	}
	fprintf(f4,"%x\t%s\t%s\t%s\n",lc, label, opcode, operand);
	printf("Length of program: %d\n",lc-sa);	
	fclose(f1);
	fclose(f3);
	fclose(f4);	
}
