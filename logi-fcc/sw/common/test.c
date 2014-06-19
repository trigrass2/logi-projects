#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "wishbone_wrapper.h"
#include "config.h"


FILE * log_file;
char text_buffer [512] ;

enum dbg_level{
	INFO,
	WARNING, 
	ERROR
};


int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void init_test_log(){
	/*
	char buffer [256] ;	
	unsigned long int ts = time(NULL); 
	sprintf(buffer, LOG_PATH, ts);
	log_file = fopen(buffer, "w+");
	if(log_file == NULL){
		printf("Cannot create log file \n");	
	}
	fwrite("TIMESTAMP, TEST_NAME, TYPE, TEST_MSG\n", sizeof(char), 37, log_file);
	*/
}

void close_test_log(){
	/*fclose(log_file);*/
}

void test_log(enum dbg_level lvl, char * test_name, char * fmt, ...){
	int msg_size ;	
	unsigned long int ts;
	va_list args;
    	va_start(args,fmt);
	ts = time(NULL); 
	msg_size = sprintf(text_buffer, "%ld", ts);
	//fwrite(text_buffer, sizeof(char), msg_size, log_file); //writing timestamp to file
	//fwrite(",", sizeof(char), 1, log_file); 
	//fwrite(test_name, sizeof(char), strlen(test_name), log_file); //writing test name
	//fwrite(",", sizeof(char), 1, log_file); 
	msg_size = vsprintf(text_buffer, fmt, args);
	switch(lvl){
		case INFO :
			/*if(log_file != NULL){
				fwrite("INFO,", sizeof(char), 5, log_file);			
				fwrite(text_buffer, sizeof(char), msg_size, log_file);
			}*/
			printf("INFO : ");			
			vprintf(fmt,args);
			break ;
		case WARNING : 
			/*if(log_file != NULL){
				fwrite("WARNING,", sizeof(char), 8, log_file);				
				fwrite(text_buffer, sizeof(char), msg_size, log_file);
			}*/
			printf("WARNING : ");
			vprintf(fmt,args);
			break ;
		case ERROR : 			
			/*if(log_file != NULL){
				fwrite("ERROR,", sizeof(char), 6, log_file);				
				fwrite(text_buffer, sizeof(char), msg_size, log_file);
			}*/
			printf("ERROR : ");
			vprintf(fmt,args);
			break ;
		default :
			break ;	
	}
	va_end(args);
	printf("\n");
}	


int testPMOD12(){
	unsigned short int dirBuf ;
	unsigned short int valBuf ;
	dirBuf = GPIO_TEST1_DIR ;
	valBuf = GPIO_TEST1_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO0DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO0);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO0);
	/*	
	valBuf = valBuf & (~GPIO_TEST1_DIR)  ;
	if(valBuf != GPIO_TEST1_1_EXPECTED){
		test_log(ERROR, "PMOD_1_2", "Pass 1 : Expected %04x got %04x \n", (GPIO_TEST1_1_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST1_1_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_1_2", "Failure on PMOD1\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST1_1_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD2\n");		
		}	
		return -1 ;
	}
	*/
	valBuf = GPIO_TEST1_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO0);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO0);
	valBuf = valBuf & (~GPIO_TEST1_DIR)  ;
	/*	
	if(valBuf != (GPIO_TEST1_2_EXPECTED) ){
		test_log(ERROR, "PMOD_1_2", "Pass 2 : Expected %04x got %04x \n", (GPIO_TEST1_2_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST1_2_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD1\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST1_2_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD2\n");		
		}	 
		return -1 ;
	}
	*/
	dirBuf = GPIO_TEST2_DIR ;
	valBuf = GPIO_TEST2_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO0DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO0);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO0);
	/*	
	valBuf = valBuf & (~GPIO_TEST2_DIR)  ;
	if(valBuf != (GPIO_TEST2_1_EXPECTED)){
		test_log(ERROR, "PMOD_1_2", "Pass 3 : Expected %04x got %04x \n", (GPIO_TEST2_1_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST2_1_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD1\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST2_1_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD2\n");		
		}		 
		return -1 ;
	}*/
	valBuf = GPIO_TEST2_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO0);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO0);
	/*valBuf = valBuf & (~GPIO_TEST2_DIR)  ;
	if(valBuf != (GPIO_TEST2_2_EXPECTED) ){
		test_log(ERROR, "PMOD_1_2", "Pass 4 : Expected %04x got %04x \n", (GPIO_TEST2_2_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST2_2_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD1\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST2_2_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_1_2","Failure on PMOD2\n");		
		}
		return -1 ;
	}*/
	return 0 ;
}

int testPMOD34(){
	unsigned short int dirBuf ;
	unsigned short int valBuf ;
	dirBuf = GPIO_TEST1_DIR ;
	valBuf = GPIO_TEST1_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO1DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO1);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO1);
	/*valBuf = valBuf & (~GPIO_TEST1_DIR)  ;
	if(valBuf != (GPIO_TEST1_1_EXPECTED)){
		test_log(ERROR, "PMOD_3_4", "Pass 1 : Expected %04x got %04x \n", (GPIO_TEST1_1_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST1_1_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD3\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST1_1_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD4\n");		
		}		
		return -1 ;
	}*/
	valBuf = GPIO_TEST1_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO1);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO1);
	/*valBuf = valBuf & (~GPIO_TEST1_DIR)  ;
	if(valBuf != (GPIO_TEST1_2_EXPECTED) ){
		test_log(ERROR, "PMOD_3_4", "Pass 1 : Expected %04x got %04x \n", (GPIO_TEST1_2_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST1_2_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD3\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST1_2_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD4\n");		
		}
		return -1 ;
	}*/
	dirBuf = GPIO_TEST2_DIR ;
	valBuf = GPIO_TEST2_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO1DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO1);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO1);
	/*valBuf = valBuf & (~GPIO_TEST2_DIR)  ;
	if(valBuf != (GPIO_TEST2_1_EXPECTED)){
		test_log(ERROR, "PMOD_3_4", "Pass 1 : Expected %04x got %04x \n", (GPIO_TEST2_1_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST2_1_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD3\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST2_1_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD4\n");		
		}		
		return -1 ;
	}*/
	valBuf = GPIO_TEST2_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO1);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO1);
	/*valBuf = valBuf & (~GPIO_TEST2_DIR)  ;
	if(valBuf != (GPIO_TEST2_2_EXPECTED) ){
		test_log(ERROR, "PMOD_3_4", "Pass 1 : Expected %04x got %04x \n", (GPIO_TEST2_2_EXPECTED), valBuf);
		if((valBuf & 0x00FF) != ((GPIO_TEST2_2_EXPECTED) & 0x00FF)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD3\n");		
		}
		if((valBuf & 0xFF00) != ((GPIO_TEST2_2_EXPECTED) & 0xFF00)){
			test_log(ERROR, "PMOD_3_4","Failure on PMOD4\n");		
		}		
		return -1 ;
	}*/

	return 0 ;
}



int testLVDS(){
        unsigned short int write_val, read_val ;
	unsigned int result = 0 ;
        write_val = 1 << SATA_WRITE_SHIFT ;
        wishbone_write((unsigned char *) &write_val, 2, REG0);
        return result ;
}


int test_arduino_port(){
	unsigned short int dirBuf ;
	unsigned short int valBuf ;
	int test_result = 0 ;
	dirBuf = ARD_TEST1_DIR ;
	valBuf = ARD_TEST1_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO2DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO2);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO2);
	/*valBuf = (valBuf & (~ARD_TEST1_DIR)) & ARD_MASK  ;
	if(valBuf != ARD_TEST1_1_EXPECTED){
		test_log(ERROR, "ARDUINO ", "Failure on Arduino connector test");
		test_log(ERROR, "ARDUINO", "Pass 1 : Expected %04x got %04x \n", (ARD_TEST1_1_EXPECTED), valBuf);
		test_result =  -1 ;
	}*/
	valBuf = ARD_TEST1_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO2);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO2);
	/*valBuf = (valBuf & (~ARD_TEST1_DIR)) & ARD_MASK  ;
	if(valBuf != (ARD_TEST1_2_EXPECTED) ){
		test_log(ERROR, "ARDUINO ", "Failure on Arduino connector test");
		test_log(ERROR, "ARDUINO", "Pass 2 : Expected %04x got %04x \n", (ARD_TEST1_2_EXPECTED), valBuf); 
		test_result =  -1 ;
	}*/

	dirBuf = ARD_TEST2_DIR ;
	valBuf = ARD_TEST2_1 ; 
	wishbone_write((unsigned char *) &dirBuf, 2, GPIO2DIR);
	wishbone_write((unsigned char *)&valBuf, 2, GPIO2);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO2);
	/*valBuf = (valBuf & (~ARD_TEST2_DIR)) & ARD_MASK  ;
	if(valBuf != (ARD_TEST2_1_EXPECTED)){
		test_log(ERROR, "ARDUINO ", "Failure on Arduino connector test");
		test_log(ERROR, "ARDUINO", "Pass 3 : Expected %04x got %04x \n", (ARD_TEST2_1_EXPECTED), valBuf); 
		test_result =  -1 ;
	}*/
	valBuf = ARD_TEST2_2 ;
	wishbone_write((unsigned char *)&valBuf, 2, GPIO2);
	wishbone_read((unsigned char *)&valBuf, 2, GPIO2);
	/*valBuf = (valBuf & (~ARD_TEST2_DIR)) & ARD_MASK  ;
	if(valBuf != (ARD_TEST2_2_EXPECTED) ){
		test_log(ERROR, "ARDUINO ", "Failure on Arduino connector test");
		test_log(ERROR, "ARDUINO", "Pass 4 : Expected %04x got %04x \n", (ARD_TEST2_2_EXPECTED), valBuf);
		test_result =  -1 ;
	}*/
	return test_result ;

}


int main(int argc, char ** argv){
	char c [10];	
	char * argv2 [3];
	init_test_log();	
	test_log(INFO,"MAIN", "Press Enter to begin testing \n");
	while(fgets(c, 2, stdin) == NULL);
	test_log(INFO, "MAIN","----------------Loading FPGA--------------\n");	
	// load fpga
	system(LOAD_CMD);
	//
	sleep(1);
	test_log(INFO, "MAIN","-----------------Starting Test-------------\n");
	
	while(1){
		#ifdef TEST_PMOD_1_2
		testPMOD12();
		#endif

		#ifdef TEST_PMOD_3_4
		testPMOD34(); 
		#endif

		#ifdef TEST_ARD
		test_arduino_port();
		#endif

		#ifdef TEST_LVDS
		testLVDS();
		#endif
	}
	close_test_log();
	return 0 ;
	
}
