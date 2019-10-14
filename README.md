np-pixelscript
=====================================
cute graphics scripting with oF and luaJIT

minimal sandbox for scripting 2d graphics using lua binded to some oF function, very opinionated workflow. 

Includes different lua namespaces:

- `px` for drawing shapes and lines and general control 
- `lfo` for cyclic animations 
- `png` for loading and displaying folders of .png images 
- `font` for drawing text
- `frag` for loading and rendering fragment shaders

For Lua scripting i'm using [ofxLua](https://github.com/danomatika/ofxLua), that i just tweaked a bit.    
A build of [luaJIT](http://luajit.org/) 2.0.5 for linux64 is included, for other systems you have to build it yourself and put the compiled library into `libs/luaJIT/lib/yourplatform`.

It also now include a `pixelscript` interpreter program which takes the file to evaluate as input.

Donate
------------ 
I support you, you support me!    
If you find this code useful, consider [fueling me with coffee](https://ko-fi.com/npisanti)!

License
------------
np-pixelscript Nicola Pisanti MIT License 2019   
[ofxLua](https://github.com/danomatika/ofxLua) Copyright (c) Dan Wilcox 2011-2017, MIT License   
[luaJIT](http://luajit.org/) Copyright (c) 2005-2017 Mike Pall, MIT License
