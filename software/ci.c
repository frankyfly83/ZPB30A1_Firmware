#include "ci.h"
#include <stdio.h>
#include <stdlib.h>

extern char     ci_buffer[buff] = {'\0'};
extern uint8_t  ci_buffer_pos = 0;

extern char     ci_actual[buff] = {'\0'};
extern uint8_t  ci_actual_pos = 0;



// read characters to buffer and return 1 if '\n\r' was recieved  


int8_t ci_input(char charact)
{
  switch (charact)
  {
    case '\n' :
      if ( ci_buffer_pos >= 1)
      {
		if ( ci_buffer[ci_buffer_pos -1]  == '\r'){
		  ci_buffer[ci_buffer_pos] = 0;
		  ci_buffer_pos-- ;
		  return 1;
		  break;  
		}
	  }else{
		return -1;
      }
    break;
        
    default   :  
      if (ci_buffer_pos < buff)
      {
        ci_buffer_pos++;
        ci_buffer[ci_buffer_pos] = charact;
	  }
	  else
	  {
		return -1;
	  }
   }
   return 0;
}


// fint next "Space" in buffer starting from "ci_actual_pos"  
int8_t ci_next()
{
  uint8_t pos = ci_actual_pos;

  while ( ci_buffer[pos] != ':' )  {
	pos++;
	if (pos > buff){
	  return -1;
    }
  } 
  
  return pos;
}

// read integer 
int16_t ci_read_int()
{
  int8_t pos = ci_next();
  int8_t n = 0;
  
  if (pos <= 0) {
	return -1;
  }else{
	
	for( n=0 ; n<buff ; n++){
	   ci_actual[n]= '\0';
     }
	  
    for ( n=0 ; n<( pos - ci_actual_pos); n++){
	  ci_actual[n] =  ci_buffer[ ci_actual_pos+n];
	}
   return atoi(ci_actual);
  }
}

// read String

