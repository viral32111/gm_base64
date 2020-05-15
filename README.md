# Base64

**Project started: 6/12/2020, Last updated: 6/12/2020**

This is a C++ module for Garry's Mod which allows developers to encode strings to Base64 and decode them from Base64. ~~I decided to make this because as of writing this, Garry's Mod only has [a function to encode strings to Base64](https://wiki.garrysmod.com/page/util/Base64Encode).~~

**UPDATE:** Garry's Mod now has [util.Base64Decode()](https://wiki.facepunch.com/gmod/util.Base64Decode()) too, so this repository has been archived as it no longer serves much purpose.

### Installation

1. Download the [latest release](https://github.com/viral32111/gm_base64/releases) binary file for your __server's__ operating system (`win32` for Windows, `osx` for MacOS and `linux` for Linux)
2. Rename the DLL prefix to match the realm you'll be using it on (Rename it to `gmsv_base64_win32.dll` if you're using it serverside on Windows, or `gmcl_base64_win32.dll` if you're using it clientside on Windows, etc.).
3. Navigate to your __server's__ root directory (where srcds.exe, garrysmod, bin, etc. are).
4. Create a new folder inside `garrysmod/lua/` called `bin` if it doesn't already exist.
5. Place the renamed DLL file into that folder.
6. Use the module in any Lua script by calling `require("base64")`.

### Usage
Here is a basic example on how to use this module:

```lua
require("base64")

local myString = "Hello World! This will be converted to Base64!"

local encoded = base64.encode(myString)
print(encoded) -- Should output 'SGVsbG8gV29ybGQhIFRoaXMgd2lsbCBiZSBjb252ZXJ0ZWQgdG8gQmFzZTY0IQ=='

local decoded = base64.decode(encoded)
print(decoded) -- Should output 'Hello World! This will be converted to Base64!'
```

###### [Copyright 2020 viral32111](LICENSE.md)
