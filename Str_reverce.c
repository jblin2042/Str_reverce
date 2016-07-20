#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#if 0
a
00 00 00 11
b
00 00 11 00
a^=b
00 00 11 11
b^=a
00 00 00 11
a^=b
00 00 11 00
#endif
#define D_swap(a,b) a^=b;b^=a;a^=b
//int Strrev ( char str[] ) {
int Strrev_marco_1 ( char * const str ) {
	if ( ! str || ! * str )
		return - 1 ;

	int i = strlen ( str ) - 1 , j = 0 ;
	while ( i > j ) {
		D_swap( str [ i ] , str [ j ] );
		i -- ; j ++ ;
	}
	return 1 ;
}
int Strrev_normal_1 ( char str [ ] ) {
	if ( ! str || ! * str )
		return - 1 ;

	int str_len = strlen ( str ) ;
	char buf [ str_len + 1 ] ;
	memcpy ( buf , str , str_len + 1 ) ;
	int j = 0 ;
	while ( 0 <= str_len )
		str [ -- str_len ] = buf [ j ++ ] ;
	return 1 ;
}

int Strrev_normal_2 ( char str [ ] ) {
	if ( ! str || ! * str )
		return - 1 ;

	int len = strlen ( str ) , loop_end = len >> 1 , i = 0 ;
	for ( i = 0 ; i < loop_end ; ++ i ) {
		str [ len ] = str [ i ] ;     // str [ len ]  把結束字元拿來用 ,就不需要另外宣告 //
		str [ i ] = str [ len - 1 - i ] ;
		str [ len - 1 - i ] = str [ len ] ;
	}
	str [ len ] = 0 ;
	return 1 ;
}

void Strrev_recursion_1 ( char str [ ] , char* p_str ) {
	if ( ! * p_str )
		return ;

	char buf = * p_str ;
	* p_str ++ = 0 ;
	Strrev_recursion_1 ( str , p_str ) ;
	str [ strlen ( str ) ] = buf ;
	return ;
}

void Strrev_recursion_2 ( char str [ ] , int begin , int end ) {
	if ( ( begin >= end ) || ( 0 > begin ) || ( 0 > end ) )
		return ;

	char buf = str [ begin ] ;
	str [ begin ++ ] = 0 ;
	Strrev_recursion_2 ( str , begin , end ) ;
	str [ strlen ( str ) ] = buf ;
	return ;
}
void Strrev_recursion_3 ( char str [ ] , int begin ) {
	if ( ( ! str [ begin ] ) || ( 0 > begin ) )
		return ;

	char buf = str [ begin ] ;
	str [ begin ++ ] = 0 ;
	Strrev_recursion_3 ( str , begin ) ;
	str [ strlen ( str ) ] = buf ;
	return ;
}

#define D_max  ( 8192 +1 )
void Test_data ( char buf [ ] ) {
	char base_char [ ] = { 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' , 'Z' , '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '0' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' , 'n' , 'o' , 'p' , 'q' , 'r' , 's' , 't' , 'u' , 'v' , 'w' , 'x' , 'y' , 'z' } ;
	srand ( time ( NULL ) ) ;
	int sz = sizeof ( base_char ) - 1 ;
	int i = 0 ;
	for ( i = 0 ; i < D_max ; ++ i )
		buf [ i ] = base_char [ rand ( ) % sz ] ;

	buf [ D_max - 1 ] = 0 ;
	return ;
}
int Cmp_test ( char base_data [ ] , char cmp_data [ ] ) {
	int i = strlen ( base_data ) - 1 , j = 0 ;
	while ( i >= 0 ) {
		if ( base_data [ i -- ] != cmp_data [ j ++ ] ) {
			fprintf ( stderr , "cmp error\n" ) ;
			return - 1 ;
		}
	}
	return 1 ;
}

int main ( void ) {
	char revers_data [ D_max ] = { 0 } ;
	char base_test_data [ D_max ] = { 0 } ;
	Test_data ( base_test_data ) ;

	int rtn = 0 ;
	int data_sz = D_max ;
		//~~~~~~~~~~~~~~~~~~~~ Strrev_recursion_3 ~~~~~~~~~~~~~~~~~~~~//
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_recursion_3 ( revers_data , 0 ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
	printf ( "<Strrev_recursion_3>Cmp status :%d\n" , rtn ) ;

	//~~~~~~~~~~~~~~~~~~~~ Strrev_marco_1 ~~~~~~~~~~~~~~~~~~~~//
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_marco_1 ( revers_data ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
	printf ( "<Strrev_marco_1>Cmp status :%d\n" , rtn ) ;

	//~~~~~~~~~~~~~~~~~~~~ Strrev_normal_1 ~~~~~~~~~~~~~~~~~~~~//
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_normal_1 ( revers_data ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
	printf ( "<Strrev_normal_1>Cmp status :%d\n" , rtn ) ;

	//~~~~~~~~~~~~~~~~~~~~ Strrev_normal_2 ~~~~~~~~~~~~~~~~~~~~//
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_normal_2 ( revers_data ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
	printf ( "<Strrev_normal_2>Cmp status :%d\n" , rtn ) ;


	//~~~~~~~~~~~~~~~~~~~~ Strrev_recursion_1 ~~~~~~~~~~~~~~~~~~~~//
	char* p_str = revers_data ;
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_recursion_1 ( revers_data , p_str ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
    printf ( "<Strrev_recursion_1>Cmp status :%d\n" , rtn ) ;

	//~~~~~~~~~~~~~~~~~~~~ Strrev_recursion_2 ~~~~~~~~~~~~~~~~~~~~//
    memcpy ( revers_data , base_test_data , data_sz ) ;
    Strrev_recursion_2 ( revers_data , 0 , strlen ( revers_data ) ) ;
    rtn = Cmp_test ( base_test_data , revers_data ) ;
	printf ( "<Strrev_recursion_2>Cmp status :%d\n" , rtn ) ;
	return 0 ;
}



