# tldr client

A tiny tldr client.

## Requirements

- Git

## Install

```shell
mkdir build && cd build
cmake ..
make
sudo make install
```

## Usage

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

## Basic tldr pages syntax

```markdown
# title

> description

- code description 1

`code example 1`

- code description 1

`code example 1`

```

## Extended syntax

### Title tags

The `[modified]` tag means that the page is modified from the original tldr page.

```markdown
# title [modified]
```

The `[new]` tag means that the page is new.

```markdown
# title [new]
```

### Multi-line code block

The syntax of the code block is consistent with Markdown, and we can use '\`\`\`' to insert a multi-line code block.

### Other tags

#### `<break>`

By default, lines of the same type are not separated by blank lines. To insert a blank line between lines of the same type, you can add the `<break>` tag at the end of the each line. For example:

```markdown
- code description 1 <break>
- code description 2 <break>
- code description 3 <break>
```
