
----------------------------------------------------
function setup()
    
    px.size( 480, 280 )
    
    font.load( "/usr/share/fonts/truetype/TerminusTTF-4.46.0.ttf", 9)
    
    png.load( "/home/nicola/resources/motore/trio" )
    
end

----------------------------------------------------
function draw()

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
    
    px.begin()
        px.polypath( 180, 100, 20, 4, - math.pi*0.5 )
        px.next()
        px.polypath( 180, 100, 10, 4, - math.pi*0.5 )
    px.finish( true )
    
    png.mode( 0 )
    png.select("trio")
    png.pct( lfo.triangle(0.25) )
    png.draw( 300, 0 )
    
end

----------------------------------------------------
function exit()

end
