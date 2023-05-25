import tomli
import sys

config_file = "config.toml"
if len(sys.argv) == 2:
  config_file = sys.argv[1]

with open(config_file, "rb") as f:
  config = tomli.load(f)

print("#define SSID \"{}\"".format(config["wifi"]["SSID"]))
print("#define SSID_PASSWORD \"{}\"".format(config["wifi"]["password"]))
print("#define USERNAME \"{}\"".format(config["account"]["username"]))


password = config["account"]["password"]
c = int.from_bytes(password.encode("utf-8"), byteorder="big")
e = 65537
n = int(b"94dd2a8675fb779e6b9f7103698634cd400f27a154afa67af6166a43fc26417222a79506d34cacc7641946abda1785b7acf9910ad6a0978c91ec84d40b71d2891379af19ffb333e7517e390bd26ac312fe940c340466b4a5d4af1d65c3b5944078f96a1a51a5a53e4bc302818b7c9f63c4a1b07bd7d874cef1c3d4b2f5eb7871", 16)
res = pow(c, e, n)
print("#define PASSWORD \"{:x}\"".format(res))
