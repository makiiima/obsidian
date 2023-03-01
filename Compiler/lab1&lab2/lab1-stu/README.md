## Lab-1 利用LEX计算文本文件的行数、单词和字符数

### 要求
编写一个LEX文件, 使之生成计算文件的行数、单词和字符(按顺序)并以空格为间隔输出的程序.(记得最后输出换行符) 
单词为不带标点或空格的字母和数字的序列. 标点和空白格不计算为单词.

### 样例
```bash
# test.in
```

```bash
# expect.out
0 0 0

```

```bash
# test.in
This is a test file.

It contains multiple lines,
including blank lines.

Each line has some punctuation!

```

```bash
# expect.out
6 17 106

```

其他测试用例与期望输出文件位于tests/目录下.

### 脚本用法
在**脚本所在目录**运行:
```bash
./script.sh [-rtc]
-r:  编译
-t:  进行测试
-c:  清理生成的文件
```
> 命令行参数可任意组合, 比如`./script.sh -rtc`表示先编译, 再进行测试, 最后清理生成的文件.


### 注意事项
* 本脚本假定`main` 函数直接写在lex.l中, 如果你有别的想法或者习惯, 请相应修改脚本.
* 本脚本在Linux和MacOS环境下进行过测试. 如果你使用的是其他操作系统(Windows), 请相应地修改脚本中的命令.
* 对于空文件, 我们认为行数为0. 具体可参考测试文件.
