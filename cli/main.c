#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include "Json.h"


// 结构体用于存储命令行参数的值
struct CommandLineArgs {
    FILE* input; // 输入流
    FILE* output; // 输出流
    int compress; // 是否压缩
    int format; // 是否格式化
    // int utf8Text; // 是否为utf-8 文本 是则需资源回收时删除中间文件
    // char* convertCacheFilePath; // 为utf-8文本时转换为gbk格式时生成的临时文件
    // char* outputFilePath; // 需要输出文件路径， 当为utf-8文本时用于转换回utf-8文本
};

// 函数声明
struct CommandLineArgs parseCommandLineArgs(int argc, char* argv[]);

int main(const int argc, char* argv[]) {
    // setlocale(LC_ALL, ""); // 设置本地化环境以支持宽字符
    const struct CommandLineArgs args = parseCommandLineArgs(argc, argv);
    // 设置输入输出流
    // 默认为标准输入输出
    setInputStream(args.input);
    setOutputStream(args.output);

    //解析Json
    const struct JsonVal* json = parseValue();
    if (args.compress) { printJsonVal(json, args.output == stdout); }
    else if (args.format) { printfJsonVal(json, 0, args.output == stdout); }

    //destoryJsonVal(json);
    if (args.input != stdin) { fclose(args.input); }
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
    // args.utf8Text = 0;
    // args.convertCacheFilePath = "__cache.json";
    // 标记是否已经出现了--format或--compress
    int formatSeen = 0;
    int compressSeen = 0;
    // 解析命令行参数
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-of") == 0) {
            // 指定输出流
            if (i + 1 < argc) {
                fputs("Output: ", stdout);fputs(argv[i + 1], stdout); fputs("\n", stdout);
                args.output = fopen(argv[i + 1], "w");
                // args.outputFilePath = argv[i + 1];
                if (args.output == NULL) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                i++; // 跳过下一个参数，因为它是文件路径
            }
            else {
                fputs("Error: --output option requires a file path.\n", stderr);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-if") == 0) {
            // 指定输入流
            if (i + 1 < argc) {
                args.input = fopen(argv[i + 1], "r");
                // FILE* f = fopen(argv[i + 1], "r");

                // if (isUtf8(f)) {
                //     printf("INFO: Is UTF-8 Text\n");
                //     args.input = convertUtf8ToGbk(f);
                //     args.utf8Text = 1;
                // }
                // else { args.input = fopen(argv[i + 1], "r"); }
                if (args.input == NULL) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                i++; // 跳过下一个参数，因为它是文件路径
            }
            else {
                fputs("Error: --input option requires a file path.\n", stderr);
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "--compress") == 0 || strcmp(argv[i], "-c") == 0) {
            // 压缩格式输出Json
            if (formatSeen) {
                fputs("Error: --compress and --format cannot be used together.\n", stderr);
                exit(EXIT_FAILURE);
            }
            args.compress = 1;
            args.format = 0;
            compressSeen = 1;
        }
        else if (strcmp(argv[i], "--format") == 0 || strcmp(argv[i], "-f") == 0) {
            // 格式化输出Json
            if (compressSeen) {
                fputs("Error: --compress and --format cannot be used together.\n", stderr);
                exit(EXIT_FAILURE);
            }
            args.format = 1;
            formatSeen = 1;
        }
        else if (strcmp(argv[i], "--utf") == 0 || strcmp(argv[i], "-u") == 0) {
            // 本地字符集设置为 UTF-8
            setlocale(LC_ALL, "");
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            setlocale(LC_ALL, "");
            puts("用法：json [选项]...\n");
            puts("从输入中解析和格式化JSON数据，可选择压缩或格式化输出。\n\n");

            puts("长选项的强制性参数对于短选项也是强制性的。\n");
            puts("    -if, --input 指定输入文件（默认为标准输入）\n");
            puts("    -of, --output 指定输出文件（默认为标准输出）\n");
            puts("    -f, --format 使用树形缩进输出格式化的JSON\n");
            puts("    -c, --compress 输出压缩的JSON\n");
            puts("    -u, --utf 启用utf-8编码支持\n");
            puts("    -h, --help 显示此帮助并退出\n\n");

            puts("示例：\n");
            puts("    json -if input.json -of output.json -f\n");
            puts("    json --input=input.json --output=output.json --compress\n\n");

            puts("如果未指定输入或输出文件，则程序将默认使用标准输入或标准输出。\n\n");

            puts("注意：--compress 和 --format 选项不能同时使用。\n");
            exit(0);
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    return args;
}
