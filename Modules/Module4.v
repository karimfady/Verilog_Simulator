module circuit_4(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w;
        
wire y;
        
wire n;
        


or #(9) g2 (w,a,b);
nand #(7) g3 (y,w,c);
        
and #(5) g0 (n,a,y);
or #(9) g1 (o,n,b);
        
endmodule;
