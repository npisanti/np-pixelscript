
----------------------------------------------------
function setup()
    
    px.size( 480, 280 )
    
    font.load( "/usr/share/fonts/truetype/TerminusTTF-4.46.0.ttf", 9)
    
    sprite.load( "data/test.png", 8, 8 )
    
end

----------------------------------------------------
function draw()
    
    lfo.speed( 0.03 )
    local animate = lfo.sine()
    
    px.clear()
    px.fill( false )

    px.color( 255, 60, 0 )

    px.line( animate * 20, 20, 70, 50 )
    
    px.rect( 80, 80, 100, 20 )
    
    font.draw( "test test", 80 + animate * 10 , 50 )
    
    px.circle( 25, 80, 15 )

    px.triangle( 240, 140, 180 + animate*30, 110, 230, 100 )
    
    px.fill()
    
    px.begin()
        px.poly( 200, 50, 20, 4, - math.pi*0.5 )
        px.next()
        px.poly( 200, 50, 10, 4, - math.pi*0.5 )
    px.finish( true )
    
    sprite.bind( "test" )
        sprite.pct( lfo.triangle() )
        sprite.draw( 5, 5 )
    sprite.unbind()
end

----------------------------------------------------
function exit()

end


