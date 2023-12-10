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
    int utf8Text;         // �Ƿ�Ϊutf-8 �ı� ��������Դ����ʱɾ���м��ļ�
    char* convertCacheFilePath; // Ϊutf-8�ı�ʱת��Ϊgbk��ʽʱ���ɵ���ʱ�ļ�
    char* outputFilePath; // ��Ҫ����ļ�·���� ��Ϊutf-8�ı�ʱ����ת����utf-8�ı�

};

// ��������
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]);

int main(const int argc, char* argv[]) {
	// setlocale(LC_ALL, ""); // ���ñ��ػ�������֧�ֿ��ַ�
    const struct CommandLineArgs args = parseCommandLineArgs(argc, argv);
    // �������������
    // Ĭ��Ϊ��׼�������
    setInputStream(args.input);
	setOutputStream(args.output);
	
    //����Json
    const struct JsonVal* json = parseValue();
    if (args.compress) {
        printJsonVal(json);
    }
    else if (args.format) {
        printfJsonVal(json, 0);
    }

    //destoryJsonVal(json);
    if (args.input != stdin) {
        fclose(args.input);
    }
    if (args.output != stdout) {
        fclose(args.output);
        if(args.utf8Text) {
            convertGbkToUtf8(args.output);
        }
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
    args.utf8Text = 0;
    args.convertCacheFilePath = "";
    // ����Ƿ��Ѿ�������--format��--compress
    int formatSeen = 0;
    int compressSeen = 0;
    // ���������в���
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-of") == 0) {
            // ָ�������
            if (i + 1 < argc) {
                printf("Output: %s\n", argv[i + 1]);
                args.output = fopen(argv[i + 1], "w");
                args.outputFilePath = argv[i+1];
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
                FILE* f = fopen(argv[i + 1], "r");
                args.convertCacheFilePath = "__cache.json";
                if(isUtf8(f)) {
                    printf("INFO: Is UTF-8 Text\n");
                    args.input = convertUtf8ToGbk(f,args.convertCacheFilePath);
                    args.utf8Text = 1;
                }else {
                    args.input = fopen(argv[i + 1], "r");
                }
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
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("�÷���json [ѡ��]...\n");
            printf("�������н����͸�ʽ��JSON���ݣ���ѡ��ѹ�����ʽ�������\n\n");

            printf("��ѡ���ǿ���Բ������ڶ�ѡ��Ҳ��ǿ���Եġ�\n");
            printf("    -if, --input ָ�������ļ���Ĭ��Ϊ��׼���룩\n");
            printf("    -of, --output ָ������ļ���Ĭ��Ϊ��׼�����\n");
            printf("    -f, --format ʹ���������������ʽ����JSON\n");
            printf("    -c, --compress ���ѹ����JSON\n");
            printf("    -h, --help ��ʾ�˰������˳�\n\n");

            printf("ʾ����\n");
            printf("    json -if input.json -of output.json -f\n");
            printf("    json --input=input.json --output=output.json --compress\n\n");

            printf("���δָ�����������ļ��������Ĭ��ʹ�ñ�׼������׼�����\n\n");

            printf("ע�⣺--compress �� --format ѡ���ͬʱʹ�á�\n");
            exit(0);
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return args;
}