#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #define RV_EXTENSION_EXPORT __declspec(dllexport)
#else
    #define RV_EXTENSION_EXPORT __attribute__((visibility("default")))
#endif

RV_EXTENSION_EXPORT void RVExtension(char *output, int outputSize, const char *function);
RV_EXTENSION_EXPORT int RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc);
RV_EXTENSION_EXPORT void RVExtensionVersion(char *output, int outputSize);

FILE* fptr = 0;

void stripLeadingTrailingQuotes(const char* in, char* out)
{
	size_t len = strlen(in);
	if (len >= 2 && in[0] == '"' && in[len-1] == '"')
	{
		memcpy(out, &in[1], len - 2);
		out[len - 2] = '\0';
	} 
	else 
	{
		memcpy(out, &in[0], len);
		out[len] = '\0';
	}

#ifndef _WIN32
	// Convert backslashes to forward slashes for Linux compatibility
	for (char* p = out; *p; p++)
	{
		if (*p == '\\') *p = '/';
	}
#endif
}

void RVExtension(char *output, int outputSize, const char *function)
{
	strncpy(output, "The 0-args entrypoint is unimplemented", outputSize);
}

int RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc)
{
	if (strcmp("open", function) == 0) {

		char filename[256];
		memset(filename, 0, 256);
		stripLeadingTrailingQuotes(argv[0], filename);
		fptr = fopen(filename, "a");

		char msg[512];
		snprintf(msg, sizeof(msg), "Opened file with handle %p at path %s", (void*)fptr, filename);
		strncpy(output, msg, outputSize);
	} else if (strcmp("close", function) == 0) {
		char msg[100];
		if (fptr != 0)
		{
			fclose(fptr);
			snprintf(msg, sizeof(msg), "Closed file handle %p", (void*)fptr);
		}
		else
		{
			snprintf(msg, sizeof(msg), "No file handle to close");
		}

		strncpy(output, msg, outputSize);
		fptr = 0;
	} else if (strcmp("writeln", function) == 0) {
		char msg[100];
		if (argv[0][0] != '"')
		{
			fputs(argv[0], fptr);
			fputs("\n", fptr);
			fflush(fptr);
			snprintf(msg, sizeof(msg), "writeln wrote %zu chars", strlen(argv[0]));
		} 
		else
		{
			snprintf(msg, sizeof(msg), "writeln ignored input as it began with a quote char - do you need to use 'text' on the input?");
		}
		strncpy(output, msg, outputSize);
	} else {
		char msg[100];
		snprintf(msg, sizeof(msg), "Unrecognised function %s", function);
		strncpy(output, msg, outputSize);
	}
	return 0;
}

void RVExtensionVersion(char *output, int outputSize)
{
	char version[] = "Tacview Recorder v1.0";
	strncpy(output, version, outputSize);
}