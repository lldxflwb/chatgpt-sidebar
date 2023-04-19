# Chatgpt-sidebar

这是一款划词软件，致力于做成windows上好用的划词，目前还在demo开发阶段，勉强可用

## 代理设置
目前必须设置代理，且代理类型是socks5，需要填充ip和port信息

## key
需要填入openai的key
[查询你的密钥](https://platform.openai.com/account/api-keys)

## 使用指南
一开始打软件会弹出设置界面，如下：
![设置界面](./src/setting.png)
你需要填入ip，port，和key，如何点击保存，点击关闭隐藏设置界面，然后随便选中一个文本，弹出bar窗口
![bar](./src/line.png)
在bar窗口选中关闭，即可让设置生效,然后重新打开重新，点击设置界面的关闭，隐藏信息。
选中文本，点击翻译或解释代码，即可使用

## 警告
目前处于demo阶段，欢迎完善

## SSE
chatgpt的流式接口采用server sent event的方式驱动，可以查看代码自己了解，本项目只用了流式接口