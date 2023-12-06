#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include "Json.h"


// 结构体用于存储命令行参数的值
struct CommandLineArgs {
	FILE* input;         // 输入流
	FILE* output;        // 输出流
	int compress;        // 是否压缩
	int format;          // 是否格式化
};

// 函数声明
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // 设置本地化环境以支持宽字符
    struct CommandLineArgs args = parseCommandLineArgs(argc, argv);
    // 设置输入输出流
    // 默认为标准输入输出
	setOutputStream(args.output);
	setInputStream(args.input);
    //解析Json
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

// 函数定义：解析命令行参数
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]) {
    struct CommandLineArgs args;

    // 初始化结构体成员
    args.input = stdin;
    args.output = stdout;
    args.compress = 0;
    args.format = 1;

    // 标记是否已经出现了--format或--compress
    int formatSeen = 0;
    int compressSeen = 0;
    // 解析命令行参数
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-of") == 0) {
            // 指定输出流
            if (i + 1 < argc) {
                args.output = fopen(argv[i + 1], "w");
                if (args.output == NULL) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                i++; // 跳过下一个参数，因为它是文件路径
            }
            else {
                fprintf(stderr, "Error: --output option requires a file path.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-if") == 0) {
            // 指定输入流
            if (i + 1 < argc) {
                args.input = fopen(argv[i + 1], "r");
                if (args.input == NULL) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                i++; // 跳过下一个参数，因为它是文件路径
            }
            else {
                fprintf(stderr, "Error: --input option requires a file path.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--compress") == 0 || strcmp(argv[i], "-c") == 0) {
            // 压缩格式输出Json
            if (formatSeen) {
                fprintf(stderr, "Error: --compress and --format cannot be used together.\n");
                exit(EXIT_FAILURE);
            }
            args.compress = 1;
            args.format = 0;
            compressSeen = 1;
        }
        else if (strcmp(argv[i], "--format") == 0 || strcmp(argv[i], "-f") == 0) {
            // 格式化输出Json
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