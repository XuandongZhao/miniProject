将源码写入mycode.txt中，放在文件夹“汇编exe”下，双击assembler.exe，再双击bin2hex.exe。

得到的instruct.txt是二进制机器码，new_inst.txt是十六进制机器码，可在quartus下直接复制入mif中。

若new_inst.txt中有空行，说明代码不符合如下要求，这时请打开instruct.txt查看错误原因。

对于mycode.txt的书写有以下要求：

  1 标号语句单独成行
  2 一行只写一条语句
  3 只支持“#”形式的注释，注释能出现在行尾也能单独成行
  4 间隔符支持空格和制表符两种形式
  5 除nop外，不支持伪码；浮点指令只支持lwc1,add.s,sub.s三条指令，如有其它代码还请自行译码。
  6 不支持十六进制表示立即数
  7 不保证能够查出语句的语法错误
  8 汇编流程：（1） mycode.txt经Analyze得ir_txt  //预编译阶段，去掉tab字符和注释
              （2） ir_txt经Main.cpp的assembler得instruct.txt,由MIPS汇编文件得二进制代码文件
              （3） instruct.txt与manual.txt经Check.cpp比较判断汇编结果是否正确，其中manual.txt为人工汇编结果文件,
	 	    若需要运行此步，去掉Main.cpp中main函数对check()的注释即可,此时需提供manual.txt文件。

