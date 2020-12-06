package curso;


simple Periodo {
    parameters:
        @display("i=device/periodo;i2=status/red, red");
    gates:
        //input in;
        //output out;
        input in[2];
        output out[2];
}

network Curso {
    types:
        channel D extends ned.DelayChannel {
            delay = 60s;
        }
    submodules:
        p[10]: Periodo;
    connections:
        
        for i=0..sizeof(p)-1 {            
        	p[i].out[0] --> D --> p[(i+1)%sizeof(p)].in[0];
        	p[i].out[1] --> D --> p[i].in[1];
        }
        
}
