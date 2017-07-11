# 点名管理系统

##BUG修复
1. 2017/7/11 修复了在主菜单下任意输入非数字错误指令所造成的无限循环，使用了 (正确类型输入下cin.rdstate()值为0，错误为4 // 正确类型输入下cin值为0) 和cin.clear()清空流两个函数。

## 功能
1. 添加学生信息
2. 删除学生信息 （根据学号删除，根据姓名删除）
3. 显示学生信息
4. 修改学生信息 （根据学号修改，根据姓名修改）
5. 查找学生信息 （根据学号查找，根据姓名查找，根据Email查找，根据性别查找）
6. 点名系统 （使用rand函数进行随机点名）
7. 修改考勤信息 （按学号，按姓名）
8. 查找考勤信息 （按学号，按姓名）
9. 文件读写
10. 异常处理

## 编写特点
1. 学生信息存储使用student结构体，结构体中使用了链表
2. rand随机函数的使用
3. 类模板的使用
4. 文件读取异常处理

## 注意
1. 默认使用的是当前文件夹下 student.txt 为默认学生信息文件