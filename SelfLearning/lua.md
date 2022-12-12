#lua notes

## Syntax

- comments
`--` for single-line comments

```lua
--[[
dssdd
sdadssdd
sdadjd
--]]
```
for multi-line comments

- global varibles
By default, varibles are considered global.
Global varibles do not need to be declared.
Accessing a no initialized global varible will get `nil`.
To delete a global varible, just let it be `nil`.

## DataType

| 数据类型 | 描述                                                         |
| :------- | :----------------------------------------------------------- |
| nil      | 这个最简单，只有值nil属于该类，表示一个无效值（在条件表达式中相当于false）。 |
| boolean  | 包含两个值：false和true。                                    |
| number   | 表示双精度类型的实浮点数                                     |
| string   | 字符串由一对双引号或单引号来表示                             |
| function | 由 C 或 Lua 编写的函数                                       |
| userdata | 表示任意存储在变量中的C数据结构                              |
| thread   | 表示执行的独立线路，用于执行协同程序                         |
| table    | Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字、字符串或表类型。在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。 |
```lua
--empty table
local tbl1={}

--initialzation
local tbl2={"apple","pear","orange"}

--table can be map
a={}
a["key"] = "value"
key = 10
a[key] = 22
a[key] = a[key] + 11
for k,v in pairs(a) do
    print(k .. ":" ..v)
end
```
In lua, default initial index is 1 (not 0)

## Varibles
- global
- local
- field in table
```lua
--index
t[i]
t.i --a simplified notation when the index is of string type
gettable_event(t,i) --index access is essentially like this function call
```
## Control

### loop
- while
  ```lua
  while(condition)
  do
      statements
  end
```
- for
  ```lua
  for var=exp1,exp2,exp3 do
      statements
  end
```
`var` from `exp1` to `exp2`, incrementing with `var3` as a step. `var3` is default to be 1
- generic for loops
  ```lua
  a={"one","two","three"}
  for i,v in ipairs(a) do
      print(i,v)
  end
  --i is index and v is the value of the corresponding element
```
- repeat ... until
  ```lua
  repeat
      statements
  until(condition)
```

loop control statements
- break
- goto
  ```lua
  goto Label
--labels are like:
::Label::
```
use `goto` to implement `continue`
```lua
for i=1,3 do
    if i<=2 then
        print(i,"yes continue")
        goto continue
    end
    print(i,"no continue")
    ::continue::
    print([[i'm end]])
end
```
