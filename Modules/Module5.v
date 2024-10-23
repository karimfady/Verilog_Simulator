module circuit_1(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w;
        
wire y;
        
wire n;
        
wire z;
wire x;
        
and #(5) g0 (w,a,b);
        
not #(2) g1 (n,a);
        
or #(9) g2 (y,n,c);
        
nand #(7) g3 (z,n,c);
        
or #(9) g2 (x,w,z);
and #(5) g0 (o,y,x);
        
endmodule; 