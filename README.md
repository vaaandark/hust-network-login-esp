把 [hust-network-login-sh](https://github.com/jyi2ya/hust-network-login-sh) 用 Arduino esp8266 抄了一遍

# HUST-Network-Login-ESP

比极简主义更极简的华中科技大学校园网络认证工具，通过先计算加密再烧录到 nodemcu 的方法实现了加密认证。

## 需求

有些路由器没有很好的刷机方案，但我们有自动校园网认证的需求，难道要去海鲜市场再买一个可以刷机的路由器吗？

当然不用，你可以使用成本 10 元都不需要的 **nodemcu esp8266** 辅助路由器认证。

## 依赖

- arduino-cli（可选，GUI 的 Arduino IDE 也可以）
- 可以编译烧录 esp8266 的库：
```console
$ arduino-cli core list
ID              Installed Latest Name
esp8266:esp8266 3.0.2     3.0.2  esp8266
```

## 编译烧录

`config.toml`是配置文件，你需要补充你的 WIFI 名字和密码、你的校园网帐号和密码。

编译并烧录到`/dev/ttyUSB0`

```console
$ bash build.sh /dev/ttyUSB0
```

查看运行日志：

```console
$ bash monitor.sh /dev/ttyUSB0
```

## 使用

配置好所需信息后编译烧录，在你的路由器开机时，给 nodemcu 插上电即可。

连接成功后，程序将会每间隔 15s 测试一次网络连通性。如果无法连接则进行重新登陆。
