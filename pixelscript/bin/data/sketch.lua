
----------------------------------------------------
function setup()
    
    px.size( 480, 480 )
    
    font.load( "/usr/share/fonts/truetype/TerminusTTF-4.46.0.ttf", 9)
    
    png.load( "triangles", "/home/nicola/resources/ink/triangles" )

    -- paths are relative to the lua script path 
    frag.load( "invert", "invert.frag" ) 
    
    memo = 0    

end

----------------------------------------------------
function draw()

    px.begin()
    
    local animate = lfo.sine( 1.1 )
    
    px.clear()
    px.fill( false )
    
    px.color(255)
    
    px.point( 200, 10 )

    px.line( animate * 20, 20, 70, 50 )
    
    px.rect( 80, 80, 100, 20 )
    
    font.draw( "this is a test", 80 + animate * 10 , 50 )
    
    px.circle( 25, 80, 15 )

    px.triangle( 240, 140, 180 + animate*30, 110, 230, 100 )
    
    px.fill()
    
    px.blendmode(1)
    
    px.begin_shape()
        px.polypath( 180, 100, 20, 4, - math.pi*0.5 )
        px.next()
        px.polypath( 180, 100, 10, 4, - math.pi*0.5 )
    px.end_shape( true )
    
    png.mode( 0 )
    png.select("triangles")
    png.pct( lfo.triangle(0.25) )
    png.draw( 300, 0 )

    local sync = 0.3 
    
    px.color( lfo.sine( sync ) * 255 )

    local now = lfo.tick( sync )
    if now ~= memo then 
        memo = now;
        print( "trigger "..now )
    end
    
    textcount = "now is "..now
    font.draw( textcount, 50 , 250 )
    
    px.finish()

    frag.apply( "invert" )
    
end

----------------------------------------------------
function exit()

end
