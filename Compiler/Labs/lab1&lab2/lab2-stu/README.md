## Lab-2 利用LEX进行C语言关键字的大小写转换

### 要求
编写一个LEX文件, 使之可生成将C程序**注释之外**的所有关键字（保留字）均变为大写的程序.

### 样例

输入:
```c
/* This is a
   multi-line comment. */

#include <stdio.h>

int main() {
    int i;
    for(i = 0; i < 10; i++) {
        printf("Hello, world!\n");
    }
    return 0;
}

```
输出:
```c
/* This is a
   multi-line comment. */

#include <stdio.h>

INT main() {
    INT i;
    FOR(i = 0; i < 10; i++) {
        printf("Hello, world!\n");
    }
    RETURN 0;
}

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
