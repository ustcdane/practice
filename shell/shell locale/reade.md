## 查看编码
locale 命令查看编码：

locale 

> 
LANG=en_US.UTF-8
LC_CTYPE="en_US.UTF-8"
LC_NUMERIC="en_US.UTF-8"
LC_TIME="en_US.UTF-8"
LC_COLLATE="en_US.UTF-8"
LC_MONETARY="en_US.UTF-8"
LC_MESSAGES="en_US.UTF-8"
LC_PAPER="en_US.UTF-8"
LC_NAME="en_US.UTF-8"
LC_ADDRESS="en_US.UTF-8"
LC_TELEPHONE="en_US.UTF-8"
LC_MEASUREMENT="en_US.UTF-8"
LC_IDENTIFICATION="en_US.UTF-8"
LC_ALL=




## 修改系统编码
所有用户——/etc/profile

单个用户——其他shell相关配置文件

可以的单独修改每个 LC_XXX, 也可以修改 LANG 或 LC_ALL 使所有的生效，优先级关系：

LC_ALL > LC_XXX > LANG

vi /etc/profile

#export LC_ALL="zh_CN.GBK"
export LANG="zh_CN.GBK"

修改公共配置文件（如 /etc/profile）时最好不要设置 LC_ALL，因为优先级的关系，即使普通用户设置了不同的 LC_XXX，这个设置也不会生效，建议设置在公共配置文件（如 /etc/profile）中设置  LANG。

## 编码遇到的坑

查看系统编码
locale 

> 
LANG=en_US.UTF-8
LC_CTYPE="en_US.UTF-8"
LC_NUMERIC="en_US.UTF-8"
LC_TIME="en_US.UTF-8"
LC_COLLATE="en_US.UTF-8"
LC_MONETARY="en_US.UTF-8"
LC_MESSAGES="en_US.UTF-8"
LC_PAPER="en_US.UTF-8"
LC_NAME="en_US.UTF-8"
LC_ADDRESS="en_US.UTF-8"
LC_TELEPHONE="en_US.UTF-8"
LC_MEASUREMENT="en_US.UTF-8"
LC_IDENTIFICATION="en_US.UTF-8"
LC_ALL=
 

sh lang_test.sh

由于编码问题导致awk、sed处理文件有问题。
gbk.tmp 行数不同。

echo "abc哈哈ａｂ" | LC_ALL='zh_CN.GBK' awk '{print substr($1, 6,1)}'

输出：ａ

echo "abc哈哈ａｂ" | LC_ALL='en_US.UTF-8' awk '{print substr($1, 6,1)}'

输出：空白