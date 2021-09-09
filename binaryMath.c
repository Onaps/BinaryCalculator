#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int * convert_to_binary(int decimal);
int * convert_twos_complement(int * binary);
int * bin_additon(int * num1,int * num2);

int main(void){

  int stdin_num;
  int i;

  printf("Enter decimal number in range of a byte [-128,127]: ");

  // input from terminal then write to address represented by stdin_num
  scanf("%d", &stdin_num);

  int * result = convert_to_binary(stdin_num);
  
  printf("\nTwo's Complement Binary Representation of %d: ", stdin_num);
  for(i=0; i<8; i++){

    printf("%d", result[i]);
  }

  printf("\n\n");
}

int * convert_to_binary(int decimal){
  //define as static var since C doesnt let the address of local var return outside of func
  static int binary[8];
  int i;
  int flag;

  if(decimal<0){
    flag = 1;
    decimal = abs(decimal);
  }
  // this algo works from right to left
  /*
    ls index: 0,1,2,3
   */
  for(i=7; i>=0; i--){
    binary[i] = decimal % 2;
    decimal = floor(decimal/2);
  }

  if(flag==1){
    return convert_twos_complement(binary);
  }
  
  return binary;
}
int * convert_twos_complement(int * binary){
  int i;
  for(i=7;i>=0;i--){
      
      if(binary[i]==1)binary[i]=0;
      else if(binary[i]==0)binary[i]=1;

    }
    // decimal number one in 8-bit binary 
    int one[8] = {0,0,0,0,0,0,0,1};
    //bin_additon(binary, one);
    return bin_additon(binary, one);
}

int * bin_additon(int * num1,int num2[4]){
  int i;
  // must decalie this as static or when i return output the compiler will free memory and discard output variable. It will end up pointing to omething random
  static int output[8]; 
  int temp;
  int carry_bit=0;
  
  for(i=7;i>=0;i--){

    temp = num1[i]+num2[i]+carry_bit;
    
    switch(temp){
      case 1:
        output[i]=1;
        carry_bit = 0;
        break;
      case 2:
        output[i]=0;
        carry_bit = 1;
        break;
      case 3:
        output[i]=1;
        carry_bit = 1;
        break;
      default:
        output[i] = 0;
    }
    //use these print statements to debug
    //printf("%d, %d ", i,num1[i]);
    //printf("%d, t: %d ", i,temp);
    //printf(" o:%d\n", output[i]);

  }
  
  return output;
}