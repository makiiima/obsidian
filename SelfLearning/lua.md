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

| �������� | ����                                                         |
| :------- | :----------------------------------------------------------- |
| nil      | �����򵥣�ֻ��ֵnil���ڸ��࣬��ʾһ����Чֵ�����������ʽ���൱��false���� |
| boolean  | ��������ֵ��false��true��                                    |
| number   | ��ʾ˫�������͵�ʵ������                                     |
| string   | �ַ�����һ��˫���Ż���������ʾ                             |
| function | �� C �� Lua ��д�ĺ���                                       |
| userdata | ��ʾ����洢�ڱ����е�C���ݽṹ                              |
| thread   | ��ʾִ�еĶ�����·������ִ��Эͬ����                         |
| table    | Lua �еı�table����ʵ��һ��"��������"��associative arrays����������������������֡��ַ���������͡��� Lua �table �Ĵ�����ͨ��"������ʽ"����ɣ���򵥹�����ʽ��{}����������һ���ձ� |
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

## Function

- define
  - `optional_function_scope`: default to be global, you can use `local`
  - `result_params_comma_separated`: return value, functions in lua can return several values
```lua
optional_function_scope function function_name(arg1,arg2,arg3...)
    function_body
    return result_params_comma_separated
end
```
- varible parameters
use `...` represents all varible parameters
```lua
function add(...)
local s = 0
  for i, v in ipairs{...} do
    s = s + v
  end
  return s
end
print(add(3,4,5,6,7)) -->25
```

