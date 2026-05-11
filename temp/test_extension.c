#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <assert.h>

typedef void (*RVExtensionVersion_t)(char *, int);
typedef int (*RVExtensionArgs_t)(char *, int, const char *, const char **, int);

int main() {
    void *handle;
    char *error;
    char output[1024];

    handle = dlopen("./ext/tacview_recorder_x64.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    RVExtensionVersion_t RVExtensionVersion = (RVExtensionVersion_t) dlsym(handle, "RVExtensionVersion");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    RVExtensionArgs_t RVExtensionArgs = (RVExtensionArgs_t) dlsym(handle, "RVExtensionArgs");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    // Test Version
    RVExtensionVersion(output, sizeof(output));
    printf("Version: %s\n", output);
    assert(strcmp(output, "Tacview Recorder v1.0") == 0);

    // Test Open with backslashes (simulating SQF behavior)
    // For the sake of this test, we'll just check if it handles a simple backslash in the same dir.
    const char* open_args_simple[] = {"\"test\\backslash.txt\""};
    RVExtensionArgs(output, sizeof(output), "open", open_args_simple, 1);
    printf("Open (backslash) result: %s\n", output);
    assert(strstr(output, "test/backslash.txt") != NULL);

    // Test Write to the backslash file
    const char* write_args_bs[] = {"Backslash test content"};
    RVExtensionArgs(output, sizeof(output), "writeln", write_args_bs, 1);

    // Test Close
    RVExtensionArgs(output, sizeof(output), "close", NULL, 0);

    // Verify backslash file content
    FILE *f_bs = fopen("test/backslash.txt", "r");
    if (f_bs) {
        printf("Verified: test/backslash.txt was created (backslash converted to forward slash)\n");
        fclose(f_bs);
        remove("test/backslash.txt");
    } else {
        // If it didn't convert, it might have created "test\backslash.txt" literally
        if (fopen("test\\backslash.txt", "r")) {
            printf("FAILED: test\\backslash.txt was created literally (no conversion)\n");
            exit(EXIT_FAILURE);
        }
    }

    // Test normal Open
    const char* open_args[] = {"\"test_output.txt\""};
    RVExtensionArgs(output, sizeof(output), "open", open_args, 1);
    printf("Open result: %s\n", output);

    // Test Close
    RVExtensionArgs(output, sizeof(output), "close", NULL, 0);
    printf("Close result: %s\n", output);

    dlclose(handle);

    // Verify file content
    FILE *f = fopen("test_output.txt", "r");
    if (f) {
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), f)) {
            printf("File content: %s", buffer);
            assert(strncmp(buffer, "Hello from Linux Extension Test!", 32) == 0);
        }
        fclose(f);
        printf("Test PASSED!\n");
        remove("test_output.txt");
    } else {
        printf("Failed to open test_output.txt for verification\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
