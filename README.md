Liberation-android
========
Liberation-android by [Liberation](https://github.com/Razzile/Liberation).

## Usage
To use Liberation, follow these steps:
* Clone repo `git clone https://github.com/circleous/Liberation-android`,
* [Build static library](#building-liberation),
* Include `<Liberation.h>` in your c++ file,
* Link static library (liberation.a) in your project, example of use at [example/](../blob/master/example/).
 
## Synopsis
```Logos
#include <Liberation.h>

Patch *Patch::Setup(void* _target, char *data, size_t len);
Patch *Patch::Setup(void* _target, uint32_t data);
Patch *Patch::Setup(void* _target, std::string data);
void Apply();
void Reset();
```

## Example
Example of use at [example/](../blob/master/example/) folder.

## Building Liberation
Using build script:
* `./liberation build` to build project (static library)
* `./liberation clean` to clean project

When built, there should be a `liberation.a` file in the `source/obj/local/$(TARGET_ARCH_ABI)` folder.

## License

```Logos
//Copyright (c) 2017, circleous

//Permission to use, copy, modify, and/or distribute this software for any purpose
//with or without fee is hereby granted, provided that the above copyright notice
//and this permission notice appear in all copies.

//THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
//REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
//FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
//INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
//OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
//THIS SOFTWARE.
```
