# TinyJsonParse
C++初学者的一个练手小项目

Jstruct类为储存管理解析之后的key value；
Value类是模板类继承基类Baseinterface，基类声名了各种可能的类型转化函数涵盖了需要的数据类型，子类重写对应转换函数，可以实现以返回值“重载函数”
Parse类做负责解析工作，并将结果保存到Jstruct对象的引用中。
（已有代码还有众多问题待解决，NULL的处理，多重Json对象嵌套的处理不太优雅；下一步实现反向解析）
