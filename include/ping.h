/* ping.h */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>




enum e_type {
    unassigned,
    echo, 
    echoreply
};
typedef enum e_type type;



//This will contain the data in more detail of the ICMP packet
struct __attribute ((packed)) s_rawicmp {
    int8_t type;
    int8_t code;
    int16_t checksum;
    int8_t data[]; 

}; 


typedef struct s_rawicmp ricmp;

//below is the struct for the header and data part of the ICMP packet
struct s_icmp {
    type kind;
    int8_t *data;
    int16_t size;
};
typedef struct s_icmp icmp;

//Old version below
// struct s_icmp {
// int8_t type;
// int8_t code;
// int16_t checksum;
// int8_t *data;

// };




int main(int, char**);
void copy(int8_t*, int8_t*, int16_t);


icmp *mkicmp(type, int8_t*, int16_t);
int8_t *evalicmp(icmp*);
void showicmp(icmp*);


/*


 ICMP header format 
 Offset 	Octet 	?0? 	\1\ 	/2/ 	|3|
 ___________________________________________________
Octet 	Bit 	?0 	1 	2 	3 	4 	5 	6 	7 ?	\8 	9 	10 	11 	12 	13 	14 	15 \	/16 17 	18 	19 	20 	21 	22 	23 /
|24 	25 	26 	27 	28 	29 	30 	31|
_____________________________________________
0 	0 	Type 	Code 	Checksum
_____________________________________
4 	32 	Rest of Header

Type: 8 bits
    ICMP type, see § Control messages.
Code: 8 bits
    ICMP subtype, see § Control messages.
Checksum: 16 bits
    Internet checksum[7] for error checking, calculated from the ICMP header and data with value 0 substituted for this field.
Rest of Header: 32 bits
    Four-byte field, contents vary based on the ICMP type and code.



*/
