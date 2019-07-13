
----------------------------------------------------
function setup()
    
    px.size( 480, 280 )
    
    font.load( "/usr/share/fonts/truetype/TerminusTTF-4.46.0.ttf", 9)
    
    sprite.load( "test.png", 8, 8 )
    
end

----------------------------------------------------
function draw()

    local animate = lfo.sine( 1.1 )
    
    px.clear()
    px.fill( false )
    
    px.color(255)
    
    px.point( 200, 10 )

    px.color( 255, 0, 0 )

    px.line( animate * 20, 20, 70, 50 )
    
    px.rect( 80, 80, 100, 20 )
    
    font.draw( "this is a test", 80 + animate * 10 , 50 )
    
    px.circle( 25, 80, 15 )

    px.triangle( 240, 140, 180 + animate*30, 110, 230, 100 )
    
    px.fill()
    
    px.blendmode(1)
    
    px.color( 0, 255, 0 )
    
    px.begin()
        px.poly( 180, 100, 20, 4, - math.pi*0.5 )
        px.next()
        px.poly( 180, 100, 10, 4, - math.pi*0.5 )
    px.finish( true )
    
    sprite.bind( "test" ) -- name of the file without .png
        sprite.pct( lfo.triangle(0.5) )
        sprite.draw( 5, 15 )
    sprite.unbind()
end

----------------------------------------------------
function exit()

end


