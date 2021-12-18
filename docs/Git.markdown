这里下载GIT

https://git-scm.com/download/win




乱码的话
进入git安装目录，改一下配置就可以基本解决：
etc\gitconfig：
添加以下内容:
[gui]

encoding = utf-8

![zero](images/newproject.png)

这里创建项目，选一个名字


Clone Existing Repository

![zero](images/clone.png)

这里文件夹是不能先创建的

先同步一下，修改完成后，要点rescan扫描得到修改了的文件，Commit Message可以留一个信息。

stage changed后，commit。
如果你没登录，会弹出一个信息框。

git config --global user.email "c782464295@163.com"
git config --global user.name "sw"

最后一步是Push

