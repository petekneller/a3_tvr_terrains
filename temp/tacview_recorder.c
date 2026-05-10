#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__attribute__((dllexport)) void RVExtension(char *output, int outputSize, const char *function);
__attribute__((dllexport)) int RVExtensionArgs(char *output, int outputSize, const char *function, const char **argv, int argc);
__attribute__((dllexport)) void RVExtensionVersion(char *output, int outputSize);

FILE* fptr = 0;

void stripLeadingTrailingQuotes(const char* in, char* out)
{
	if (in[0] == '"')
	{
		memcpy(out, &in[1], strlen(in)-2);
	} 
	else 
	{
		memcpy(out, &in[0], strlen(in));
	}
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

		char msg[256];
		sprintf(msg, "Opened file with handle %u at path %s", fptr, filename);
		strncpy(output, msg, outputSize);
	} else if (strcmp("close", function) == 0) {
		if (fptr != 0)
		{
			fclose(fptr);
		}

		char msg[100];
		sprintf(msg, "Closed file handle %d", fptr);
		strncpy(output, msg, outputSize);
		fptr = 0;
	} else if (strcmp("writeln", function) == 0) {
		char msg[100];
		if (argv[0][0] != '"')
		{
			fputs(argv[0], fptr);
			fputs("\n", fptr);
			fflush(fptr);
			sprintf(msg, "writeln wrote %d chars", strlen(argv[0]));
		} 
		else
		{
			sprintf(msg, "writeln ignored input as it began with a quote char - do you need to use 'text' on the input?");
		}
		strncpy(output, msg, outputSize);
	} else {
		char msg[100];
		sprintf(msg, "Unrecognised function %s", function);
		strncpy(output, msg, outputSize);
	}
	return 0;
}

void RVExtensionVersion(char *output, int outputSize)
{
	char version[] = "Tacview Recorder v1.0";
	strncpy(output, version, outputSize);
}