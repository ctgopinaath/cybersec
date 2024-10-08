#include <stdio.h>
#include <string.h>

void vulnerable_function(char *str) {
    char buffer[10];  // small buffer size
    size_t input_length = strlen(str);  // Get the length of the input

    // Display the address of the input string
    printf("Input address: %p\n", (void*)str);
    
    // Check if the input length exceeds the buffer size
    if (input_length >= sizeof(buffer)) {
        // Calculate the address of the exceeded bytes
        void *exceeded_address = (void*)(str + sizeof(buffer));
        printf("Buffer overflow detected!\n");
        printf("Exceeded address: %p\n", exceeded_address);
        printf("Input length: %zu, Buffer size: %zu\n", input_length, sizeof(buffer));
    }

    // Display addresses of each byte of the input string
    printf("\nActual Buffer Addresses:\n");
    for (size_t i = 0; i < sizeof(buffer); i++) {
        if (i < input_length) {
            printf("Byte %zu: Value: '%c', Address: %p\n", i, str[i], (void*)&str[i]);
        } else {
            printf("Byte %zu: Value: ' ', Address: %p (unused)\n", i, (void*)&str[i]);
        }
    }

    // Display exceeded addresses if there are any
    if (input_length >= sizeof(buffer)) {
        printf("\nExceeded Buffer Addresses:\n");
        for (size_t i = sizeof(buffer); i < input_length; i++) {
            printf("Byte %zu: Value: '%c', Address: %p\n", i, str[i], (void*)&str[i]);
        }
    }

    // Unsafe copy
    strcpy(buffer, str);  // This is still unsafe and will cause overflow if input is too long
    printf("\nBuffer: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        vulnerable_function(argv[1]);
    } else {
        printf("Usage: %s <input>\n", argv[0]);
    }
    return 0;
}
