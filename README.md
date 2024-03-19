# GIWish

## 介绍

GIWish是模拟原神祈愿的一个程序，根据官方公示的概率制作而成

## 如何编译

确保你的电脑上有CMake以及C/C++工具链和Git，运行以下命令

```
git clone https://github.com/patryyyy/GIWish.git
cd GIWish
mkdir build && cd build && cmake ..
```

根据不同的环境运行不同的命令：

若你使用的是Visual Studio，则运行`msbuild .\GIWish.sln /p:Configuration=Release`

若你使用的是Linux或者macOS，则运行`make`或者`gmake`

## 我该怎么用

如果你想更改概率等其他操作，请参阅下面的命令行参数

`--pfive=<double>`: 设置5星物品基础概率

`--pfour=<double>`: 设置4星物品基础概率

`--pthree=<double>`: 设置3星物品基础概率

`--times=<int> or -t <int>`: 设置每轮祈愿的次数

`--version or -v`: 版本信息

`--help or -?`: 帮助信息

用法示例：

```
GIWish.exe --pfive=0.6 --pfour=5.1 --pthree=94.3 -t 10
```

此命令告诉程序，将**5星物品基础概率**设置为0.6%，**4星物品基础概率**设置为5.1%，**3星物品基础概率**设置为94.3%，每轮进行10次祈愿

## 关于概率

这是通过20000000次抽取，计算GIWish的综合概率如下：

| 物品星级 | 综合概率 |
| -------- | -------- |
| 5星物品  | 1.60211% |
| 4星物品  | 12.3297% |
| 3星物品  | 86.0682% |

## 使用的第三方库

[tanakh/cmdline: A Command Line Parser](https://github.com/tanakh/cmdline) License: [BSD-3-Clause license](https://github.com/tanakh/cmdline/blob/master/LICENSE)

## 关于协议

[MIT LICENSE](https://github.com/patryyyy/GIWish/blob/main/LICENSE)