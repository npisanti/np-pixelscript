np-pixelscript
=====================================
cute graphics scripting with oF and luaJIT

sandbox for scripting low res graphics using lua binded to some oF function, very opinionated workflow. Will work only if you install luajit, for example on debian:
```
sudo apt-get install lua5.1 luajit liblua5.1-0-dev libluajit-5.1-dev 
```

Includes different lua namespaces:

- `px` for drawing shapes and lines and general control 
- `lfo` for cyclic animations 
- `sprite` for loading and displaying .png spritesheets
- `font` for drawing text

For Lua scripting i'm using [ofxLua](https://github.com/danomatika/ofxLua), that i just tweaked a bit.

Donate
------------ 
I support you, you support me!    
If you find this code useful, consider [fueling me with coffee](https://ko-fi.com/npisanti)!

License
------------
np-pixelscript Nicola Pisanti MIT License 2019   
ofxLua Copyright (c) Dan Wilcox 2011-2017   
