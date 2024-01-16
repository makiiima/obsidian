# Java Review

1. Java is a type-safe language. T

2. Compiled Java program can be executed in any operating systems directly. F

3. 设String对象s="Hello "，运行语句`System.out.println(s.concat("world!"));`后String对象s的内容为`Hello world!`，所以语句输出为`Hello world!`。

   > 在Java中，`String` 对象是不可变的（immutable）。这意味着一旦一个 `String` 对象被创建，它的内容就不能被改变。当你对一个 `String` 对象执行操作，如 `concat()`，它实际上不会修改原始字符串，而是会创建一个新的 `String` 对象来保存修改后的字符串内容。
   >
   > 在你的例子中，`s.concat("world!")` 会创建一个新的字符串 `"Hello world!"`，但是这不会改变原始 `String` 对象 `s` 的内容。原始的 `s` 仍然是 `"Hello "`。
   >
   > 因此，当执行 `System.out.println(s.concat("world!"));` 时，会打印出新创建的字符串 `"Hello world!"`。但是，这不会改变 `s` 的值，`s` 依旧是 `"Hello "`。
   >
   > 简而言之，即使 `System.out.println` 输出的是 `"Hello world!"`，`String` 对象 `s` 的内容在这之后仍然是 `"Hello "`。

4. Some Java objects are put in the heap, while some are in stack. F

   > Heap:
   >
   > - objects, object members, garbage
   >
   > Stack:
   >
   > - **Local Variables**, **Method Call Stack**, **Object References**, **Scope and Lifetime**

5. A wrapper is used when you want to treat a primitive like an object. T

6. Which statement below is incorrect:

   A.

   float a = 2.0

   B.

   double b=2.0

   C.

   int c=2

   D.

   long d=2

   > A. `float a = 2.0`
   >
   > 在Java中，当你写`2.0`而没有任何后缀时，它默认被视为`double`类型的字面量。因此，尝试将一个`double`类型的字面量赋值给一个`float`类型的变量会导致编译错误，除非你进行显式的类型转换或使用`float`字面量的后缀`f`或`F`。正确的写法应该是`float a = 2.0f`或`float a = (float) 2.0`。

7. Which word below is NOT keyword of Java？ ( )

   A.

   const

   B.

   NULL

   C.

   false

   D.

   native

   > B
   > ![img](https://pic4.zhimg.com/v2-b85c894b2e2ced23284d3dd412853b4b_b.jpg)

8. Which line below will not generate warning or error when compiling? ( )

   A.

   float f = 1.3;

   B.

   char c = "a";

   C.

   byte b = 257;

   D.

   int i = 10;

   > A. `float f = 1.3;`
   >
   > 这行代码会产生编译错误。在Java中，小数默认被视为`double`类型。要将小数赋值给`float`类型的变量，需要在数字后面加上`f`或`F`。正确的写法应该是`float f = 1.3f;`。
   >
   > B. `char c = "a";`
   >
   > 这行代码也会产生编译错误。在Java中，单字符用单引号`'`表示，而双引号`"`用于表示字符串。正确的写法应该是`char c = 'a';`。
   >
   > C. `byte b = 257;`
   >
   > 这行代码会产生编译错误。`byte`类型的数据范围是-128到127。`257`超出了这个范围，因此不能直接赋值给`byte`类型的变量。
   >
   > D. `int i = 10;`
   >
   > 这行代码是正确的。整数`10`可以直接赋值给`int`类型的变量。
   > D

9. Which of the following statements is **NOT** true?

   A.

   `Strings` can be initialized using the = operator with a string literal value.

   B.

   The `toString()` method can be used to return a String value from an object of any class.

   C.

   All strings are terminated with a `null` (‘\0’) character.

   D.

   It is impossible to change the contents of a `String` object.

   > 
   > The statement that is NOT true among the provided options is:
   >
   > C. All strings are terminated with a null (‘\0’) character.
   >
   > In Java, strings are not terminated with a null character. This concept of null-terminated strings is common in languages like C, but Java strings are handled differently. In Java, a `String` object stores its length, so it doesn't need a null character to mark the end of the string. The length of the string can be obtained using the `.length()` method on a `String` object.
   >
   > Let's briefly look at the other statements:
   >
   > A. Strings can be initialized using the = operator with a string literal value.
   >
   > - This is true. In Java, you can initialize strings using string literals, like `String s = "Hello";`.
   >
   > B. The toString() method can be used to return a String value from an object of any class.
   >
   > - This is true. In Java, the `toString()` method is defined in the `Object` class and can be overridden by any class to return a string representation of an object.
   >
   > D. It is impossible to change the contents of a String object.
   >
   > - This is true. In Java, `String` objects are immutable, meaning once a `String` object is created, its contents cannot be changed.

10. 

