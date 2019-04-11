#include<string.h>
#include<stdio.h>

void main(){
	FILE *f1,*f2,*f3,*f4;
	char label[20], opcode[20], operand[20];
	int address, sa=0, len;
	
	f1 = fopen("output1.txt","r");
	f2 = fopen("pass2out.txt","w");
	
	fscanf(f1,"%X %s %s %s",&address, label, opcode, operand);
	if(strcmp(opcode,"START")==0){
		fprintf(f2,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
		sa = address;
	}
	fscanf(f1,"%X %s %s %s",&address,label,opcode,operand);
	while(strcmp(opcode,"END")!=0){
		fprintf(f2,"%X\t%s\t%s\t%s\t",address,label,opcode,operand);
		f3 = fopen("optab.txt","r");
		char tempcode[20],tempval[20];
		fscanf(f3,"%s %s",tempcode,tempval);
		while(!feof(f3)){
			if(strcmp(tempcode,opcode)==0){
				fprintf(f2,"%s",tempval);
				break;
			}
			fscanf(f3,"%s %s",tempcode,tempval);
		}
		fclose(f3);
		char actoperand[20];
		if(operand[strlen(operand)-1]=='X'){
			int i;
			for(i=0; i<strlen(operand)-2;i++)
				actoperand[i] = operand[i];
			actoperand[i]='\0';
		}
		else{
			strcpy(actoperand,operand);
		}
		f4 = fopen("symtab.txt","r");
		char symcode[20], symval[20];
		fscanf(f4,"%s %s",symcode, symval);
		while(!feof(f4)){
			if(strcmp(symcode,actoperand)==0){
				int val=strtol(symval, NULL,16);
				if(operand[strlen(operand)-1]=='X'){
					val = val+0x8000;	
				}
				fprintf(f2,"%x\n",val);
				break;
			}
			else
				fscanf(f4,"%s %s",symcode, symval);
		}
		fclose(f4);
		if(strcmp(opcode,"WORD")==0){
			int val=strtol(operand,NULL,16);
			char num[10];
			sprintf(num,"%X",val);
			int l = strlen(num);
			while(l<6){
				fprintf(f2,"0");
				l++;
			}
			fprintf(f2,"%s\n",num);
		}
		if(strcmp(opcode,"BYTE")==0){
			if(operand[0]=='X'){
				for(int i=2;i<strlen(operand)-1;i++){
					fprintf(f2,"%c",operand[i]);
				}
				fprintf(f2,"\n");
			}
			else{
				for(int i=2;i<strlen(operand)-1;i++){
					fprintf(f2,"%02X",operand[i]);
				}
				fprintf(f2,"\n");
			}
		}
		if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0){
			fprintf(f2,"-\n");
		}
		
		fscanf(f1,"%X %s %s %s",&address,label,opcode,operand);
	}
	
	fprintf(f2,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
	printf("Length of program: %d\n",address-sa);
	fclose(f1);
	fclose(f2);
	
}
