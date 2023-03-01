# Java Programming

## W1

- Java is type-safe

## W2

- 语句 `System.out.println(4+8+"Hello,world!");` 的输出结果是`12Hello,world!`
- 堆中存放对象, 栈中存放基本数据类型和堆中对象的引用
- java中没有float类型
- java中null为小写(所有保留字都为小写)
- java中char表示单字母需要用双引号`char a = 'c'`
- byte取值范围-128~127
- 标识符可以是中文和$, `goto`和`const`没啥用但是也不能作标识符
- string结尾没有`\0`, 编译器可以自行判断字符串结尾
- 成员变量可以默认初始化, 局部变量必须手动初始化
- `protected`成员变量只能被类自己, 子类以及包内其他类访问
- `public`->自己, 子类, 包内, 其他包
- `private`->只能自己
- `default`->自己和包内
- `static` method 无法使用`this` 访问非 `static` 变量
- 