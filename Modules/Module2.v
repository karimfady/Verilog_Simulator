module circuit_2(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w;
wire n;
        
wire z;

not #(2) g1 (n,b);
        
and #(5) g0 (w,n,a);
        
nor #(7) g5 (z,c,b)
        
xor #(1) g4 (o,z,w);

        
endmodule; 