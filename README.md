# tldr client

## TODO

- [ ] Support subcommand, such as `tldr git clone`
- [ ] auto download tldr pages if not exist
- [ ] auto update tldr pages

## install

```shell
mkdir build && cd build
cmake ..
make
sudo make install
```

## usage

```shell
A tiny tldr client. More information: https://github.com/jiayuancs/tldr-client.
Usage:
  tldr [options] [command]

 Available options:
  -u, --update      update tldr pages
  -s, --suffix arg  specify the suffix of `tldr pages` directory, such as 
                    `-s zh` for `pages.zh`
  -v, --version     show version
  -h, --help        show this help message
```
