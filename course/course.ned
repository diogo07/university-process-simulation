package course;


simple Period {
    parameters:
        @display("i=device/periodo;i2=status/red, red");
    gates:
        input in[2];
        output out[2];
}

network Course {
    types:
        channel D extends ned.DelayChannel {
            delay = 60s;
        }
    submodules:
        p[10]: Period;
    connections:
        
        for i=0..sizeof(p)-1 {            
        	p[i].out[0] --> D --> p[(i+1)%sizeof(p)].in[0];
        	p[i].out[1] --> D --> p[i].in[1];
        }
        
}
