; ModuleID = 'main'
source_filename = "main"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [5 x i8] c"\22%d\22\00", align 1

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %temp = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 250, i32* %a, align 4
  store i32 50, i32* %b, align 4
  br label %WhileCond

WhileCond:                                        ; preds = %WhileLoop, %entry
  %0 = load i32, i32* %b, align 4
  %1 = icmp ne i32 %0, 0
  br i1 %1, label %WhileLoop, label %WhileEnd

WhileLoop:                                        ; preds = %WhileCond
  %2 = load i32, i32* %b, align 4
  store i32 %2, i32* %temp, align 4
  %3 = load i32, i32* %a, align 4
  %4 = load i32, i32* %b, align 4
  %5 = srem i32 %3, %4
  store i32 %5, i32* %b, align 4
  %6 = load i32, i32* %temp, align 4
  store i32 %6, i32* %a, align 4
  br label %WhileCond

WhileEnd:                                         ; preds = %WhileCond
  %7 = load i32, i32* %a, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32 %7)
  ret i32 0
}
