#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include "Json.h"


// �ṹ�����ڴ洢�����в�����ֵ
struct CommandLineArgs {
	FILE* input;         // ������
	FILE* output;        // �����
	int compress;        // �Ƿ�ѹ��
	int format;          // �Ƿ��ʽ��
};

// ��������
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // ���ñ��ػ�������֧�ֿ��ַ�
    struct CommandLineArgs args = parseCommandLineArgs(argc, argv);
    // �������������
    // Ĭ��Ϊ��׼�������
	setOutputStream(args.output);
	setInputStream(args.input);
    //����Json
    struct JsonVal* json = parseValue();
    if (args.compress) {
        printJsonVal(json);
    }
    else if (args.format) {
        printfJsonVal(json, 0);
    }

    destoryJsonVal(json);
    if (args.input != stdin) {
        fclose(args.input);
    }
    if (args.output != stdout) {
        fclose(args.output);
    }
	return 0;
}

// �������壺���������в���
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]) {
    struct CommandLineArgs args;

    // ��ʼ���ṹ���Ա
    args.input = stdin;
    args.output = stdout;
    args.compress = 0;
    args.format = 1;

    // ����Ƿ��Ѿ�������--format��--compress
    int formatSeen = 0;
    int compressSeen = 0;
    // ���������в���
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-of") == 0) {
            // ָ�������
            if (i + 1 < argc) {
                args.output = fopen(argv[i + 1], "w");
                if (args.output == NULL) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                i++; // ������һ����������Ϊ�����ļ�·��
            }
            else {
                fprintf(stderr, "Error: --output option requires a file path.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-if") == 0) {
            // ָ��������
            if (i + 1 < argc) {
                args.input = fopen(argv[i + 1], "r");
                if (args.input == NULL) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                i++; // ������һ����������Ϊ�����ļ�·��
            }
            else {
                fprintf(stderr, "Error: --input option requires a file path.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--compress") == 0 || strcmp(argv[i], "-c") == 0) {
            // ѹ����ʽ���Json
            if (formatSeen) {
                fprintf(stderr, "Error: --compress and --format cannot be used together.\n");
                exit(EXIT_FAILURE);
            }
            args.compress = 1;
            args.format = 0;
            compressSeen = 1;
        }
        else if (strcmp(argv[i], "--format") == 0 || strcmp(argv[i], "-f") == 0) {
            // ��ʽ�����Json
            if (compressSeen) {
                fprintf(stderr, "Error: --compress and --format cannot be used together.\n");
                exit(EXIT_FAILURE);
            }
            args.format = 1;
            formatSeen = 1;
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return args;
}