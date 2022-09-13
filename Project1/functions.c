/******************************************************************************
 * @file: functions.c
 *
 * lunzmann
 * lunzmann
 * 908 200 8187
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Jacob Lunzmann (lunzmann@wisc.edu)
 * @modified: 10/7/21
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...
int isLetter(char character) {
	if(character > 64 && character < 91){
	    return 1;
	}
	if(character > 96 && character < 123){
	    return 1;
	}
	return 0;

}

int isNumber(char character) {
	if(character > 47 && character < 58){
	    return 1;
	}
	return 0;
}
/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of
 * these conditions are not met. Only print the first applicable error
 * message.
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    if((user[0] < 65 || user[0] > 122) || (user[0] > 90 && user[0] < 97)){
	printf(ERROR_01_USER_START_INVALID);
	return 0;
    }

    int size = 0;
    for(int i = 0; i < len; i++){
	if(user[i] == '\0'){
	    break;
	}
	size = size + 1;
    }

    if(size > 32){
	printf(ERROR_02_USER_LEN_INVALID);
	return 0;
    }

    for(int i = 0; i < size; i++){
	if(isLetter(user[i]) == 0 && isNumber(user[i]) == 0 && user[i] != '_'){
	    printf(ERROR_03_USER_CHARS_INVALID);
	    return 0;
	}
    }

    dbgprintf("This line only prints if DEBUG is set to 1\n");
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    if(email[0] == '@' || email[0] == '.'){
	printf(ERROR_04_EMAIL_MISSING_NAME);
	return 0;
    }

    if(isLetter(email[0]) == 0){
	printf(ERROR_05_EMAIL_START_INVALID);
	return 0;
    }

    int size = 0;
    for(int i = 0; i < len; i++){
	if(email[i] == '@'){
	    break;
	}
	if(email[i] == '.'){
	    break;
	}
	size = size + 1;
    }


    if(size > 32){
	printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
	return 0;
    }

    for(int i = 0; i < size; i++){
	if(isLetter(email[i]) == 0 && isNumber(email[i]) == 0){
            printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
	    return 0;
	}
    }

    if(email[size] != '@'){
	printf(ERROR_08_EMAIL_MISSING_SYMBOL);
	return 0;
    }

    if(email[size+1] == '.'){
	printf(ERROR_09_EMAIL_MISSING_DOMAIN);
	return 0;
    }

    int endIndex = 0;
    for(int i = 0; i < len; i++){
	if(email[i] == '\0'){
	    break;
	}
	endIndex = endIndex + 1;
    }
    int domainSize = endIndex - 4 - size - 1;

    if(domainSize > 64){
	printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
	return 0;
    }

    if(isLetter(email[size + 1]) == 0){
	printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
	return 0;
    }

    for(int i = size + 1; i < endIndex - 4; i++){
        if(email[i] == '.'){
	    if(isLetter(email[i+1]) == 0){
		printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
		return 0;
	    }
	}
    }

    for(int i = size + 1; i < endIndex - 4; i++){
	if(isLetter(email[i]) == 0 && isNumber(email[i]) == 0 && email[i] != '.'){
	    printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
	    return 0;
	}
    }

    if(email[endIndex - 4] != '.'){
	printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
	return 0;
    }

    if(!(email[endIndex - 3] == 'c' && email[endIndex - 2] == 'o' && email[endIndex - 1] == 'm')){
	if(!(email[endIndex - 3] == 'e' && email[endIndex - 2] == 'd' && email[endIndex - 1] == 'u')){
	     if(!(email[endIndex - 3] == 'n' && email[endIndex - 2] == 'e' && email[endIndex] == 't')){
		printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
		return 0;
	     }
	}
    }

    /* END MODIFYING CODE HERE */
    
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int size = 0;
    for(int i = 0; i < len; i++){
	if(pwd[i] == '\0'){
	    break;
	}
	size = size + 1;
    }

    for(int i = 0; i < size; i++){
	if(pwd[i] == ' '){
	    printf(ERROR_14_PWD_SPACES_INVALID);
	    return 0;
	}
    }

    if(size < 8){
	printf(ERROR_15_PWD_MIN_LEN_INVALID);
	return 0;
    }

    if(size > 16){
	printf(ERROR_16_PWD_MAX_LEN_INVALID);
	return 0;
    }

    for(int i = 0; i < size; i++){
	if(pwd[i] > 64 && pwd[i] < 91){
	    break;
	}
	if(i == size){
	    printf(ERROR_17_PWD_MIN_UPPER_INVALID);
	    return 0;
	}
    }

    for(int i = 0; i < size; i++){
	if(pwd[i] > 96 &&  pwd[i] < 123){
	    break;
	}
	if(i == size){
	    printf(ERROR_18_PWD_MIN_LOWER_INVALID);
	    return 0;
	}
    }
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {

    /* BEGIN MODIFYING CODE HERE */
    int size1 = 0;
    int size2 = 0;
    for(int i = 0; i < len1; i++){
	if(pwd1[i] == '\0'){
	    break;
	}
	size1 = size1 + 1;
    }

    for(int i = 0; i < len2; i++){
	if(pwd2[i] == '\0'){
	    break;
	}
	size2 = size2 + 1;
    }

    if(size1 != size2){
	printf(ERROR_19_PWD_MATCH_INVALID);
	return 0;
    }

    for(int i = 0; i < size1; i++){
	if(pwd1[i] != pwd2[i]){
	    printf(ERROR_19_PWD_MATCH_INVALID);
	    return 0;
	}
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */
    for(int i = 0; i < MAX_LENGTH;i++){
	if(data[i] == '\n'){
		data[i] = '\0';
	}
    }
    /* END MODIFYING CODE HERE */
    return;
}
