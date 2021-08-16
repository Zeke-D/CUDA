/* 
 * caesar.c
 *
 * Decrypt the given ciphertext to find the encrypted plaintext. 
 *
 * Compile with: gcc -o caesar caesar.c
 */

#include <stdio.h>
#include <string.h>

int main() {
    char msg[] = "dahhk pdana cajanwh gajkxe";
	
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < strlen(msg); j++) {
			printf("%c", ((int) msg[j] - (int) 'a' + i) % 26 + (int) 'a');
		} 
		printf("\n");
	}
	
    return 0;
}
