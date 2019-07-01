
----------------------------------------------------
function setup()
    
    px.size( 480, 280 )
    
    font.load( "/usr/share/fonts/truetype/TerminusTTF-4.46.0.ttf", 9)
    
end

----------------------------------------------------
function draw()
    
    local animate = lfo.noise( 0.3 )
    
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
    
end

----------------------------------------------------
function exit()

end


